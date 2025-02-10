#include "Hourglass.h"

Hourglass::Hourglass(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor>{ "lightslategray", "lightblue" };
    m_columnVisible = false;
}

void Hourglass::setColumnVisibility(bool vis)
{
    m_columnVisible = vis;
}


void Hourglass::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const qreal x = width();
    const qreal y = height();
    //step1: �Ȼ���������ƿ��
    qreal ang = (m_angle - 320) / 40;//��320�ȵ�ʱ��Ҫ��תƿ��
    if (ang > 1) ang = 1;
    if (ang < 0) ang = 0;
    ang *= 180;
    QPen pen(m_colorList[0]);//�һ�ɫ��ƿ��
    pen.setWidth(16);
    pen.setCapStyle(Qt::RoundCap);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);

    painter.translate(x / 2, y / 2);
    painter.rotate(ang);
    painter.drawLine(-x / 4, -0.375 * y, x / 4, -0.375 * y);//�Ϸ�ƿ��
    painter.drawLine(-x / 4, 0.375 * y, x / 4, 0.375 * y);//  �·�ƿ��
    //step2: ��һ��ƿ��
    QPainterPath pp;
    const int gap1 = 8;//ƿ������ķ�֮һˮƽλ�õļ��,���ֵԽ��,ɳ©Խ��
    QPointF start(-x / 4 + gap1, -0.375 * y);
    QPointF end(-x / 32, 0);
    QPointF c1(start.x(), end.y());
    QPointF c2(end.x(), end.y() + 0.4 * (start.y() - end.y()));
    pp.moveTo(start);
    pp.cubicTo(c1, c2, end);

    const qreal penWidth = 6;
    pen.setWidthF(penWidth);
    painter.setPen(pen);
    painter.drawPath(pp);//ƿ���������ϲ���
    painter.rotate(180);
    painter.drawPath(pp);//����
    painter.rotate(-180);
    painter.scale(1, -1);
    painter.drawPath(pp);//����
    painter.rotate(180);
    painter.drawPath(pp);//����

    //step3: ������С����(��ѡ)
    if (m_columnVisible)
    {
        pen.setWidthF(4);
        painter.setPen(pen);
        painter.drawLine(-x / 4, start.y(), -x / 4, -start.y());
        painter.drawLine(x / 4, start.y(), x / 4, -start.y());
    }

    painter.resetTransform();
    painter.translate(x / 2, y / 2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_colorList[1]));
    if (m_angle < 320) 
    { 
        //step4: ����̬��ɳ��
        //�������ɳ��
        QPainterPath sand;
        start.setX(start.x() + penWidth / 2);//ɳ������Ҫ��һ��,��ø�ס��ƿ��
        end.setX(end.x() + penWidth / 2);    //ɳ������Ҫ��һ��,��ø�ס��ƿ��
        c1.setX(c1.x() + penWidth / 2);      //ɳ������Ҫ��һ��,��ø�ס��ƿ��
        c2.setX(c2.x() + penWidth / 2);      //ɳ������Ҫ��һ��,��ø�ס��ƿ��

        sand.moveTo(start);
        sand.cubicTo(c1, c2, end);
        sand.lineTo(0, (0.33 - 0.2 * m_angle / 320) * y);
        sand.lineTo(QPointF(end.x() * -1, end.y()));
        sand.cubicTo(QPointF(-c2.x(), c2.y()), QPointF(-c1.x(), c1.y()), QPointF(-start.x(), start.y()));
        sand.lineTo(start);
        painter.setClipPath(sand);
        painter.drawRect(QRectF(-x / 2, -y / 4 + m_angle / 320 * y * 0.38, x, x));

        //�������ɳ��, һ������������
        QPointF a(start.x() * m_angle / 320, 0.33 * y);
        QPointF top(0, (0.33 - m_angle / 320 * 0.2) * y);
        QPointF b(-a.x(), a.y());
        sand.moveTo(a);
        sand.lineTo(top);
        sand.lineTo(b);
        sand.closeSubpath();
        painter.setClipPath(sand);
        painter.drawRect(-x / 2, top.y(), x, x);//����߶Ȳ���̫����,�����������ɳ��Ҳ������
    }
    else {
        //��תɳ��
        QPainterPath pp;
        pp.moveTo(QPointF(start.x() + penWidth / 2, 0.33 * y));
        pp.lineTo(0, 0.13 * y);
        pp.lineTo(QPointF(-start.x() - penWidth / 2, 0.33 * y));
        pp.closeSubpath();
        QTransform bottoleTrans;
        bottoleTrans.rotate(ang);
        painter.setClipPath(bottoleTrans.map(pp));
        painter.drawRect(QRectF(-x / 2, -x / 2, x, x));
    }
}
