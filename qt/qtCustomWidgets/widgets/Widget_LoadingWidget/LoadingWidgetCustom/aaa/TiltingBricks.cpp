#include "TiltingBricks.h"

TiltingBricks::TiltingBricks(QWidget* parent) : LoadingWidget(parent)
{
    m_colorList = QList<QColor> { "lightcoral", "lightblue", "khaki" };
}


void TiltingBricks::paintEvent(QPaintEvent*)
{
	//三个正方形一个接一个倾斜倒向右侧
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    const int x = width();
    const int y = height();
    painter.translate(x / 2, y / 2);

    const int cornerGap = 2;
    const int edgeLen = x / 3;//小方块边长
    const QRectF rct1(-edgeLen - cornerGap, -edgeLen - cornerGap, edgeLen, edgeLen);//左上
    const QRectF rct2(-edgeLen - cornerGap, cornerGap, edgeLen, edgeLen);//左下
    const QRectF rct3(cornerGap, cornerGap, edgeLen, edgeLen);//右下

    const QRectF baseRectList[3] = { rct1,rct2,rct3 };
    qreal ang = m_angle;
    int round = (int)ang / 90;
    if (round >= 4) round = 0;
    ang = fmod(ang, 90);
    const int rectIdx = (int)ang / 30;
    ang = fmod(ang, 30) * 3;

    painter.rotate(90 * round);
    for (int i = 0; i < 3; ++i) {
        painter.setBrush(QBrush(m_colorList[i]));
        if (i == rectIdx) {
            painter.rotate(ang);
            painter.drawRoundedRect(baseRectList[i], 4, 4);
            painter.rotate(-ang);
        }
        else {
            if (i < rectIdx) {
                painter.rotate(90);
                painter.drawRoundedRect(baseRectList[i], 4, 4);
                painter.rotate(-90);
            }
            else {
                painter.drawRoundedRect(baseRectList[i], 4, 4);
            }
        }
    }
}
