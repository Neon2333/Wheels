#ifndef SPOTSCIRCLE_H
#define SPOTSCIRCLE_H
#include "LoadingWidget.h"

class SpotsCircle :public LoadingWidget 
{
    //32������ȷֲ�������,��������תȦ,��Խ��ԽС
    Q_OBJECT
        Q_PROPERTY(qreal angle READ angle WRITE setAngle)
public:
    explicit SpotsCircle(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event);
};

#endif // !SPOTSCIRCLE_H