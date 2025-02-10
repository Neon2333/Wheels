#ifndef RADAR_H
#define RADAR_H
#include "LoadingWidget.h"
class Radar :public LoadingWidget 
{
public:
    explicit Radar(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif