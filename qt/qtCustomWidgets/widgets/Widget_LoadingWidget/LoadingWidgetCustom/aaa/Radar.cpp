#include "Radar.h"

Radar::Radar(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("deepskyblue");
}


void Radar::paintEvent(QPaintEvent*)
{
	//像一个雷达一样扫描,等待耗时操作的结束
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const int x = width();
    const int y = height();
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_color);
    //step1: 画一个淡色背景,很多简约的界面都需要透明背景,这一步可以删掉
    //painter.drawRoundedRect(rect(), x / 12, x / 12);
    //step2: 画一个雷达
    painter.translate(x / 2, y / 2);
    QConicalGradient gra(QPointF(0, 0), 45);
    QColor color0 = m_color;
    QColor color1(color0.red(), color0.green(), color0.blue(), 100);
    gra.setColorAt(0, color0);
    gra.setColorAt(0.2, color1);
    gra.setColorAt(1, "transparent");
    painter.setBrush(gra);
    painter.rotate(m_angle);
    const auto rect = QRectF(-x / 4, -y / 4, x / 2, y / 2);
    painter.drawPie(rect, 45 * 16, 90 * 16);
}
