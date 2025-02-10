#ifndef QANIMATIONSTACKEDWIDGET_H
#define QANIMATIONSTACKEDWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QPainter>

class QAnimationStackedWidget : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY(int leftWidth READ leftWidth WRITE setLeftWidth)
    Q_PROPERTY(int topHeight READ topHeight WRITE setTopHeight)
public:
    explicit QAnimationStackedWidget(QWidget *parent = 0);
    ~QAnimationStackedWidget();

    //切换方向
    enum class switchDirection
    {
        Horizontal, //水平
        Vertical   //垂直
    };

    //动画模式
    enum class aniMode
    {
        Switch,   //切换
        Cover     //覆盖
    };

    //设置动画持续的间隔
    void setDuration(int ms);
    //设定动画模式
    void setAniMode(aniMode mode);
    aniMode getAniMode();
    //设定切页方向
    void setSwitchDirection(switchDirection dir);
    switchDirection getSwitchDirection();

private:
    //leftWidth属性访问函数
    void setLeftWidth(int w);
    int leftWidth();

    //topHeight属性访问函数
    void setTopHeight(int h);
    int topHeight();

    //水平切页
    void paintLeft(QPainter& painter, int pageIndex);
    void paintRight(QPainter& painter, int pageIndex);

    //垂直切页
    void paintTop(QPainter& painter, int pageIndex);
    void paintBottom(QPainter& painter, int pageIndex);

private:
    int m_leftWidth;    //左侧部分的宽度（动画修改变量）
    int m_topHeight;    //上侧部分的高度（动画修改变量）

    QPropertyAnimation* m_aniSwitchPage;    //切页动画
    int m_aniDuration;  //动画的持续时间
    int m_lastIndex;    //记录切页前的index
    bool m_isNext;      //是否是向后切页
    switchDirection m_switchDirection;  //切页方向
    aniMode m_aniMode;  //动画模式

protected:
    virtual void paintEvent(QPaintEvent* ev) override;

signals:


public slots:
    //切页
    void switchPage(bool isNext);
};

#endif // QANIMATIONSTACKEDWIDGET_H
