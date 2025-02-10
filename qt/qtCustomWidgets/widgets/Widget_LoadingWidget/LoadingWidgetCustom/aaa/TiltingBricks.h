#ifndef TILTINGBRICKS_H
#include "LoadingWidget.h"
class TiltingBricks :public LoadingWidget 
{
public:
    explicit TiltingBricks(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif
