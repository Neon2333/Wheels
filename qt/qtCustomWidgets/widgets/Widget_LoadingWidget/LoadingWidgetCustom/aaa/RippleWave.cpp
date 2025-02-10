#include "RippleWave.h"

RippleWave::RippleWave(QWidget* parent) : LoadingWidget(parent)
{
    m_color = QColor("black");
}

void RippleWave::paintEvent(QPaintEvent* event)
{
    //8层波纹,从中间逐渐向外变亮,然后变暗
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);
    QPen pen(m_color);
    const int x = this->width();
    const int y = this->height();
    if (x < 150)
    {
        pen.setWidth(2);
    }
    else
    {
        pen.setWidth(3);
    }
    //每层波浪的生命周期是6个单位,一共有八层,每层开始时间是前一层波浪的一个单位之后,时间共分为14个单位
    //static const int arr[8] = { 10,15,22,31,42,55,70,87 };//波浪的半径
    static const qreal arr[8] = { (qreal)x/20, (qreal)x/13, (qreal)x/9, x/6.45, x/4.76, x/3.63, x/2.85, x/2.3 };//波浪的半径
    static const qreal unit = 360.0 / 14;
    static const qreal startArr[8] = { 0,unit,unit * 2 , unit * 3 ,unit * 4,unit * 5,unit * 6,unit * 7 };
    static const qreal lifeSpan = unit * 6;
    painter.translate(x / 2, y / 2);

    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) 
    {
        const auto start = startArr[i];
        const auto delta = m_angle - start;
        qreal alpha = 1;
        if (delta > 0 && delta < lifeSpan) 
        {
            if (delta < unit * 2) alpha = delta / (unit * 2);
            if (delta > unit * 4) alpha = (lifeSpan - delta) / (unit * 2);
            QColor c(m_color);
            c.setAlphaF(alpha);
            pen.setColor(c);
            painter.setPen(pen);
            painter.drawEllipse(QPointF(0, 0), arr[i], arr[i]);
        }
        else 
        {
            //什么都不用做
        }
    }
}
