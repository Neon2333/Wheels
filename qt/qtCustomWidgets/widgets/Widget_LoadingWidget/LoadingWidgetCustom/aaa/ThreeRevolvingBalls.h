#ifndef THREEREVOLVINGBALLS_H
#define THREEREVOLVINGBALLS_H
#include "LoadingWidget.h"
class ThreeRevolvingBalls :public LoadingWidget
{
public:
    ThreeRevolvingBalls(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !THREEREVOLVINGBALLS_H