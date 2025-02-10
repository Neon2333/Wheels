#include "JellyInBox.h"

JellyInBox::JellyInBox(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor>{ "grey" , "lightblue"};
}


void JellyInBox::paintEvent(QPaintEvent* event)
{
	//一个会伸缩的果冻在一个小盒子里面,一开始拉伸,然后移动,然后收缩
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);

    int x = this->width();
    const int y = this->height();

    //先画一个盒子
    QPen pen(m_colorList[0]);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(1, 0.4375 * y, x - 2, y / 8), y / 16.0, y / 16.0);

    //画果冻
    pen.setColor(m_colorList[1]);
    pen.setCapStyle(Qt::RoundCap);
    painter.setBrush(Qt::NoBrush);

    const int gap = 4;//果冻和盒子之间的间距
    const int boxGap = 1;//盒子的外间距
    const qreal jh = y / 8 - gap * 2;//果冻高度
    pen.setWidthF(jh);
    painter.setPen(pen);

    painter.translate(boxGap + gap + jh / 2, y / 2);
    x -= (boxGap + gap) * 2 + jh;//可以移动的x范围是总宽度 - 两边的两个间距 - 笔头厚度
    const qreal maxw = 0.4 * x;//最大的果冻宽度
    int jx = 0;
    qreal jw = 0;

    if (m_angle < 90) {
        jw = maxw * m_angle / 90;
    }
    else if (m_angle < 270) {
        jw = maxw;
        jx = (x - maxw) * (m_angle - 90) / 180;
    }
    else {
        jx = x - maxw + (m_angle - 270) / 90 * maxw;
        jw = x - jx;
    }
    painter.drawLine(jx, 0, jx + jw, 0);
}
