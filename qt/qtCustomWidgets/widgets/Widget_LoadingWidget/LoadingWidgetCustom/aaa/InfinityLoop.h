#ifndef INFINITYLOOP_H
#define INFINITYLOOP_H
#include "LoadingWidget.h"

class InfinityLoop :public LoadingWidget {//һ��������־��˫��,������һ���������޾�������
public:
    InfinityLoop(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !INFINITYLOOP_H