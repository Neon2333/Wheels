#include "RhombusShift.h"

RhombusShift::RhombusShift(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor> { "lightblue" , "cadetblue" , "lightblue" , "cadetblue" };
}

void RhombusShift::paintEvent(QPaintEvent* )
{
	//做斜向平移的四个菱形
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    const int x = width();
    const int y = height();
    const int cornerGap = 4; //菱形内部顶点和中心点的距离
    const int edgeGap = 2;   //菱形顶点和外边框的距离
    const qreal edgeLen = (x / 2 - cornerGap - edgeGap) / 1.42; // 菱形的边长
    const int halfDiagonalx = (x / 2 - edgeGap - cornerGap) / 2;    //水平方向一半对角线长度
    const int halfDiagonaly = (y / 2 - edgeGap - cornerGap) / 2;    //垂直方向一半对角线长度
    const QPointF point1(x / 2, edgeGap + halfDiagonaly);           //上方
    const QPointF point2(x / 2 + cornerGap + halfDiagonalx, y / 2); //右侧
    const QPointF point3(x / 2, y / 2 + cornerGap + halfDiagonaly); //下方
    const QPointF point4(edgeGap + halfDiagonalx, y / 2);          //左侧
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
    const int staticTime = 15;   //每次移动到四个节点上面,要静止一段时间,这个值在0-90之间
    for (int i = 0; i < 4; ++i) {
        qreal proportion = 0;
        const auto rest = fmod(m_angle, 90);//余数
        const auto quotient = (int)m_angle / 90 * 0.25;//商
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
