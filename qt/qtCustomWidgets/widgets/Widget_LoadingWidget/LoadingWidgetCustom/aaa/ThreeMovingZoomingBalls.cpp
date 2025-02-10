#include "ThreeMovingZoomingBalls.h"

ThreeMovingZoomingBalls::ThreeMovingZoomingBalls(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("cadetblue");
}


void ThreeMovingZoomingBalls::paintEvent(QPaintEvent*)
{
	//三个一边移动一边缩放的小球
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));
    qreal x = width();
    qreal y = height();
    painter.translate(0, y / 2);
    const qreal delta = 0.08 * x;
    const qreal minr = 0.02 * x;
    for (int i = 0; i < 5; ++i) {
        qreal ang = m_angle + 90 * i;
        qreal posx = ang / 360 * x;
        if (posx > x) posx -= x;
        qreal r = minr + delta * qSin(M_PI / x * posx);
        painter.drawEllipse(QPointF(posx, 0), r, r);
    }
}
