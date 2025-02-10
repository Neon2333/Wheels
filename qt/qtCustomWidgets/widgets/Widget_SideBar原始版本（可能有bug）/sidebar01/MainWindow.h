#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "SideBar.h"
#include <QStackedWidget >
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QPainter>
#include <QPalette>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    SideBar* sidebar;
    QStackedWidget* stackedWidget;
    QWidget* container;
    QHBoxLayout* hlay;
    QSpacerItem* placeholder;
    int placeholderWidth = 50; //sidebar和stackedWidget之间的间距，通过placeholder占位实现

protected:
    void resizeEvent(QResizeEvent* ev);
private:
    Ui::MainWindowClass ui;

    QPainter* p;

};
