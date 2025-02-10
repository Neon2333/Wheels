#ifndef EXPANDINGSCROLL_H
#define EXPANDINGSCROLL_H

#include "LoadingWidget.h"
class ExpandingScroll :public LoadingWidget 
{
public:
    ExpandingScroll(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !EXPANDINGSCROLL_H
