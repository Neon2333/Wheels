#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qanimationstackedwidget.h"
#include <QPushButton>

int g_index=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAnimationStackedWidget* aniSW = new QAnimationStackedWidget(this);
    aniSW->setGeometry(50,50,500,400);
    aniSW->setDuration(1000);

    connect(aniSW, &QAnimationStackedWidget::currentChanged, this, [=](int curIndex){
        qDebug()<<"curIndex="<<curIndex;
    });

    QPushButton* page0 = new QPushButton(aniSW);
    page0->setStyleSheet("QPushButton{background-color:red;}");
    page0->setText("0");
    aniSW->addWidget(page0);

    QPushButton* page1 = new QPushButton(aniSW);
    page1->setStyleSheet("QPushButton{background-color:blue;}");
    page1->setText("1");
    aniSW->addWidget(page1);

    QPushButton* page2= new QPushButton(aniSW);
    page2->setStyleSheet("QPushButton{background-color:green;}");
    page2->setText("2");
    aniSW->addWidget(page2);

    QPushButton* pbNext = new QPushButton(this);
    pbNext->setText("nextPage");
    pbNext->setGeometry(500,500,100,50);
    connect(pbNext, &QPushButton::clicked, this, [=](){
        aniSW->switchPage(true);
    });

    QPushButton* pbPre = new QPushButton(this);
    pbPre->setText("prePage");
    pbPre->setGeometry(400,500,100,50);
    connect(pbPre, &QPushButton::clicked, this, [=](){
        aniSW->switchPage(false);
    });

    QPushButton* pbMode = new QPushButton(this);
    pbMode->setText("changeMode");
    pbMode->setGeometry(600,500,100,50);
    connect(pbMode, &QPushButton::clicked, this, [=](){
        if(aniSW->getAniMode()==QAnimationStackedWidget::aniMode::Switch)
            aniSW->setAniMode(QAnimationStackedWidget::aniMode::Cover);
        else
            aniSW->setAniMode(QAnimationStackedWidget::aniMode::Switch);
    });

    QPushButton* pbDir = new QPushButton(this);
    pbDir->setText("changeDirection");
    pbDir->setGeometry(700,500,100,50);
    connect(pbDir, &QPushButton::clicked, this, [=](){
        if(aniSW->getSwitchDirection()==QAnimationStackedWidget::switchDirection::Horizontal)
            aniSW->setSwitchDirection(QAnimationStackedWidget::switchDirection::Vertical);
        else
            aniSW->setSwitchDirection(QAnimationStackedWidget::switchDirection::Horizontal);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
