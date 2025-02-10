#ifndef TUBEGRADIANTCIRCLE_H
#define TUBEGRADIANTCIRCLE_H
#include "LoadingWidget.h"

class TubeGradiantCircle :public LoadingWidget 
{
    Q_OBJECT
        Q_PROPERTY(qreal angle READ angle WRITE setAngle)
public:
    explicit TubeGradiantCircle(QWidget* parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent* event) override;

};

#endif // !TUBECIRCLE_H