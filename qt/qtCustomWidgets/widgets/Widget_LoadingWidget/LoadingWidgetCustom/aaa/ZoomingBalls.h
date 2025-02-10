#ifndef ZOOMINGBALLS_H
#define ZOOMINGBALLS_H
#include "LoadingWidget.h"

class ZoomingBalls :public LoadingWidget
{
    Q_OBJECT
public:
    explicit ZoomingBalls(QWidget* parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // !ZOOMINGBALLS_H