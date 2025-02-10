#include "mainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(300, 300);
    w.show();
    return a.exec();
}
