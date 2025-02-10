#include "Radar.h"

Radar::Radar(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("deepskyblue");
}


void Radar::paintEvent(QPaintEvent*)
{
	//��һ���״�һ��ɨ��,�ȴ���ʱ�����Ľ���
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const int x = width();
    const int y = height();
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_color);
    //step1: ��һ����ɫ����,�ܶ��Լ�Ľ��涼��Ҫ͸������,��һ������ɾ��
    //painter.drawRoundedRect(rect(), x / 12, x / 12);
    //step2: ��һ���״�
    painter.translate(x / 2, y / 2);
    QConicalGradient gra(QPointF(0, 0), 45);
    QColor color0 = m_color;
    QColor color1(color0.red(), color0.green(), color0.blue(), 100);
    gra.setColorAt(0, color0);
    gra.setColorAt(0.2, color1);
    gra.setColorAt(1, "transparent");
    painter.setBrush(gra);
    painter.rotate(m_angle);
    const auto rect = QRectF(-x / 4, -y / 4, x / 2, y / 2);
    painter.drawPie(rect, 45 * 16, 90 * 16);
}
