#include "ScrollBarCustom01.h"

ScrollBarCustom01::ScrollBarCustom01(QWidget *parent)
	: QScrollBar(parent)
{
	ui.setupUi(this);
}

ScrollBarCustom01::~ScrollBarCustom01()
{}

void ScrollBarCustom01::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.eraseRect(this->rect());  //清空画布

    int x = width();
    int y = height();
    qreal ratio = this->value() * 1.0 / this->maximum();    //当前值和最大值的比例

    p.setRenderHints(QPainter::Antialiasing);
    QPen pen;
    pen.setColor("black");  //滚动条颜色
    p.setPen(pen);

    if (this->orientation() == Qt::Vertical)
    {
        //垂直方向滚动条
        //画轨道
        p.drawRoundedRect(QRectF(x / 2 - 1, 20, 2, y - 40), 1, 1); // w=2，h=y-40，上下留白20，左右留白x/2-1

        //画圆（圆角矩形）
        int R = x - 2;    //圆直径（圆角矩形模拟圆）
        int _y = (y - 40 - R) * ratio;    //圆左上角纵坐标
        p.setBrush(QBrush("gray"));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF((x - R) / 2, _y + 20, R, R), R, R);
    }
    else
    {
        //水平方向滚动条
        //画轨道
        p.drawRoundedRect(QRectF(20, y / 2 - 1, x - 40, 2), 1, 1); // w=2，h=y-40，上下留白20，左右留白x/2-1

        //画圆（圆角矩形）
        int R = y - 2;    //圆直径（圆角矩形模拟圆）
        int _x = (x - 40 - R) * ratio;    //圆左上角纵坐标
        p.setBrush(QBrush("gray"));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF(_x + 20, (y - R) / 2, R, R), R, R);
    }

}