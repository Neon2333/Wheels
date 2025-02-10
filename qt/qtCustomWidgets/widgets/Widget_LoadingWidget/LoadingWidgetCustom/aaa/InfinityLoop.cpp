#include "InfinityLoop.h"

InfinityLoop::InfinityLoop(QWidget* parent):LoadingWidget(parent)
{
    m_colorList = QList<QColor>{ "darkgray", "lightblue" };
}

void InfinityLoop::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const qreal x = width();
    const qreal y = height();
    const qreal r = 0.45 * x / (1 + qSqrt(2));
    static const qreal _sqrt2 = 0.70711;// 1/根号2
    painter.setBrush(Qt::NoBrush);
    painter.translate(x / 2, y / 2);

    QColor railColor = m_colorList[0];
    railColor.setAlphaF(0.5);
    QPen pen(railColor);
    int penWidth = 6;
    if (x <= 100)
    {
        penWidth = 5;
    }
    else if (x > 100 && x <= 200)
    {
        penWidth = 6;
    }
    else if (x > 200 && x <= 300)
    {
        penWidth = 7;
    }
    else if (x > 300 && x <= 400)
    {
        penWidth = 8;
    }
    else
    {
        penWidth = 10;
    }
    pen.setWidth(penWidth);
    painter.setPen(pen);

    //先画一个淡色的轨道
    QPainterPath pp;
    pp.moveTo(0, 0);
    pp.lineTo(_sqrt2 * r, -_sqrt2 * r);
    pp.arcTo(QRectF(0.45 * x - 2 * r, -r, 2 * r, 2 * r), 135, -270);
    pp.lineTo(-_sqrt2 * r, -_sqrt2 * r);
    pp.arcTo(QRectF(-0.45 * x, -r, 2 * r, 2 * r), 45, 270);
    pp.lineTo(0, 0);
    painter.drawPath(pp);
    //画一个小火车
    pen.setColor(m_colorList[1]);
    painter.setPen(pen);
    QBrush brush(m_colorList[1]); // 蓝色填充
    painter.setBrush(brush);

    static const int totPercent = 30;
    const int rotateAngle = 270;
    int radius = 1;
    if (x <= 100)
    {
        radius = 1;
    }
    else if (x > 100 && x <= 200)
    {
        radius = 2;
    }
    else if (x > 200 && x <= 300)
    {
        radius = 3;
    }
    else if (x > 300 && x <= 400)
    {
        radius = 4;
    }
    else
    {
        radius = 5;
    }

    if (m_angle < rotateAngle) 
    {
        for (int i = 0; i < totPercent; ++i)
        {
            qreal percent = m_angle / rotateAngle - 0.01 * i;
            int tmp = percent * 100;
            percent = tmp / 100.0;//精度不要太高,否则起点会有抖动
            if (percent < 0) break;
            painter.drawEllipse(pp.pointAtPercent(percent), radius, radius);
        }
        
    }
    else {
        int left = (360 - m_angle) / (360 - rotateAngle) * totPercent;
        for (int i = 0; i < left; ++i) {
            painter.drawEllipse(pp.pointAtPercent(1 - 0.01 * i), radius, radius);
        }
    }
}
