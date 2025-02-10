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
    worm->setFocus(); // ÉèÖÃ½¹µã
    w.setCentralWidget(worm);

    QLabel* frameIndex = new QLabel(&w);
    frameIndex->setGeometry(1400, 10, 100, 100);
    frameIndex->setFont(QFont("Microsoft Yahei", 10));
    int index = 0;
    QObject::connect(worm, &Worm::firstBonePosChanged, frameIndex, [frameIndex, &index]() {
        frameIndex->setText(QString::number((index++)%10));
        });

    w.show();
    return a.exec();
}
