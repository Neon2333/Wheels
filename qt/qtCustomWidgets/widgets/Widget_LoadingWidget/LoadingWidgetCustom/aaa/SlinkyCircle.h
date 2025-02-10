#ifndef SLINKYCIRCLE_H
#define SLINKYCIRCLE_H
#include "LoadingWidget.h"

class SlinkyCircle :public LoadingWidget
{
    Q_OBJECT
public:
    explicit SlinkyCircle(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event);
};

#endif // !SLINKYCIRCLE_H
