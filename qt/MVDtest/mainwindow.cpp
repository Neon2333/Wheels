#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QStringList strList;
    strList << u8"北京"<< u8"上海"<< u8"深圳"<< u8"广东"<< u8"南京"<<u8"苏州"<< u8"西安";
    //创建数据模型
    m_pStringListModel=new QStringListModel(this);
    //为模型设置原始数据StringList，会导入StringList的内容
    m_pStringListModel->setStringList(strList);
    //为ui->listView设置数据模型
    ui->listView->setModel(m_pStringListModel);

    //链接信号，弹出菜单
    connect(ui->listView, &QListView::customContextMenuRequested, this, [=](const QPoint& pos){
        if(!(ui->listView->selectionModel()->selectedIndexes()).empty())
        {
            m_pMenu->exec(QCursor::pos());	//在当前鼠标所在位置显示
        }
    });

    //设置菜单策略
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    m_pMenu = new QMenu(ui->listView);
    QAction* pAc1 = new QAction(u8"删除", ui->listView);
    QAction* pAc2 = new QAction(u8"插入", ui->listView);
    QAction* pAc3 = new QAction(u8"置顶", ui->listView);
    QAction* pAc4 = new QAction(u8"排到最后", ui->listView);
    QAction* pAc5= new QAction(u8"清空", ui->listView);
    QAction* pAc6 = new QAction(u8"尾部增加一项", ui->listView);
    QAction* pAc7 = new QAction(u8"显示选中项的行列号", ui->listView);
    QAction* pAc8 = new QAction(u8"显示全部", ui->listView);

    m_pMenu->addAction(pAc1);
    m_pMenu->addAction(pAc2);
    m_pMenu->addAction(pAc3);
    m_pMenu->addAction(pAc4);
    m_pMenu->addAction(pAc5);
    m_pMenu->addAction(pAc6);
    m_pMenu->addAction(pAc7);
    m_pMenu->addAction(pAc8);

    //删除
    connect(pAc1, &QAction::triggered, this, [=](){
        QModelIndex selIndex=ui->listView->currentIndex();	//获取当前index
        m_pStringListModel->removeRow(selIndex.row());	//QModelIndex包含行列的
    });

    //选中行前插入
    connect(pAc2, &QAction::triggered, this, [=](){
        QModelIndex selIndex = ui->listView->currentIndex();
        m_pStringListModel->insertRow(selIndex.row());	//在selIndex前插入一行
        m_pStringListModel->setData(selIndex, "inserted item", Qt::DisplayRole);	//给新增一行设置文本
        ui->listView->setCurrentIndex(selIndex);
    });

    //置顶
    connect(pAc3, &QAction::triggered, this, [=](){
        QModelIndex selIndex = ui->listView->currentIndex();
        QVariant delData = selIndex.data();
        m_pStringListModel->removeRow(selIndex.row());
        m_pStringListModel->insertRow(0);
        m_pStringListModel->setData(m_pStringListModel->index(0, 0), delData, Qt::DisplayRole);

    });

    //排到最后
    connect(pAc4, &QAction::triggered, this, [=](){
        QModelIndex selIndex = ui->listView->currentIndex();
        QVariant delData = selIndex.data();
        m_pStringListModel->removeRow(selIndex.row());
        m_pStringListModel->insertRow(m_pStringListModel->rowCount());
        m_pStringListModel->setData(m_pStringListModel->index(m_pStringListModel->rowCount()-1, 0), delData, Qt::DisplayRole);
    });

    //清空
    connect(pAc5, &QAction::triggered, this, [=](){
        m_pStringListModel->removeRows(0, m_pStringListModel->rowCount());
    });

    //尾部增加一项
    connect(pAc6, &QAction::triggered, this, [=](){
        m_pStringListModel->insertRow(m_pStringListModel->rowCount());	//尾部增加一行，否则会把原有最后一行替换掉
        //获取新增的一行
        QModelIndex newRowIndex = m_pStringListModel->index(m_pStringListModel->rowCount()-1, 0);
        m_pStringListModel->setData(newRowIndex, "new item", Qt::DisplayRole);	//给新增一行设置文本
        ui->listView->setCurrentIndex(newRowIndex);
    });

    //显示选中项的行列号
    connect(pAc7, &QAction::triggered, this, [=](){
        QModelIndex selIndex = ui->listView->currentIndex();
        ui->textEdit->clear();
        //显示选中的selIndex的行列号
        ui->textEdit->append(QString::asprintf(u8"当前项:row=%d, column=%d", selIndex.row(), selIndex.column()));
    });

    //显示全部
    connect(pAc8, &QAction::triggered, this, [=](){
        QStringList temp = m_pStringListModel->stringList();
        ui->textEdit->clear();
        for(auto item : temp)
        {
            ui->textEdit->append(item);
        }
    });


}
