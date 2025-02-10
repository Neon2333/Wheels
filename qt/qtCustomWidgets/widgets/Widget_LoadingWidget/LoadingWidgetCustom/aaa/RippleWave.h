#ifndef RIPPLEWAVE_H
#define RIPPLEWAVE_H
#include "LoadingWidget.h"

class RippleWave :public LoadingWidget 
{
    Q_OBJECT
public:
    explicit RippleWave(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event);
};

#endif // !RIPPLEWAVE_H
