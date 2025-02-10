#include "StickCircle.h"

StickCircle::StickCircle(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("black");
    m_font = QFont("Microsoft YaHei", 7, 4);

}


void StickCircle::paintEvent(QPaintEvent* event)
{
    //12��С���ֲ���Χ,����С������ɫ��,�������ǵ�ɫ��,��ɫС��ѭ��ռȡ��ɫС����λ��
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    int x = width();
    int y = height();
    qreal ang = m_angle;

    painter.setPen(Qt::NoPen);
    painter.translate(x / 2, y / 2);
    QColor lightColor = m_color;
    lightColor.setAlphaF(0.1);

    const int stickw = x / 10;  //С���ӵĿ��
    qreal stickl = x / 4;   //С���ӵĳ���

    QColor highlight = m_color;
    const int startIdx = ang / 30;  //��ͷ����ɫС���ӵ�������
    const int arr[14] = { 0,1,2,3,4,5,6,7,8,9,10,11,0,1 };
    QList<int> hightlightList{ arr[startIdx],arr[startIdx + 1],arr[startIdx + 2] };
    QList<qreal> alphaList{ 0.5,0.75,0.99 };    //������ɫ��С���ӵ�͸����

    for (int i = 0; i < 12; ++i) 
    {
        if (hightlightList.contains(i)) 
        {
            auto hc = highlight;
            hc.setAlphaF(alphaList[0]);
            painter.setBrush(QBrush(hc));
            alphaList.pop_front();
        }
        else 
        {
            painter.setBrush(QBrush(lightColor));
        }

        painter.drawRoundedRect(QRectF(-stickw / 2, 0.375 * y - stickl / 2 - 1, stickw, stickl), stickw / 2, stickw / 2);
        auto transform = painter.transform();
        transform.rotate(30);
        painter.setTransform(transform);
    }

    painter.resetTransform();

    if (m_text == "")	return;
    QFontMetrics fm(m_font);
    qreal textw = fm.horizontalAdvance(m_text);
    qreal texth = fm.height();
    painter.setPen(m_textColor);
    painter.setFont(m_font);
    painter.drawText(QPointF((x - textw) / 2, 0.5 * y + texth / 4), m_text);
}
