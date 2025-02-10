#ifndef TEXTCIRCLE_H
#define TEXTCIRCLE_H
#include "LoadingWidget.h"

class TextCircle :public LoadingWidget 
{ 
    Q_OBJECT
public:
    explicit TextCircle(QWidget* parent = nullptr, const QString& txt = "Loading...");
protected:
    void paintEvent(QPaintEvent* event);
};

#endif