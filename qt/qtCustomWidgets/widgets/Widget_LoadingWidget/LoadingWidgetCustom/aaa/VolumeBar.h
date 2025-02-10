#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H
#include "LoadingWidget.h"
#include <QRandomGenerator>

class VolumeBar :public LoadingWidget
{
public:
    VolumeBar(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
private:
};

#endif // !VOLUMEBAR_H