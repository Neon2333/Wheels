#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

QSlider* slider = new QSlider(this);
    slider->move(100, 100);

    //水平
    // slider->resize(300, 50);
    // slider->setOrientation(Qt::Horizontal);
    // slider->setStyleSheet("QSlider:groove:horizontal{border:1px solid #999999;height:10px;}\
    //                        QSlider::handle:horizontal{background:#fff;width:10px;margin: -3px -1px;border:1px solid #5555ff;border-top-right-radius:5px;}\
    //                        QSlider::add-page:horizontal{background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:1,stop:0 rgba(188,231,215,255),stop:1 rgba(122,215,255,255));}\
    //                        QSlider::sub-page:horizontal{background:qlineargradient(spread:pad,x1:1,y1:0.585,x2:0,y2:0,y2:0.556818,stop:0 rgba(132,76,171,255),stop:1 rgba(122,130,255,255))}");

    //垂直
    slider->resize(50, 300);
    slider->setOrientation(Qt::Vertical);
    slider->setStyleSheet("QSlider:groove:vertical{border:1px solid #999999;width:10px;}\
                           QSlider::handle:vertical{background:#fff;height:10px;margin: -1px -3px;border:1px solid #5555ff;border-top-right-radius:5px;}\
                           QSlider::add-page:vertical{background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:1,stop:0 rgba(188,231,215,255),stop:1 rgba(122,215,255,255));}\
                           QSlider::sub-page:vertical{background:qlineargradient(spread:pad,x1:1,y1:0.585,x2:0,y2:0,y2:0.556818,stop:0 rgba(132,76,171,255),stop:1 rgba(122,130,255,255))}");


}

MainWindow::~MainWindow()
{
    delete ui;
}
