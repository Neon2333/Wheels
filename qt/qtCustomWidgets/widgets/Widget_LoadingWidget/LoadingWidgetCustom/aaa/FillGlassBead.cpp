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
	//һ�Ų�����,�ڲ��𽥳���Һ��
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const int x = width();
    const int y = height();
    if (m_angle < 90) 
    {
        //ֻҪ��һ��׹���С��
        painter.translate(x / 2, 0);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(m_color));
        qreal posY = y / 4.0 * m_angle / 90;//׹���С����͵��Ǹ߶ȵ��ķ�֮һ
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
            //��һ�������������Բ��
            //��ߵ����Ƕ���90,������0,��͵����Ƕ���-90,������360
            qreal proportion = (m_angle - 90) / 135.0;
            painter.drawArc(QRectF(-r, -r, 2 * r, 2 * r), 16 * (90 - 180 * proportion), 16 * 360 * proportion);
        }
        else 
        {
            //��һ����ȥ�İ���Բ��
            //�ʼ���Ƕ���-90,������Ƕ���90
            qreal proportion = (m_angle - 225) / 135.0;
            painter.drawArc(QRectF(-r, -r, 2 * r, 2 * r), 16 * (-90 + 180 * proportion), 16 * (360 - proportion * 360));
            //�ٻ�һ�����ǵ�ˮ��
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
                pp.cubicTo(c1, c2, end);    //����������
                pp.lineTo(end.x(), 999);//999û�о��庬��,��һ�������
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
