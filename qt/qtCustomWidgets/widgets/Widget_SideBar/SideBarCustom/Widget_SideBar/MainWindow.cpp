#include "MainWindow.h"

const int fixed = 20; //固定侧边栏宽度

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->resize(600, 400);

    this->setAttribute(Qt::WA_TranslucentBackground);   //背景透明
    //this->setWindowFlags(Qt::FramelessWindowHint);  //隐藏最大最小化等按键

  
    //固定侧边栏
    fixedBar = new QWidget(this);
    fixedBar->move(0, 0);
    fixedBar->resize(QSize(fixed, this->height()));
    fixedBar->setFixedWidth(fixed);
    fixedBar->setStyleSheet("QWidget{background-color:rgb(0,0,255);border:none;border-radius:5px;}");
    vlay_fixedBar = new QVBoxLayout;
    vlay_fixedBar->setContentsMargins(0, 0, 0, 0);
    vlay_fixedBar->setSpacing(0);
    QPushButton* btnsidebar5 = new QPushButton(this);
    QPushButton* btnsidebar6 = new QPushButton(this);
    btnsidebar5->setStyleSheet("QPushButton{background-color:rgb(255,255,255)}");
    btnsidebar6->setStyleSheet("QPushButton{background-color:rgb(255,255,255)}");
    vlay_fixedBar->addWidget(btnsidebar5);
    vlay_fixedBar->addWidget(btnsidebar6);
    fixedBar->setLayout(vlay_fixedBar);
    //this->stackUnder(fixedBar);

    //固定侧边栏图层下方的占位，宽度同固定侧边栏
    placeholder_fixedBar = new QSpacerItem(fixed, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

    //侧边栏
    //sidebar = new SideBar(this, 50, 10, 10, 0, 0);
    sidebar = new SideBar(this, 80);    //shrinkWidth=fixedWidth+右侧添加的widget的宽度。80+30*2=140
    //sidebar->setIncreasedWidth(270);

    QPushButton* btnsidebar1 = new QPushButton(this);
    QPushButton* btnsidebar2 = new QPushButton(this);
    QPushButton* btnsidebar3 = new QPushButton(this);
    QPushButton* btnsidebar4 = new QPushButton(this);
    sidebar->addWidget(btnsidebar1, QSize(30, 15), 1, 0);
    sidebar->addWidget(btnsidebar2, QSize(30, 15), 2, 0);
    sidebar->addWidget(btnsidebar3, QSize(30, 15), 1, 1);
    sidebar->addWidget(btnsidebar4, QSize(30, 15), 2, 1);

    //翻页容器
    stackedWidget = new QStackedWidget(this);
    QWidget* page1 = new QWidget;
    QGridLayout* hlayR1 = new QGridLayout;
    hlayR1->setContentsMargins(0, 0, 0, 0);
    hlayR1->setSpacing(0);
    QPushButton* btn1 = new QPushButton;
    hlayR1->addWidget(btn1);
    page1->setLayout(hlayR1);

    QWidget* page2 = new QWidget;
    QGridLayout* hlayR2 = new QGridLayout;
    hlayR2->setContentsMargins(0, 0, 0, 0);
    hlayR2->setSpacing(0);
    QPushButton* btn2 = new QPushButton;
    hlayR2->addWidget(btn2);
    page2->setLayout(hlayR2);

    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->setCurrentIndex(0);

    
    //侧边栏、翻页容器添加到水平布局
    hlay = new QHBoxLayout;
    hlay->setContentsMargins(0, 0, 0, 0);
    hlay->setSpacing(0);
    //hlay->addWidget(fixedBar);
    hlay->addSpacerItem(placeholder_fixedBar);
    hlay->addWidget(sidebar);
    placeholder_right = new QSpacerItem(placeholderRightWidth, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    hlay->addSpacerItem(placeholder_right);
    hlay->addWidget(stackedWidget);

    //中央容器应用水平布局
    container = new QWidget(this);
    container->setLayout(hlay);
    this->setCentralWidget(container);

    sidebar->setStyleSheet("QWidget{background-color:royalblue;border:none;border-radius:5px}");
    btnsidebar1->setStyleSheet("QPushButton{background-color:rgb(255,0,0)}");
    btnsidebar2->setStyleSheet("QPushButton{background-color:rgb(0,255,0)}");
    btnsidebar3->setStyleSheet("QPushButton{background-color:rgb(0,0,255)}");
    btnsidebar4->setStyleSheet("QPushButton{background-color:rgb(255,255,255)}");
    btn1->setStyleSheet("QPushButton{background-color:yellow}");
    btn2->setStyleSheet("QPushButton{background-color:royalblue}");
    container->setStyleSheet("QWidget{background-color:rgb(255, 85, 127);border:none;border-radius:5px;}");
    //container->setStyleSheet("QWidget{background-color:rgb(255, 85, 127);border-radius:5px;border:1px solid rgb(213, 213, 213);}");
    //container->setStyleSheet("QWidget{background-color:white;border:none;border-radius:5px;}");
    stackedWidget->setStyleSheet("QStackedWidget{border:none;}");


    //侧边栏置于hlay布局中所有控件之上
    //sidebar->raise();
    fixedBar->raise();


    connect(sidebar, &SideBar::shrinkWidthChanged, this, [this](int newShrinkWidth) {
        });

    connect(sidebar, &SideBar::widthChanged, this, [=](int sidebarWidth) {
        qDebug() << "connect sidebarwidth=" << sidebarWidth;
        int stackedWidgetWidth = this->width() - fixed - sidebarWidth - placeholderRightWidth - hlay->spacing() - hlay->contentsMargins().left() - hlay->contentsMargins().right();
        int stackedWidgetX = fixed + sidebarWidth + placeholderRightWidth + hlay->spacing();
        stackedWidget->setGeometry(stackedWidgetX, stackedWidget->y(), stackedWidgetWidth, stackedWidget->height());
        });

    connect(sidebar, &SideBar::hasShown, this, [this]() {
        //限制窗口最小大小，避免暴露sidebar无法自适应大小。最小：扩展情况下，右侧区域留50，正方形。
        this->setMinimumSize(sidebar->x() + sidebar->getShrinkWidth() + sidebar->increasedWidth + 50, sidebar->getShrinkWidth() + sidebar->increasedWidth + 50);
        sidebar->setIsInit(false);
        });

    connect(btn1, &QPushButton::clicked, sidebar, [=]() {
        /*btnsidebar2->setVisible(true);
        btnsidebar4->setVisible(true);*/

        stackedWidget->setCurrentIndex(1);
        sidebar->expand();
        });


    connect(btn2, &QPushButton::clicked, sidebar, [=]() {
        //QStackedWidget翻页和sidebar收缩变化会干扰导致QStackedWidget先瞬间收缩又恢复原尺寸再慢慢收缩，解决：先翻页后收缩，不可先收缩再翻页。
        stackedWidget->setCurrentIndex(0);
        sidebar->shrink();

      /* btnsidebar2->setVisible(false);
        btnsidebar4->setVisible(false);*/
        
        //btnsidebar2->setFixedWidth(1);
        //btnsidebar4->setFixedWidth(1);
        });
}

MainWindow::~MainWindow()
{}

void MainWindow::resizeEvent(QResizeEvent * ev)
{
    //为了解决：改变窗口大小时，sidebar宽度瞬间回到初始值。
    //按照isExpanded状态设定其宽度为固定值。通过设定窗口最小尺寸避免暴露sidebar无法自适应。
    if (!sidebar->isAnimationRunning)
    {
        //只修改宽度，不修改高度，因此resize第二个参数为sidebar->height()。高度由SideBar::resizeEvent调整。
        if (sidebar->isExpanded)
        {
            sidebar->resize(sidebar->getShrinkWidth() + sidebar->increasedWidth, sidebar->height());
        }
        else
        {
            sidebar->resize(sidebar->getShrinkWidth(), sidebar->height());
        }
    }

    fixedBar->resize(QSize(fixed, sidebar->height()));
    qDebug() << "stackedWidget size=" << stackedWidget->size();
    QMainWindow::resizeEvent(ev);
}

void MainWindow::showEvent(QShowEvent* event)
{
}
