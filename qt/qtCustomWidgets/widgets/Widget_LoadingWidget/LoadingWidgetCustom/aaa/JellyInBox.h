#ifndef JELLYINBOX_H
#define JELLYINBOX_H

#include "LoadingWidget.h"
class JellyInBox :public LoadingWidget 
{
public:
    explicit JellyInBox(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event);
};

#endif