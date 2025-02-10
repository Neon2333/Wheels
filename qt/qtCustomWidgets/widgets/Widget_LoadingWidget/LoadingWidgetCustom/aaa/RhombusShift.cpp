#include "RhombusShift.h"

RhombusShift::RhombusShift(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor> { "lightblue" , "cadetblue" , "lightblue" , "cadetblue" };
}

void RhombusShift::paintEvent(QPaintEvent* )
{
	//��б��ƽ�Ƶ��ĸ�����
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    const int x = width();
    const int y = height();
    const int cornerGap = 4; //�����ڲ���������ĵ�ľ���
    const int edgeGap = 2;   //���ζ������߿�ľ���
    const qreal edgeLen = (x / 2 - cornerGap - edgeGap) / 1.42; // ���εı߳�
    const int halfDiagonalx = (x / 2 - edgeGap - cornerGap) / 2;    //ˮƽ����һ��Խ��߳���
    const int halfDiagonaly = (y / 2 - edgeGap - cornerGap) / 2;    //��ֱ����һ��Խ��߳���
    const QPointF point1(x / 2, edgeGap + halfDiagonaly);           //�Ϸ�
    const QPointF point2(x / 2 + cornerGap + halfDiagonalx, y / 2); //�Ҳ�
    const QPointF point3(x / 2, y / 2 + cornerGap + halfDiagonaly); //�·�
    const QPointF point4(edgeGap + halfDiagonalx, y / 2);          //���
    const QList<QPointF> pointList{ point1,point2,point3,point4,point1,point2,point3,point4 };

    QPainterPath pathList[4];
    for (int i = 0; i < 4; ++i) {
        auto& path = pathList[i];
        path.moveTo(pointList[i]);
        path.lineTo(pointList[i + 1]);
        path.lineTo(pointList[i + 2]);
        path.lineTo(pointList[i + 3]);
        path.lineTo(pointList[i + 4]);
    }
    const int staticTime = 15;   //ÿ���ƶ����ĸ��ڵ�����,Ҫ��ֹһ��ʱ��,���ֵ��0-90֮��
    for (int i = 0; i < 4; ++i) {
        qreal proportion = 0;
        const auto rest = fmod(m_angle, 90);//����
        const auto quotient = (int)m_angle / 90 * 0.25;//��
        if (rest > 90 - staticTime) proportion = quotient + 0.25;
        else proportion = rest / (90 - staticTime) * 0.25 + quotient;
        const QPointF center = pathList[i].pointAtPercent(proportion);
        painter.translate(center);
        painter.rotate(45);
        painter.setBrush(QBrush(m_colorList[i]));
        painter.drawRect(-edgeLen / 2, -edgeLen / 2, edgeLen, edgeLen);
        painter.resetTransform();
    }

}
