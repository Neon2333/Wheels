#include "FillGlassBead.h"

FillGlassBead::FillGlassBead(QWidget* parent) : LoadingWidget(parent)
{
    m_waveType = WaveType::SwayingWater;
    m_color = QColor("lightseagreen");
    m_font = QFont("Microsoft YaHei", 7, 4);
}


void FillGlassBead::setWaveType(WaveType t)
{
    m_waveType = t;
}

void FillGlassBead::paintEvent(QPaintEvent*)
{
	//一颗玻璃珠,内部逐渐充满液体
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const int x = width();
    const int y = height();
    if (m_angle < 90) 
    {
        //只要画一个坠落的小球
        painter.translate(x / 2, 0);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(m_color));
        qreal posY = y / 4.0 * m_angle / 90;//坠落的小球最低点是高度的四分之一
        painter.drawEllipse(QPointF(0, posY), 5, 5);
    }
    else 
    {
        painter.translate(x / 2, 0.625 * y);
        QPen pen(m_color);
        pen.setWidth(4);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        const qreal r = 0.375 * y;
        if (m_angle < 225) 
        {
            //画一个包裹玻璃珠的圆环
            //最高点起点角度是90,弧长是0,最低点起点角度是-90,弧长是360
            qreal proportion = (m_angle - 90) / 135.0;
            painter.drawArc(QRectF(-r, -r, 2 * r, 2 * r), 16 * (90 - 180 * proportion), 16 * 360 * proportion);
        }
        else 
        {
            //画一个退去的包裹圆环
            //最开始起点角度是-90,最后起点角度是90
            qreal proportion = (m_angle - 225) / 135.0;
            painter.drawArc(QRectF(-r, -r, 2 * r, 2 * r), 16 * (-90 + 180 * proportion), 16 * (360 - proportion * 360));
            //再画一个上涨的水波
            QPainterPath pp;
            const qreal startx = -x / 2;
            const qreal starty = 0.375 * y - 0.75 * y * proportion;
            if (m_waveType == WaveType::PeacefulWater) 
            {
                pp.addRect(QRectF(startx, starty, x, y));
            }
            else
            {
                QPointF start(startx, starty);
                QPointF end(start.x() + x, start.y());
                const qreal h = qSin(4 * M_PI * proportion) * x * 0.3;
                QPointF c1(start.x() + 0.25 * x, start.y() + h);
                QPointF c2(start.x() + 0.75 * x, start.y() - h);
                pp.moveTo(start);
                pp.cubicTo(c1, c2, end);    //贝塞尔曲线
                pp.lineTo(end.x(), 999);//999没有具体含义,大一点就行了
                pp.lineTo(startx, 999);
                pp.closeSubpath();
            }
            painter.setClipPath(pp);
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(m_color));
            const qreal r2 = r - 4;
            painter.drawEllipse(QRectF(-r2, -r2, 2 * r2, 2 * r2));
        }
    }

}
