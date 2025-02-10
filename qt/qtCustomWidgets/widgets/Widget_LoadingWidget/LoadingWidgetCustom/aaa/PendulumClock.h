#ifndef PENDULUMCLOCK_H
#define PENDULUMCLOCK_H
#include "LoadingWidget.h"
class PendulumClock :public LoadingWidget
{
public:
    PendulumClock(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !PENDULUMCLOCK_H