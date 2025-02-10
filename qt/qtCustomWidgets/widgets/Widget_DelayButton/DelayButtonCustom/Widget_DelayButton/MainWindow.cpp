#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    DelayButton* btn = new DelayButton(this);
    btn->resize(96, 96);
    btn->move(100, 100);
    //btn->icon_normal = QIcon(":/MainWindow/biliTV_96_96.png");

    QPushButton* btn2 = new QPushButton(this);
    btn2->move(300, 300);
    btn2->resize(100, 100);
    connect(btn2, &QPushButton::clicked, this, [this,btn]() {
        btn->setUnchecked();
        });
}

MainWindow::~MainWindow()
{}
