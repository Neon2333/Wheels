#ifndef PACMAN_H
#define PACMAN_H
#include "LoadingWidget.h"
class Pacman :public LoadingWidget
{
public:
    Pacman(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // !PACMAN_H