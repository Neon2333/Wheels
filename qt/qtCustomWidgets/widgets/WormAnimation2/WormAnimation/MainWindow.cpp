#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->move(300, 300);

    /*animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(pos().x(), pos().y(), 100, 100));
    animation->setEndValue(QRect(pos().x(), pos().y(), frameGeometry().width(), frameGeometry().height()));
    animation->setLoopCount(1);
    animation->start();*/

    /*this->setWindowOpacity(0.0);
    animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setLoopCount(1);
    animation->start();*/

}

MainWindow::~MainWindow()
{}

void MainWindow::paintEvent(QPaintEvent* e)
{
    /*QPainter painter(this);
    QPixmap* bgPic = new QPixmap("G:\\Pictures\\BingWallpaper.jpg");    //±³¾°Í¼
    if (bgPic)
    {
        painter.drawPixmap(rect(), *bgPic);
    }*/
}
