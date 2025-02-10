#include "SlinkyCircle.h"

SlinkyCircle::SlinkyCircle(QWidget* parent) :LoadingWidget(parent)
{
    m_animation.setEasingCurve(QEasingCurve::InOutCubic);
    m_color = QColor("black");
    m_font = QFont("Microsoft YaHei", 7, 4);

}


void SlinkyCircle::paintEvent(QPaintEvent* event)
{
    //可以伸缩的管子,绕着中心转动,就像弹簧圈
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    //画圆弧
    painter.setBrush(Qt::NoBrush);
    const int x = this->width();
    const int y = this->height();
    QPen pen(m_color);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(x / 20);
    painter.setPen(pen);

    painter.translate(x / 2, y / 2);

    static const qreal spanAngle = 90;//mAngle<=45,要把弧线拉伸出来
    static const qreal shrinkAngle = 360 - spanAngle;//mAngle==315时,要把弧线收缩起来

    auto arcRect = this->rect().adjusted(x / 5, y / 5, -x / 5, -y / 5);
    arcRect.translate(-x / 2, -y / 2);

    static const int direction = -1;//顺时针

    if (m_angle < spanAngle) 
    {
        painter.drawArc(arcRect, 90 * 16, m_angle * 16 * direction);
    }
    else 
    {
        //弧长是固定的
        //40 - 320 --> 320 , 280 --> 320
        if (m_angle > shrinkAngle)
        {
            painter.drawArc(arcRect, 90 * 16, -(360 - m_angle) * 16 * direction);
        }
        else 
        {
            //我转动的角度是当前角度 - 拉伸门槛,因为有收尾的不动的时间段,占据了一段角度,所以要把转动的角度拉伸一些,
            //这个比例就是 (360-spanAngle) / (shrinkAngle - spanAngle)
            const auto delta = (m_angle - spanAngle) * (360 - spanAngle) / (shrinkAngle - spanAngle);
            painter.rotate(-delta * direction);
            painter.drawArc(arcRect, 90 * 16, spanAngle * 16 * direction);
        }
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
