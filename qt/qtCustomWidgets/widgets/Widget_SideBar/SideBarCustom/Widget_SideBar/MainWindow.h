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
    QSpacerItem* placeholder_right;   //sidebar���Ҳ�ؼ���֮��հ׼��ռλ
    int placeholderRightWidth = 0; //sidebar��stackedWidget֮��ļ�࣬ͨ��placeholderռλʵ��

protected:
    void resizeEvent(QResizeEvent* ev) override;
    
    virtual void showEvent(QShowEvent* event) override;

signals:
    void hasShown();

private:
    Ui::MainWindowClass ui;

    QPainter* p;
};
