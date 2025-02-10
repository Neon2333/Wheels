#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "navibar.h"

int g_index=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QList<QColor> btnColors{QColor(qRgba(247, 59, 89, 150)),
                            QColor(qRgba(16, 188, 249, 150)),
                            QColor(qRgba(92, 99, 252, 150)),
                            QColor(qRgba(7, 197, 108, 150)),
                            QColor(qRgba(254, 167, 2, 150))};


    NaviBar* navibar=new NaviBar(this);
    navibar->move(0,0);
    // navibar->setButtonWidth(150);
    // navibar->setIconSize(QSize(64,64));
    // navibar->setTextSize(16);
    // navibar->setGeometry(0,0,1500,100);
    // navibar->setPaddins(10,10,10,10);
    for(int ii=0;ii<btnColors.size();++ii)
    {
        navibar->setIconSize(QSize(32+ii,32+ii));
        navibar->setTextSize(10+ii);
        navibar->appendButton(QIcon(":/E:/WorkSpace/icons/biliTV_46_46.png"), QString("btnAdd%1").arg(g_index++), QColor("white"), QColor("white"), btnColors.at(ii));
    }

    int idTmp = navibar->btnID(0);
    QToolButton& btn = navibar->btn(idTmp);
    connect(&btn, &QToolButton::clicked, this, [=](){
        qDebug()<<"btn0 clicked...";
    });


    QPushButton* btnAdd = new QPushButton(this);
    btnAdd->setGeometry(100,500,50,50);
    btnAdd->setText("add");
    connect(btnAdd,&QPushButton::clicked,this,[=](){
        // navibar->appendButton(QIcon(":/E:/WorkSpace/icons/biliTV_46_46.png"), QString("btnAdd%1").arg(g_index++), QColor("white"), QColor("white"));
        for(int ii=0;ii<btnColors.size();++ii)
        {
            navibar->appendButton(QIcon(":/E:/WorkSpace/icons/biliTV_46_46.png"), QString("btnAdd%1").arg(g_index++), QColor("white"), QColor("white"), btnColors.at(ii));
        }
    });



    QPushButton* btnIns = new QPushButton(this);
    btnIns->setGeometry(200,500,50,50);
    btnIns->setText("ins");
    connect(btnIns,&QPushButton::clicked,this,[=](){
        navibar->insertButton(0,QIcon(":/E:/WorkSpace/icons/biliTV_46_46.png"), QString("btnIns%1").arg(g_index++), QColor("white"), QColor("white"));
    });



    QPushButton* btnDel = new QPushButton(this);
    btnDel->setGeometry(300,500,50,50);
    btnDel->setText("del");
    connect(btnDel,&QPushButton::clicked,this,[=](){
        int idtmp = navibar->btnID(0);
        navibar->removeButton(0, idtmp);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
