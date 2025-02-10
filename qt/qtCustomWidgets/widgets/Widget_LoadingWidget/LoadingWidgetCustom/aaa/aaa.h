#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_aaa.h"

class aaa : public QMainWindow
{
    Q_OBJECT

public:
    aaa(QWidget *parent = nullptr);
    ~aaa();

private:
    Ui::aaaClass ui;
};
