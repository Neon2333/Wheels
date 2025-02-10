#include "VolumeBar.h"

VolumeBar::VolumeBar(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("purple");
}


void VolumeBar::paintEvent(QPaintEvent*)
{
	//一个类似音量检测器的动画,有一排小柱子,它们的高度随时变化
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));

    const qreal x = width();
    const qreal y = height();

    static const int amount = 8;//8个小柱子
    static const int gap = 2;//小柱子之间的间距
    const qreal w = (0.667 * x - (amount - 1) * gap) / amount;

    painter.translate(x / 6, 0.667 * y);
    static QList<qreal> offsetList;
    static QList<qreal> factorList;
    if (offsetList.size() <= 0) {
        QRandomGenerator g;
        for (int i = 0; i < amount; ++i) offsetList.push_back(g.bounded(1.0) * 2 * M_PI);
        for (int i = 0; i < amount; ++i) factorList.push_back(g.bounded(4) + 1);//周期不一样
    }

    for (int i = 0; i < amount; ++i) {
        const int maxh = y / 3;
        const int h = (1 + qSin((2 * M_PI / 360 * m_angle * factorList[i]) + offsetList[i])) / 2 * 0.8 * maxh + 0.2 * maxh;
        painter.drawRect(i * (gap + w), -h, w, h);
    }
}
