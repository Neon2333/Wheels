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

    QWidget* fixedBar;
    QVBoxLayout* vlay_fixedBar;
    QSpacerItem* placeholder_fixedBar;   


    SideBar* sidebar;
    QStackedWidget* stackedWidget;
    QWidget* container;
    QHBoxLayout* hlay;
    QSpacerItem* placeholder_right;   //sidebar和右侧控件的之间空白间距占位
    int placeholderRightWidth = 0; //sidebar和stackedWidget之间的间距，通过placeholder占位实现

protected:
    void resizeEvent(QResizeEvent* ev) override;
    
    virtual void showEvent(QShowEvent* event) override;

signals:
    void hasShown();

private:
    Ui::MainWindowClass ui;

    QPainter* p;
};
