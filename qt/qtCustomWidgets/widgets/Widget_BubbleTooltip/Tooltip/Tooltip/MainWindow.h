#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include <QPushButton>
#include "BubbleTipsWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;

    QPushButton* button;
    QPushButton* button1;
    BubbleTipsWidget* tips;

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};
