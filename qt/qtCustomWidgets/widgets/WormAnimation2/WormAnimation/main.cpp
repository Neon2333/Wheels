#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Worm.h"
#include <QHBoxLayout>
#include <QLabel>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    Worm* worm = new Worm(&w);
    worm->show();
    worm->setFocus(); // ���ý���
    w.setCentralWidget(worm);

    //��ʾ֡���
    QLabel* frameIndex = new QLabel(&w);
    frameIndex->setGeometry(1400, 10, 100, 100);
    frameIndex->setFont(QFont("Microsoft Yahei", 10));
    QObject::connect(worm, &Worm::curFrameIndexChanged, frameIndex, [frameIndex](int index) {
        frameIndex->setText(QString("Frame: ") + QString::number(index));
        });
    
    w.show();
    return a.exec();
}
