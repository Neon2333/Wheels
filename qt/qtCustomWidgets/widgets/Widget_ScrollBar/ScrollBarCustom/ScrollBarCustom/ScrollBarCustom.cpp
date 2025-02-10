#include "ScrollBarCustom.h"

ScrollBarCustom::ScrollBarCustom(QWidget *parent, int lenHandler, int widthGroove, int widthHandler)
	: QScrollBar(parent), m_lenHandler(lenHandler), m_widthGroove(widthGroove), m_widthHandler(widthHandler)
{
	ui.setupUi(this);

    colorBorder = QColor("transparent");
    colorGroove = QColor("red");
    colorHandler = QColor("gray");
}

ScrollBarCustom::~ScrollBarCustom()
{}

void ScrollBarCustom::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.eraseRect(this->rect());  //清空画布

    int x = width();
    int y = height();
    qreal ratio = this->value() * 1.0 / this->maximum();    //当前值和最大值的比例

    p.setRenderHints(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(colorBorder);  //滚动条边框颜色
    p.setPen(pen);

    if (this->orientation() == Qt::Vertical) //垂直方向滚动条
    {
        //槽
        p.setBrush(QBrush(colorGroove));
        p.drawRoundedRect(QRectF((x - m_widthGroove)/2, 20, m_widthGroove, y - 40), m_widthGroove /2, m_widthGroove /2); // width=W，height=y-40，上下留白20，左右留白(x-W)/2

        //滑块（圆形或圆角矩形）
        int R = m_widthGroove + m_widthHandler;    //圆角直径
        int _y = (y - 40 - R) * ratio;    //圆左上角纵坐标
        p.setBrush(QBrush(colorHandler));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF((x - R) / 2, _y + 20, R, R + m_lenHandler), R * 0.5, R * 0.5);
    }
    else//水平方向滚动条
    {
        //槽
        p.setBrush(QBrush(colorGroove));
        p.drawRoundedRect(QRectF(20, (y - m_widthGroove)/2, x - 40, m_widthGroove), m_widthGroove /2, m_widthGroove /2); // width=W，height=y-40，上下留白20，左右留白(x-W)/2

        //滑块（圆形或圆角矩形）
        int R = m_widthGroove + m_widthHandler;    //圆角直径
        int _x = (x - 40 - R) * ratio;    //圆左上角纵坐标
        p.setBrush(QBrush(colorHandler));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF(_x + 20, (y - R) / 2, R + m_lenHandler, R), R * 0.5, R * 0.5);
    }
}