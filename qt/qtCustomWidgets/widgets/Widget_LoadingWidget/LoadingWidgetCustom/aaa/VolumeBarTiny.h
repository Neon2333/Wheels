#ifndef VOLUMEBARTINY_H
#define VOLUMEBARTINY_H
#include "LoadingWidget.h"

class VolumeBarTiny :public LoadingWidget 
{
public:
    VolumeBarTiny(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
private:
};

#endif