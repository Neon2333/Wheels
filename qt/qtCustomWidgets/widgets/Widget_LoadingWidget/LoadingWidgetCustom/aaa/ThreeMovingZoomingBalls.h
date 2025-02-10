#ifndef THREEMOVINGZOOMINGBALLS_H
#define THREEMOVINGZOOMINGBALLS_H
#include "LoadingWidget.h"
class ThreeMovingZoomingBalls :public LoadingWidget {
public:
    ThreeMovingZoomingBalls(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif