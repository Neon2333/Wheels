#ifndef FOURROTATINGfIREBALL_H
#define FOURROTATINGfIREBALL_H
#include "LoadingWidget.h"

class FourRotatingFireBall :public LoadingWidget
{
public:
    FourRotatingFireBall(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !FOURROTATINGfIREBALL_H
