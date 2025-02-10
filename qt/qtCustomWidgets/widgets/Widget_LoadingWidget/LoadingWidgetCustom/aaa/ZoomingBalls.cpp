#include "ZoomingBalls.h"

ZoomingBalls::ZoomingBalls(QWidget* parent):LoadingWidget(parent)
{
    m_colorList = QList<QColor>{ "#3BB6FE", "#3BB6FE", "#3BB6FE", "#3BB6FE", "#3BB6FE" };
}


void ZoomingBalls::paintEvent(QPaintEvent* event)
{
	//���С��,ÿ�����α��
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    const int x = width();
    const int y = height();
    const qreal r = x / 24;    //С��İ뾶
    const qreal rmax = x / 10;  //С�����뾶
    const qreal alphaSpace = 0.8; //С����ɫ�仯��Χ
    static const int startAngle[5] = { 0,45,90,135,180 };//���С��ʼ�仯ʱ���
    painter.translate(x / 6, y / 2);

    for (int i = 0; i < m_colorList.size(); ++i) 
    {
        const auto start = startAngle[i];
        qreal delta = m_angle - start;

        QColor background = m_colorList[i];
        if (delta > 0 && delta < 180)
        {
            if (delta > 90) delta = 180 - delta;
            qreal ratio = delta / 90.0;
            qreal alpha = 1 - ratio * alphaSpace;
            qreal radius = r + ratio * (rmax - r);
            background.setAlphaF(alpha);
            painter.setBrush(QBrush(background));
            painter.drawEllipse(QPointF(0, 0), radius, radius);
        }
        else 
        {
            //����
            painter.setBrush(QBrush(background));
            painter.drawEllipse(QPointF(0, 0), r, r);
        }
        painter.translate(x / 6.0, 0);
    }
}
