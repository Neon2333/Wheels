#ifndef NAVIBAR_H
#define NAVIBAR_H


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <mutex>

class Bitmap { //位图bitmap类
private:
    char* M;
    long long int N; //比特图所存放的空间M[]，容量为N*sizeof(char)*8比特
    std::mutex mtx;
protected:
    void init(long long int n)   //初始化位图空间
    {
        M = new char[N = (n + 7) / 8];   //申请内存
        memset(M, 0, N);    //初始化内存块
    }

public:
    Bitmap(long long int n = 8) { init(n); } //按指定或默认规模创建比特图（为测试暂时选用较小的默认值）
    Bitmap(char* file, long long int n = 8) //按指定或默认规模，从指定文件中读取比特图
    {
        init(n); FILE* fp = fopen(file, "r"); fread(M, sizeof(char), N, fp); fclose(fp);
    }
    ~Bitmap() { delete[] M; M = NULL; } //析构时释放比特图空间

    void set(long long int k)   //置位第k个标志位
    {
        expand(k);   //拓容
        //mtx.lock();
        M[k >> 3] |= (0x80 >> (k & 0x07));  //M[第k个标志位所在的字节(k/8 取整)] |= （第k个标志位在所在字节中的位数(取余)）
        //mtx.unlock();
    }

    void clear(long long int k) {
        expand(k);    //拓容
        M[k >> 3] &= ~(0x80 >> (k & 0x07)); //M[第k个标志位所在的字节(k/8 取整)] &= ~（第k个标志位在所在字节中的位数(取余)）
    }

    bool test(long long int k) {//取出指定字节中的指定位
        expand(k);    //拓容
        return M[k >> 3] & (0x80 >> (k & 0x07));  //M[第k个标志位所在的字节(k/8 取整)] &（第k个标志位在所在字节中的位的值）
    }

    void dump(char* file) //将位图整体导出至指定的文件，以便对此后的新位图批量初始化
    {
        FILE* fp = fopen(file, "w"); fwrite(M, sizeof(char), N, fp); fclose(fp);
    }

    char* bits2string(long long int n)
    { //将前n位转换为字符串——
        expand(n - 1); //此时可能被访问的最高位为bitmap[n - 1]
        char* s = new char[n + (long long)1]; s[n] = '\0'; //字符串所占空间，由上层调用者负责释放
        for (long long int i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
        return s; //返回字符串位置
    }

    void expand(long long int k)
    { //若被访问的bitmap[k]已出界，则需扩容
        if (k < 8 * N) return; //仍在界内，无需扩容
        long long int oldN = N; char* oldM = M;
        init((long long)2 * k); //与向量类似，加倍策略
        memcpy_s(M, N, oldM, oldN);
        delete[] oldM; //原数据转移至新空间
    }

    void print(long long int n) //逐位打印以检验位图内容，非必需接口
    {
        expand(n);
        for (unsigned int i = 0; i < n; i++)
            printf(test(i) ? "1" : "0");
    }

    static bool isPrime(int n) {  //判断某个数是否为素数
        if (n <= 3) {
            return n > 1;
        }
        // 不在6的倍数两侧的一定不是质数
        if (n % 6 != 1 && n % 6 != 5) {
            return false;
        }
        int s = (int)sqrt(n);
        for (int i = 5; i <= s; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }

    //返回耗费内存MB
    unsigned int size()
    {
        return (unsigned int)(N / (1024 * 1024));
    }
};


#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <navibuttongroup.h>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class NaviBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor curBtnColor READ curBtnColor WRITE setCurBtnColor NOTIFY curBtnColorChanged FINAL)

public:
    explicit NaviBar(QWidget *parent = nullptr);
    ~NaviBar();

    void setBackGround(QColor bgcolor=QColor("black"));
    void setButtonMinWidth(int w);
    void setPaddings(int left, int top, int right, int bottom);
    void setIconSize(QSize iconSize);
    void setTextSize(int pixel);
    void setMoveSpeed(int milliseconds);

    void appendButton(QIcon icon, QString text, QColor iconColor=QColor("white"), QColor textColor=QColor("white"), QColor btnColor=QColor(qRgba(247, 59, 89, 150)));
    void insertButton(int index, QIcon icon, QString text, QColor iconColor=QColor("white"), QColor textColor=QColor("white"), QColor btnColor=QColor(qRgba(247, 59, 89, 150)));
    void removeButton(int index, int id);

    QToolButton& curBtn() const;
    QToolButton& btn(int btnID) const;
    int btnID(int btnIndex) const;

    void setBtnCountMax(int maxCount);
    int btnCountMax() const;

private:
    void initUI();
    QIcon changeIconColor(QIcon icon, QColor newColor);
    void showHighLight(QToolButton* curBtn);
    void moveHighLight(QToolButton* curBtn);
    int createID() const; //分配可用ID
    //属性：当前按钮颜色
    QColor curBtnColor() const;
    void setCurBtnColor(QColor color);

private:
    int m_btnIDMax; //按钮个数最大值

    QSize m_btnSize; //按钮最小尺寸，防止显示不全

    QSize m_iconSize;   //按钮icon尺寸

    int m_textSize; //按钮text尺寸，单位px

    int m_moveSpeed;    //高亮移动速度

    std::unique_ptr<Bitmap> m_btnsIDPool=nullptr;//存储按钮可能id的使用情况
    QList<int> m_btnsID; //记录按钮的(id,index)
    std::unordered_map<int,QColor> m_btnColors; //存储所有按钮的(id,高亮颜色)

    NaviButtonGroup* m_btnsGroup;    //按钮组
    QLabel* m_label_background;     //背景颜色
    QGraphicsDropShadowEffect* m_curBtnShadow; //高亮阴影
    QLabel* m_label_highlight;      //当前按钮高亮
    QToolButton* m_curBtn;    //记录当前选中按钮

    QPropertyAnimation* m_aniHighlightMove; //当前高亮移动动画
    QPoint m_highlightStartPos;   //高亮动画初始位置
    QPoint m_highlightEndPos;     //高亮动画结束位置
    QPropertyAnimation* m_aniHighlightColorChange;  //当前高亮、阴影颜色改变动画
    QColor m_curBtnColor;   //当前按下按钮颜色
    QColor m_lastBtnColor;  //上个按下按钮颜色

    QParallelAnimationGroup* m_paralAniGroup;   //并行动画组

protected:
    void showEvent(QShowEvent* se) override;
    void paintEvent(QPaintEvent* ev) override;

signals:
    void curBtnColorChanged(QColor color);
};
#endif // NAVIBAR_H
