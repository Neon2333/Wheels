#include "VolumeBarTiny.h"

VolumeBarTiny::VolumeBarTiny(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("purple");
}


void VolumeBarTiny::paintEvent(QPaintEvent*)
{
	//VolumeBar的简化版,三个循环变化高度的小柱子
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));
    const qreal x = width();
    const qreal y = height();
    painter.translate(x / 2, y / 2);
    static const int w = 8;
    static const int h = 16;
    static const int gap = 4;
    qreal h1 = h / 2 + h / 2 * qSin(-2 * M_PI / 360 * m_angle);
    qreal h2 = h / 2 + h / 2 * qSin(-2 * M_PI / 360 * m_angle + M_PI * 2 / 3);
    qreal h3 = h / 2 + h / 2 * qSin(-2 * M_PI / 360 * m_angle + M_PI * 4 / 3);
    qreal yList[3] = { -h1,-h2,-h3 };
    qreal xList[3] = { -1.5 * w - gap,-0.5 * w,0.5 * w + gap };
    for (int i = 0; i < 3; ++i) {
        painter.drawRect(QRectF(xList[i], yList[i], w, -2 * yList[i]));
    }
}
