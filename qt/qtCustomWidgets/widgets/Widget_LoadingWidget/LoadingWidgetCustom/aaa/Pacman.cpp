#include "Pacman.h"

Pacman::Pacman(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor>{ "yellow", "black", "yellow" };
}


void Pacman::paintEvent(QPaintEvent*)
{
	//吃豆人
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const qreal x = width();
    const qreal y = height();
    const qreal r = 0.2 * x;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_colorList[0]));   //眼睛
    painter.translate(4, y / 2);
    qreal startAngle = 22.5 + 22.5 * qSin(M_PI / 90 * m_angle + M_PI / 2);
    qreal span = 360 - 2 * startAngle;
    painter.drawPie(QRectF(0, -r, 2 * r, 2 * r), startAngle * 16, span * 16);
    painter.setBrush(QBrush(m_colorList[1]));   //身体
    painter.drawEllipse(QPointF(r * 0.8, -r / 2), 4, 4);

    //画移动的豆子
    painter.setBrush(QBrush(m_colorList[2]));
    painter.resetTransform();
    painter.translate(x, y / 2);
    qreal ratio = m_angle / 360;
    for (int i = 0; i < 3; ++i) {
        ratio += 0.333;
        if (ratio > 1) ratio -= 1;
        painter.drawEllipse(QPointF(-(x - 2 * r) * ratio, 0), 8, 8);
    }
}
