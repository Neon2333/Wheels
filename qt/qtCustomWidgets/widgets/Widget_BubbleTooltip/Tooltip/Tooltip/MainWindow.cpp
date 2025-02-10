#include "mainWindow.h"
#include <QHoverEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setMouseTracking(true);

    button = new QPushButton(this);
    button->move(0, 0);
    button->resize(100, 50);
    button->setText("tool button");
    button->installEventFilter(this);

    button1 = new QPushButton(this);
    button1->move(400, 400);
    button1->resize(100, 50);
    button1->setText("test");
    button1->installEventFilter(this);
}

MainWindow::~MainWindow()
{}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == tips) return QMainWindow::eventFilter(obj, event);  //防止移动到tips上触发hoverleave

    if (event->type() == QEvent::HoverEnter)
    {
        qDebug() << "HoverEnter";

        QHoverEvent* hoverEvent = dynamic_cast<QHoverEvent*>(event);

        tips = new BubbleTipsWidget(this, 200);

        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);

        tips->setBackColor(QColor(71, 76, 84));
        //tips->setBackColor(QColor(132, 133, 135));

        tips->setDirect(DIRECT::DIRECT_LEFT, 0.4);
        tips->setIcon(QIcon("E:\\WorkSpace\\icons\\unbrella_filled"));
        //tips->setContent(tr("this is a tool tip...this is a tool tip...this is a tool tip...this is a tool tip..."), QColor(Qt::white));
        tips->setContent(tr("this is a tool tip..."), QColor(Qt::white));
        tips->setAutoPosition(true, button1);
        tips->animeShow();


        return true;
    }
    else if (event->type() == QEvent::HoverLeave)
    {
        qDebug() << "HoverLeave";
        tips->animeClose();
        return true;
    }

    return QMainWindow::eventFilter(obj, event);	//没安装过滤器的，调用默认的过滤器
}