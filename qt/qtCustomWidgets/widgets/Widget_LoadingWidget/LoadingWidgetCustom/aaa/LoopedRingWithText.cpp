#include "LoopedRingWithText.h"

LoopedRingWithText::LoopedRingWithText(QWidget* parent) : LoadingWidget(parent)
{
    m_text = "Loading...";
    m_colorList = QList<QColor>{ "dimgray", "lightblue" };
    m_font = QFont("Microsoft YaHei", 7, 4);
}


void LoopedRingWithText::paintEvent(QPaintEvent*)
{
	//外面有三圈圆环转动,中间有一个高亮的灯光从左向右移动照亮字符串的一部分
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const int x = width();
    const int y = height();
    //step0:定义一些颜色变量,也可以改成成员变量
    static const QColor bright(m_colorList[1]);    //最亮的圆环颜色
    static const QColor medium = QColor(bright.red(), bright.green(), bright.blue(), 200);
    static const QColor dim = QColor(bright.red(), bright.green(), bright.blue(), 160);

    //step1:画一个深色的背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(m_colorList[0])));
    painter.drawRoundedRect(this->rect(), x / 12, x / 12);  //圆角矩形
    //step2:画最外面的两个圆环
    painter.translate(x / 2, y / 2);
    QPen pen(dim);
    pen.setWidth(int(0.04 * x));
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    const auto rect1 = QRectF(-0.45 * x, -0.45 * y, 0.9 * x, 0.9 * y);

    static const qreal start = 30;
    static const qreal span = 120;
    auto ang = m_angle;
    painter.rotate(ang);
    painter.drawArc(rect1, start * 16, span * 16);
    painter.drawArc(rect1, (start + 180) * 16, span * 16);
    painter.resetTransform();

    //step3:画中间的两个圆环
    pen.setColor(medium);
    painter.setPen(pen);
    painter.translate(x / 2, y / 2);
    const auto rect2 = QRectF(-0.375 * x, -0.375 * y, 0.75 * x, 0.75 * y);
    if (ang > 180) ang -= 180;//周期改成180,比外面的转的快一倍
    painter.rotate(-2 * ang);
    painter.drawArc(rect2, start * 16, span * 16);
    painter.drawArc(rect2, (start + 180) * 16, span * 16);
    painter.resetTransform();

    //step4:画内部的4个圆环
    pen.setColor(bright);
    painter.setPen(pen);
    painter.translate(x / 2, y / 2);
    const auto rect3 = QRectF(-0.3 * x, -0.3 * y, 0.6 * x, 0.6 * y);
    ang = m_angle;
    static const qreal t3 = 120;//周期改成120,比中间的更快
    while (ang > t3) ang -= t3;
    painter.rotate(ang * 90 / t3);//四个圆环转过90度的时候也就是长短交替一次,要把这个转过的角度乘以调整系数:90/120
    qreal start0 = 15 + (90 - 15) * (ang / t3);//开始的时候上方圆环起点在15度,变化到90度时弧长为0
    qreal span0 = 180 - 2 * start0;
    if (span0 > 0) {
        //第一组
        painter.drawArc(rect3, start0 * 16, span0 * 16);
        painter.drawArc(rect3, (start0 + 180) * 16, span0 * 16);
    }
    start0 = -75 * (ang / t3);//开始的时候,右侧圆环起点是0,弧长为0,它的最大弧长时刻,起点在-75度
    span0 = -start0 * 2;
    if (span0 > 0) {
        //第二组
        painter.drawArc(rect3, start0 * 16, span0 * 16);
        painter.drawArc(rect3, (start0 + 180) * 16, span0 * 16);
    }
    painter.resetTransform();

    //为了step6的文本移动灯光，才不用drawText而用drawRect方式
    painter.setFont(m_font);
    QFontMetrics fm(m_font);
    static const QString text(m_text);
    qreal textw = fm.horizontalAdvance(text);
    qreal texth = fm.height();
    QPainterPath pp;
    pp.addText(QPointF((x - textw) / 2, 0.5 * y + texth / 4), m_font, text);
    painter.setClipPath(pp);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(dim));
    //step5: 先画一个淡色的文本
    painter.drawRect(rect());
    //step6: 画文本的移动高亮
    painter.translate(0, 0.5 * y);
    const qreal unit = x / 360.0;
    QRadialGradient grad(QPointF(m_angle * unit, 0), texth);
    grad.setColorAt(0, bright);
    grad.setColorAt(1, dim);
    painter.setBrush(grad);
    painter.drawEllipse(QPointF(m_angle * unit, 0), texth, texth);
}
