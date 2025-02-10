#include "SpotCircle.h"

SpotCircle::SpotCircle(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("black");
    m_font = QFont("Microsoft YaHei", 6, 4);
}

void SpotCircle::paintEvent(QPaintEvent* event) 
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    int width = this->width();
    int height = this->height();

    painter.setPen(Qt::NoPen);
    painter.translate(width / 2, height / 2);
    QColor color = m_color;
    qreal alpha = color.alphaF();
    painter.rotate(m_angle);
    for (int i = 0; i < 16; ++i) 
    {
        qreal rw = 1.0 / 8 * width;
        qreal r = rw / 2;
        painter.setBrush(QBrush(color));
        alpha *= 0.8;
        color.setAlphaF(alpha);
        painter.drawEllipse(0, width / 2 - rw, r, r);
        auto transform = painter.transform();
        transform.rotate(-2);
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
