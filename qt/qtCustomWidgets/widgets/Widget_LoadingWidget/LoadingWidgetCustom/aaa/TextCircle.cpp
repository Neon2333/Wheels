#include "TextCircle.h"

TextCircle::TextCircle(QWidget* parent, const QString& txt) : LoadingWidget(parent)
{
    m_color = QColor("black");
    m_font = QFont("Microsoft YaHei", 6, 4);
}


void TextCircle::paintEvent(QPaintEvent* event)
{
    //һ���ı�����������ת
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int x = width();
    int y = height();

    QPen pen(m_textColor);
    pen.setWidth(4);
    painter.setPen(pen);

    painter.translate(x / 2, y / 2);
    painter.rotate(m_angle);

    for (int i = 0; i < m_text.length(); ++i) {
        const QString s = QString(m_text[i]);
        painter.drawText(QRect(-10, y / 2 - 22, 20, 20), Qt::AlignTop, s);//���·���һ���ַ�
        painter.rotate(-8);//ÿ���ַ�֮����8��
    }


}

