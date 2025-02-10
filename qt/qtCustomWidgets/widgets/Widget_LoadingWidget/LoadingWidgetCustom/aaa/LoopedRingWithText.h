#ifndef LOOPEDRINGWITHTEXT_H
#define LOOPEDRINGWITHTEXT_H
#include "LoadingWidget.h"
class LoopedRingWithText :public LoadingWidget 
{
public:
    explicit LoopedRingWithText(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !LOOPEDRINGWITHTEXT_H
