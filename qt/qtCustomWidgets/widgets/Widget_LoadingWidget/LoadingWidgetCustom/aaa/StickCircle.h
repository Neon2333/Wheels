#ifndef STICKYCIRCLE_H
#define STICKYCIRCLE_H
#include "StickCircle.h"
#include "LoadingWidget.h"

class StickCircle :public LoadingWidget
{
    Q_OBJECT
        Q_PROPERTY(qreal angle READ angle WRITE setAngle)
public:
    explicit StickCircle(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event);
};

#endif // STICKYCIRCLE_H