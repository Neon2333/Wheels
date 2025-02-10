#include "MainWindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->resize(600, 400);
    
    this->setAttribute(Qt::WA_TranslucentBackground);   //����͸��
    //this->setWindowFlags(Qt::FramelessWindowHint);  //���������С���Ȱ���


    //�����
    sidebar = new SideBar(this, false, 10, 10, 10, 10, 50);
    sidebar->move(0,0);
    //sidebar->container->setStyleSheet("QWidget{background-color:royalblue;border:none;border-radius:5px}");
    //sidebar->setIncreasedWidth(270);

    QPushButton* btnsidebar1 = new QPushButton(this);
    QPushButton* btnsidebar2 = new QPushButton(this);
    //sidebar->addWidget(btnsidebar1);
    //sidebar->addWidget(btnsidebar2);
    sidebar->addWidget(btnsidebar1, QSize(30, 20));
    sidebar->addWidget(btnsidebar2, QSize(30, 20));


    //��ҳ����
    stackedWidget = new QStackedWidget(this);
    //stackedWidget->setStyleSheet("QStackedWidget{border-radius:0px;}");
    QWidget* page1 = new QWidget;
    //page1->setStyleSheet("QWidget{border:none;}");
    QGridLayout* hlayR1 = new QGridLayout;
    hlayR1->setContentsMargins(0, 0, 0, 0);
    hlayR1->setSpacing(0);
    QPushButton* btn1 = new QPushButton;
    //btn1->setStyleSheet("QPushButton{background-color:yellow}");
    hlayR1->addWidget(btn1);
    page1->setLayout(hlayR1);

    QWidget* page2 = new QWidget;
    //page2->setStyleSheet("QWidget{border:none;}");
    QGridLayout* hlayR2 = new QGridLayout;
    hlayR2->setContentsMargins(0, 0, 0, 0);
    hlayR2->setSpacing(0);
    QPushButton* btn2 = new QPushButton;
    //btn2->setStyleSheet("QPushButton{background-color:royalblue}");
    hlayR2->addWidget(btn2);
    page2->setLayout(hlayR2);
    
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->setCurrentIndex(0);


    //���������ҳ������ӵ�ˮƽ����
    hlay = new QHBoxLayout;
    hlay->setContentsMargins(0, 0, 0, 0);
    hlay->setSpacing(0);
    hlay->addWidget(sidebar);
    placeholder = new QSpacerItem(placeholderWidth, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    hlay->addSpacerItem(placeholder);
    hlay->addWidget(stackedWidget);

    //��������Ӧ��ˮƽ����
    container = new QWidget(this);
    //container->setStyleSheet("QWidget{background-color:rgb(255, 85, 127);border-radius:5px;border:1px solid rgb(213, 213, 213);}");
    //container->setStyleSheet("QWidget{background-color:rgb(255, 85, 127);border-radius:5px;border:none;}");
    container->setLayout(hlay);
    this->setCentralWidget(container);
    
    //sidebar->container->setStyleSheet("QWidget{background-color:royalblue;border:none;border-radius:5px}");
    sidebar->setStyleSheet("QWidget{background-color:royalblue;border:none;border-radius:5px}");
    btnsidebar1->setStyleSheet("QPushButton{background-color:rgb(255,0,0)}");
    btnsidebar2->setStyleSheet("QPushButton{background-color:rgb(0,255,0)}");
    btn1->setStyleSheet("QPushButton{background-color:yellow}");
    btn2->setStyleSheet("QPushButton{background-color:royalblue}");
    container->setStyleSheet("QWidget{background-color:rgb(255, 85, 127);border:none;border-radius:5px;}");
    //container->setStyleSheet("QWidget{background-color:white;border:none;border-radius:5px;}");
    //stackedWidget->setStyleSheet("QStackedWidget{border:5px solid black;}");


    ////���������hlay���������пؼ�֮��
    //sidebar->raise();
   
    //���ƴ�����С��С�����Ⱪ¶sidebar�޷�����Ӧ��С
    this->setMinimumSize(sidebar->getFixedWidth() + sidebar->increasedWidth + placeholderWidth + 100, sidebar->getFixedWidth() + sidebar->increasedWidth + placeholderWidth + 100);

    connect(btn1, &QPushButton::clicked, sidebar, [=]() {
        stackedWidget->setCurrentIndex(1);  
        sidebar->expand();
        });

    
    connect(btn2, &QPushButton::clicked, sidebar, [=]() {
        //QStackedWidget��ҳ��sidebar�����仯����ŵ���QStackedWidget��˲�������ָֻ�ԭ�ߴ�������������������ȷ�ҳ�������������������ٷ�ҳ��
        stackedWidget->setCurrentIndex(0);
        sidebar->shrink();
        });


    connect(sidebar, &SideBar::widthChanged, this, [=](int sidebarWidth) {
        qDebug() << "connect sidebarwidth=" << sidebarWidth;
        int stackedWidgetWidth = this->width() - sidebarWidth - placeholderWidth - hlay->spacing() - hlay->contentsMargins().left() - hlay->contentsMargins().right();
        int stackedWidgetX = sidebar->x() + sidebarWidth + placeholderWidth + hlay->spacing();
        stackedWidget->setGeometry(stackedWidgetX, stackedWidget->y(), stackedWidgetWidth, stackedWidget->height());
        });
}

MainWindow::~MainWindow()
{}

void MainWindow::resizeEvent(QResizeEvent * ev)
{
    //Ϊ�˽�����ı䴰�ڴ�Сʱ��sidebar���˲��ص���ʼֵ��
    //����isExpanded״̬�趨����Ϊ�̶�ֵ��ͨ���趨������С�ߴ���Ⱪ¶sidebar�޷�����Ӧ��
    if (sidebar->isExpanded) {
        sidebar->resize(sidebar->getFixedWidth() + sidebar->increasedWidth, sidebar->height());
    }
    else {
        sidebar->resize(sidebar->getFixedWidth(), sidebar->height());
    }

    qDebug() << "5 sidebar size=" << sidebar->size();
    qDebug() << "5 sidebar->getFixedWidth()=" << sidebar->getFixedWidth();

    //QWidget::resizeEvent(ev);
}
