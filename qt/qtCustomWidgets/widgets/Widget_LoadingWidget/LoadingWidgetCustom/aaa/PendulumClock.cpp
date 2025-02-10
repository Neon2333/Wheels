#include "PendulumClock.h"

PendulumClock::PendulumClock(QWidget* parent) :	LoadingWidget(parent)
{
    m_color = QColor("silver");
}


void PendulumClock::paintEvent(QPaintEvent*)
{
	//µõÖÓÖÓ°Ú
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const qreal x = width();
    const qreal y = height();
    painter.translate(x / 2, y / 8);
    QPen pen(m_color);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.rotate(30 * qSin(M_PI / 180 * m_angle));
    painter.setBrush(QBrush(m_color));
    painter.drawLine(0, 0, 0, 0.6 * y);
    painter.translate(0, 0.6 * y);
    painter.drawEllipse(QPointF(0, 0), 16 * x/200, 16 * y/200);
}
