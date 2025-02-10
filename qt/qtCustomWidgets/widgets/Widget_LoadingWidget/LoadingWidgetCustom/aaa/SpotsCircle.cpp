#include "SpotsCircle.h"

SpotsCircle::SpotsCircle(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("black");
    m_font = QFont("Microsoft YaHei", 7, 4);
}

void SpotsCircle::paintEvent(QPaintEvent* event) 
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing); //���ÿ����
    int width = this->width();
    int height = this->height();
    qreal ang = m_angle;

    painter.setPen(Qt::NoPen);  //��ʹ�ñʴ�������ζ���κλ��Ƶ����������������ᱻ���Ƴ�������Ҫ����û�б߽��ͼ�Σ������ڻ����ı�ʱ��ϣ���ı����������Ƴ���
    painter.translate(width / 2, height / 2);    //translate() ���������ƶ�������ԭ�㣨����ϵͳ����һ���µ�λ��
    QColor color = m_color;
    qreal alpha = color.alphaF();
    painter.rotate(ang);    //ͨ���ڶ���֮֡��ı���ת�Ƕȣ����Դ�����ת������Ч����
    qreal rw = 1.0 / 7 * width;
    qreal r = rw / 2;
    //���㣺12-�������-360/18���ࣨ12����ռ240�㣩
    for (int i = 0; i < 12; ++i) {
        painter.setBrush(QBrush(color));
        alpha *= 0.9;
        color.setAlphaF(alpha);
        painter.drawEllipse(0, width / 2 - rw, r, r);
        r *= 0.95;
        auto transform = painter.transform();
        transform.rotate(-360 / 18);
        painter.setTransform(transform);
    }

    painter.resetTransform();

    if (m_text == "")	return;
    QFontMetrics fm(m_font);
    qreal textw = fm.horizontalAdvance(m_text);
    qreal texth = fm.height();
    painter.setPen(m_textColor);
    painter.setFont(m_font);
    painter.drawText(QPointF((width - textw) / 2, 0.5 * height + texth / 4), m_text);
}
