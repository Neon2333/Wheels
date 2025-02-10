#include "JellyInBox.h"

JellyInBox::JellyInBox(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor>{ "grey" , "lightblue"};
}


void JellyInBox::paintEvent(QPaintEvent* event)
{
	//һ���������Ĺ�����һ��С��������,һ��ʼ����,Ȼ���ƶ�,Ȼ������
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);

    int x = this->width();
    const int y = this->height();

    //�Ȼ�һ������
    QPen pen(m_colorList[0]);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawRoundedRect(QRectF(1, 0.4375 * y, x - 2, y / 8), y / 16.0, y / 16.0);

    //������
    pen.setColor(m_colorList[1]);
    pen.setCapStyle(Qt::RoundCap);
    painter.setBrush(Qt::NoBrush);

    const int gap = 4;//�����ͺ���֮��ļ��
    const int boxGap = 1;//���ӵ�����
    const qreal jh = y / 8 - gap * 2;//�����߶�
    pen.setWidthF(jh);
    painter.setPen(pen);

    painter.translate(boxGap + gap + jh / 2, y / 2);
    x -= (boxGap + gap) * 2 + jh;//�����ƶ���x��Χ���ܿ�� - ���ߵ�������� - ��ͷ���
    const qreal maxw = 0.4 * x;//���Ĺ������
    int jx = 0;
    qreal jw = 0;

    if (m_angle < 90) {
        jw = maxw * m_angle / 90;
    }
    else if (m_angle < 270) {
        jw = maxw;
        jx = (x - maxw) * (m_angle - 90) / 180;
    }
    else {
        jx = x - maxw + (m_angle - 270) / 90 * maxw;
        jw = x - jx;
    }
    painter.drawLine(jx, 0, jx + jw, 0);
}
