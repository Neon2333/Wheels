#ifndef RHOMBUSSHIFT_H
#define RHOMBUSSHIFT_H
#include "LoadingWidget.h"
class RhombusShift :public LoadingWidget 
{
public:
    explicit RhombusShift(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !RHOMBUSSHIFT_H
