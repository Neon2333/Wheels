#pragma once

#include <QWidget>
#include "ui_bubbleTipsWidget.h"
#include <QIcon>
#include <QFontMetrics>
#include <QPropertyAnimation>

// 三角形的高度和底边长度
#define TRIANGLE_HEIGHT 15
#define TRIANGLE_WIDTHHALF  5
// 透明宽度（需要大于TRIANGLE_HEIGHT才能容纳三角形显示）
#define TRANSPARENT_LENGTH 20
// 文字左边距
#define LEFT_MARGIN 0
// 文字上边距
#define TOP_MARGIN 0

enum class DIRECT
{
    DIRECT_LEFT = 1,
    DIRECT_TOP,
    DIRECT_RIGHT,
    DIRECT_BOTTOM
};

class BubbleTipsWidget : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(QColor backColor READ backColor WRITE setBackColor)

public:
    BubbleTipsWidget(QWidget* parent = nullptr, int widthFixed = 300);
    ~BubbleTipsWidget();

    //背景色
    QColor backColor() const;
    void setBackColor(QColor color);

    // 设置三角方向(左上右下)，位置系数(宽度 * 系数)
    void setDirect(DIRECT direct = DIRECT::DIRECT_TOP, double size = 0.75);

    //文本内容
    void setContent(const QString& content, QColor color = {});

    //文本font
    void setContentFont(QFont font = {});

    //文本边距
    void setLeftTopMargin(int leftMargin = LEFT_MARGIN, int topMargin = TOP_MARGIN);

    //设定图标、尺寸（尺寸要设定适当，确保图标完整显示）
    void setIcon(QIcon icon, int w = 100, int h = 100);

    //根据三角形顶点，确定整个bubbletips的左上角坐标
    void setPositionByTriangle(int x, int y);

    //设定目标控件，自动按照鼠标进入目标控件的位置设置箭头方向、位置
    void setAutoPosition(bool isAuto, QWidget* target);

    //动画弹出显示
    void animeShow();

    //动画消失
    void animeClose();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void closeEvent(QCloseEvent* event) override;

private:
    Ui::BubbleTipsWidgetClass ui;

    QPropertyAnimation m_animationEnter;
    QPropertyAnimation m_animationLeave;

    int m_widthFixed;                       //提示框宽度（宽度不要太大，高度自适应）
    int m_leftMargin = LEFT_MARGIN;         //内容左右边距
    int m_topMargin = TOP_MARGIN;           //内容上下边距
    int m_textHeight;   //文本显示实际高度（与m_iconHeight联合确定较大者作为height()实际取值）
    int m_iconHeight;   //icon实际高度

    int m_triposX = 0;  //三角形顶点坐标（相对屏幕的绝对坐标）
    int m_triposY = 0;  //三角形顶点坐标
    int m_posX = 0;     //this窗口的坐标（相对屏幕的绝对坐标）
    int m_posY = 0;     //this窗口的坐标

    QFont m_font;                             //文本字体信息
    QColor  m_backColor{ 255, 0, 255, 255 };  //背景色

    DIRECT  m_direct = DIRECT::DIRECT_TOP;    //三角形位置
    double m_posRatio = 0.75;                 //三角形位置（顶点坐标占边长比例）

    bool m_autoPosition = false;              //是否自动在target控件上寻找位置显示
    QWidget* m_target;  //弹出tips的控件（父窗口是设定过滤器的）

    QIcon m_icon;       //图标
    int calculateTextHeight(const QString& text, const QFont& font, int width); //计算文本显示高度
};
