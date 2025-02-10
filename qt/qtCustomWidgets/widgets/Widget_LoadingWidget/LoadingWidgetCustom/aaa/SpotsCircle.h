#ifndef SPOTSCIRCLE_H
#define SPOTSCIRCLE_H
#include "LoadingWidget.h"

class SpotsCircle :public LoadingWidget 
{
    //32个球均匀分布在四周,绕着中心转圈,球越来越小
    Q_OBJECT
        Q_PROPERTY(qreal angle READ angle WRITE setAngle)
public:
    explicit SpotsCircle(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event);
};

#endif // !SPOTSCIRCLE_H