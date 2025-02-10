#include "LoopedRingWithText.h"

LoopedRingWithText::LoopedRingWithText(QWidget* parent) : LoadingWidget(parent)
{
    m_text = "Loading...";
    m_colorList = QList<QColor>{ "dimgray", "lightblue" };
    m_font = QFont("Microsoft YaHei", 7, 4);
}


void LoopedRingWithText::paintEvent(QPaintEvent*)
{
	//��������ȦԲ��ת��,�м���һ�������ĵƹ���������ƶ������ַ�����һ����
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const int x = width();
    const int y = height();
    //step0:����һЩ��ɫ����,Ҳ���Ըĳɳ�Ա����
    static const QColor bright(m_colorList[1]);    //������Բ����ɫ
    static const QColor medium = QColor(bright.red(), bright.green(), bright.blue(), 200);
    static const QColor dim = QColor(bright.red(), bright.green(), bright.blue(), 160);

    //step1:��һ����ɫ�ı���
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(m_colorList[0])));
    painter.drawRoundedRect(this->rect(), x / 12, x / 12);  //Բ�Ǿ���
    //step2:�������������Բ��
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

    //step3:���м������Բ��
    pen.setColor(medium);
    painter.setPen(pen);
    painter.translate(x / 2, y / 2);
    const auto rect2 = QRectF(-0.375 * x, -0.375 * y, 0.75 * x, 0.75 * y);
    if (ang > 180) ang -= 180;//���ڸĳ�180,�������ת�Ŀ�һ��
    painter.rotate(-2 * ang);
    painter.drawArc(rect2, start * 16, span * 16);
    painter.drawArc(rect2, (start + 180) * 16, span * 16);
    painter.resetTransform();

    //step4:���ڲ���4��Բ��
    pen.setColor(bright);
    painter.setPen(pen);
    painter.translate(x / 2, y / 2);
    const auto rect3 = QRectF(-0.3 * x, -0.3 * y, 0.6 * x, 0.6 * y);
    ang = m_angle;
    static const qreal t3 = 120;//���ڸĳ�120,���м�ĸ���
    while (ang > t3) ang -= t3;
    painter.rotate(ang * 90 / t3);//�ĸ�Բ��ת��90�ȵ�ʱ��Ҳ���ǳ��̽���һ��,Ҫ�����ת���ĽǶȳ��Ե���ϵ��:90/120
    qreal start0 = 15 + (90 - 15) * (ang / t3);//��ʼ��ʱ���Ϸ�Բ�������15��,�仯��90��ʱ����Ϊ0
    qreal span0 = 180 - 2 * start0;
    if (span0 > 0) {
        //��һ��
        painter.drawArc(rect3, start0 * 16, span0 * 16);
        painter.drawArc(rect3, (start0 + 180) * 16, span0 * 16);
    }
    start0 = -75 * (ang / t3);//��ʼ��ʱ��,�Ҳ�Բ�������0,����Ϊ0,������󻡳�ʱ��,�����-75��
    span0 = -start0 * 2;
    if (span0 > 0) {
        //�ڶ���
        painter.drawArc(rect3, start0 * 16, span0 * 16);
        painter.drawArc(rect3, (start0 + 180) * 16, span0 * 16);
    }
    painter.resetTransform();

    //Ϊ��step6���ı��ƶ��ƹ⣬�Ų���drawText����drawRect��ʽ
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
    //step5: �Ȼ�һ����ɫ���ı�
    painter.drawRect(rect());
    //step6: ���ı����ƶ�����
    painter.translate(0, 0.5 * y);
    const qreal unit = x / 360.0;
    QRadialGradient grad(QPointF(m_angle * unit, 0), texth);
    grad.setColorAt(0, bright);
    grad.setColorAt(1, dim);
    painter.setBrush(grad);
    painter.drawEllipse(QPointF(m_angle * unit, 0), texth, texth);
}
