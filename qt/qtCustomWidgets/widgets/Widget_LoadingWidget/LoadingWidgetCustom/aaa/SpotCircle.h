#ifndef SPOTCIRCLE_H
#define SPOTCIRCLE_H
#include "LoadingWidget.h"


class SpotCircle : public LoadingWidget
{
    Q_OBJECT
        Q_PROPERTY(qreal angle READ angle WRITE setAngle)
public:
    explicit SpotCircle(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
};


#endif // !SPOTCIRCLE_H