#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QPropertyAnimation>
#include <QPainter>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void paintEvent(QPaintEvent* e) override;

private:
    Ui::MainWindowClass ui;

    QPropertyAnimation* animation;
};
