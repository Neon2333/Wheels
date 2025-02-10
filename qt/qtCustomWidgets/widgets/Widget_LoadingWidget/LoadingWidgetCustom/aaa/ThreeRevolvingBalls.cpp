#include "ThreeRevolvingBalls.h"

ThreeRevolvingBalls::ThreeRevolvingBalls(QWidget* parent):LoadingWidget(parent)
{
    m_colorList = QList<QColor> { "cadetblue", "coral", "hotpink"};
    //m_colorList = QList<QColor>{ "cadetblue", "coral", "hotpink", "lightblue", "yellow", "lightgreen" };
}


void ThreeRevolvingBalls::paintEvent(QPaintEvent*)
{
	//三个绕着中心店旋转和缩放的球
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const qreal x = width();
    const qreal y = height();
    painter.setPen(Qt::NoPen);
    painter.translate(x / 2, y / 2);
    painter.rotate(m_angle);
    const int count = m_colorList.size();
    for (int i = 0; i < count; ++i)
    {
        painter.setBrush(QBrush(m_colorList[i]));
        const auto r = (0.1 + 0.03 * qSin(M_PI / 60 * m_angle)) * y;
        painter.drawEllipse(QPointF(0, -y / 6), r, r);
        painter.rotate(360 / count);
    }
}
