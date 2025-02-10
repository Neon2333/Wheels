#ifndef INFINITYLOOP_H
#define INFINITYLOOP_H
#include "LoadingWidget.h"

class InfinityLoop :public LoadingWidget {//一个无穷大标志的双环,上面有一个行星在无尽地绕行
public:
    InfinityLoop(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !INFINITYLOOP_H