#include "SpotsCircle.h"

SpotsCircle::SpotsCircle(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("black");
    m_font = QFont("Microsoft YaHei", 7, 4);
}

void SpotsCircle::paintEvent(QPaintEvent* event) 
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing); //启用抗锯齿
    int width = this->width();
    int height = this->height();
    qreal ang = m_angle;

    painter.setPen(Qt::NoPen);  //不使用笔触，这意味着任何绘制的线条或轮廓都不会被绘制出来，需要绘制没有边界的图形，或者在绘制文本时不希望文本轮廓被绘制出来
    painter.translate(width / 2, height / 2);    //translate() 函数用于移动画布的原点（坐标系统）到一个新的位置
    QColor color = m_color;
    qreal alpha = color.alphaF();
    painter.rotate(ang);    //通过在动画帧之间改变旋转角度，可以创建旋转动画的效果。
    qreal rw = 1.0 / 7 * width;
    qreal r = rw / 2;
    //画点：12-点个数，-360/18点间距（12个点占240°）
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
