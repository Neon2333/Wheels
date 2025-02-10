#include "FourRotatingFireBall.h"

FourRotatingFireBall::FourRotatingFireBall(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor>{ "lightblue" , "lightpink" };
    m_font = QFont("Microsoft YaHei", 7, 4);
}

void FourRotatingFireBall::paintEvent(QPaintEvent*)
{
	//四个旋转的火球,说他是火球是因为快速转动的时候它有残影,看上去像弧线
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const qreal x = width();
    const qreal y = height();
    const qreal r = 0.4 * y;
    const qreal maxArc = 30;
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(int(0.06*x));
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    for (int i = 0; i < 4; ++i) {
        painter.resetTransform();
        painter.translate(x / 2, y / 2);
        painter.rotate(90 * i);
        if (i % 2 == 0) 
        {
            pen.setColor(m_colorList[0]);
            painter.setPen(pen);
        }
        else 
        {
            pen.setColor(m_colorList[1]);
            painter.setPen(pen);
        }
        if (m_angle < 30) 
        { //启动火球,画出弧线
            qreal ratio = m_angle / 30;
            painter.drawArc(QRectF(-r, -r, 2 * r, 2 * r), 16 * 90, 16 * -ratio * maxArc);
        }
        else if (m_angle < 330)
        {//转动两圈
            qreal ratio = (m_angle - 30) / 300;
            painter.rotate((720 - maxArc) * ratio);
            painter.drawArc(QRectF(-r, -r, 2 * r, 2 * r), 16 * 90, 16 * -maxArc);
        }
        else 
        {//收起弧线
            qreal ratio = (m_angle - 330) / 30;
            painter.drawArc(QRectF(-r, -r, 2 * r, 2 * r), 16 * 90, 16 * (1 - ratio) * maxArc);
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
