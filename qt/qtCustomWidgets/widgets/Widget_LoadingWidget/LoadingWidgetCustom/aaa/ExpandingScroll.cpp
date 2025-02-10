#include "ExpandingScroll.h"

ExpandingScroll::ExpandingScroll(QWidget* parent) :LoadingWidget(parent)
{
    m_textColor = QColor("black");
    m_color = QColor("burlywood");
    m_text = "loading";
    setFont(QFont("Microsoft YaHei", 16, 2));
}


void ExpandingScroll::paintEvent(QPaintEvent*)
{
	//一个圆环转动两圈之后像卷轴一样展示"正在加载"
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    qreal x = width();
    qreal y = height();
    painter.translate(x / 2, y / 2);
    painter.setBrush(Qt::NoBrush);
    QPen pen(m_textColor);
    qreal penWidth = 4;
    if (x < 100 || y < 100)
    {
        penWidth = 2;
    }
    pen.setWidthF(penWidth);
    painter.setPen(pen);
    x -= 4;
    y -= 4;
    const auto ang = m_angle;

    const int arr[9] = { 20,30,60,90,150,180,210,275,345 };//9个时间节点,分割下面10个分支

    if (ang < arr[0]) {//中间的竖线转变为半圆弧线
        const qreal h = 0.25 * x;
        painter.drawLine(0, h / 2 - ang / arr[0] * h, 0, -h / 2);
        painter.drawArc(QRectF(0, -1.5 * h, 2 * h, 2 * h), 180 * 16, -180 * 16 * ang / arr[0]);
    }
    else if (ang < arr[1]) {//半圆弧线转变为四分之一圆弧和右侧的小竖线
        const qreal h = 0.25 * x;
        const qreal ratio = (ang - arr[0]) / (arr[1] - arr[0]);
        qreal start = 180 - 90 * ratio;

        painter.drawArc(QRectF(0, -1.5 * h, 2 * h, 2 * h), start * 16, -start * 16);
        painter.drawLine(x / 2, -h / 2, x / 2, -h / 2 + h / 2 * ratio);
    }
    else if (ang < arr[2]) {//剩下的上方的四分之一圆弧转为大的下方的八分之一圆弧
        const qreal h = 0.25 * x;
        const qreal ratio = (ang - arr[1]) / (arr[2] - arr[1]);
        qreal start = 90 - 90 * ratio;
        painter.drawArc(QRectF(0, -1.5 * h, 2 * h, 2 * h), start * 16, -start * 16);
        painter.drawLine(x / 2, -h / 2, x / 2, 0);
        painter.drawArc(QRectF(-x / 2, -y / 2, x, y), 0, -45 * 16 * ratio);
    }
    else if (ang < arr[3]) {//小竖线转为下方的大的八分之一圆弧
        const qreal h = x / 8;
        qreal ratio = (ang - arr[2]) / (arr[3] - arr[2]);
        painter.drawLine(x / 2, -h * (1 - ratio), x / 2, 0);
        painter.drawArc(QRectF(-x / 2, -y / 2, x, y), 0, -(45 + 45 * ratio) * 16);
    }
    else if (ang < arr[4]) {//大圆弧转两圈
        qreal ratio = (ang - arr[3]) / (arr[4] - arr[3]);
        painter.rotate(720 * ratio);
        painter.drawArc(QRectF(-x / 2, -y / 2, x, y), 0, -90 * 16);
    }
    else if (ang < arr[5]) {//大圆弧转为竖线
        qreal ratio = (ang - arr[4]) / (arr[5] - arr[4]);
        painter.drawArc(QRectF(-x / 2, -y / 2, x, y), -90 * ratio * 16, -90 * (1 - ratio) * 16);
        painter.drawLine(0, y / 2, 0, y / 2 - 0.625 * ratio * y);
    }
    else if (ang < arr[6]) {//竖线缩小一下
        qreal ratio = (ang - arr[5]) / (arr[6] - arr[5]);
        painter.drawLine(0, y / 2 - 0.375 * y * ratio, 0, -0.125 * y);
    }
    else if (ang < arr[7]) {//展开卷轴
        qreal ratio = (ang - arr[6]) / (arr[7] - arr[6]);
        QPainterPath pp;
        pp.addRect(QRectF(-0.375 * x * ratio, -0.125 * y, 0.75 * x * ratio, y / 4).adjusted(
            penWidth / -2, penWidth / -2, penWidth / 2, penWidth / 2));
        painter.setClipPath(pp);
        const auto rct = QRectF(-0.375 * x, -0.125 * y, 0.75 * x, y / 4);

        painter.setBrush(QBrush(m_color));
        painter.drawRoundedRect(rct, 4, 4);
        painter.drawText(rct, Qt::AlignCenter, m_text);
    }
    else if (ang < arr[8]) {//展示一小段时间
        const auto rct = QRectF(-0.375 * x, -0.125 * y, 0.75 * x, y / 4);
        painter.setBrush(QBrush(m_color));
        painter.drawRoundedRect(rct, 4, 4);
        painter.drawText(rct, Qt::AlignCenter, m_text);
    }
    else 
    {
        //收起卷轴
        qreal ratio = (ang - arr[8]) / (360 - arr[8]);
        QPainterPath pp;
        pp.addRect(QRectF(-0.375 * x * (1 - ratio), -0.125 * y, 0.75 * x * (1 - ratio), y / 4).adjusted(
            penWidth / -2, penWidth / -2, penWidth / 2, penWidth / 2));
        painter.setClipPath(pp);
        const auto rct = QRectF(-0.375 * x, -0.125 * y, 0.75 * x, y / 4);
        painter.setBrush(QBrush(m_color));
        painter.drawRoundedRect(rct, 4, 4);
        painter.drawText(rct, Qt::AlignCenter, m_text);
    }
}
