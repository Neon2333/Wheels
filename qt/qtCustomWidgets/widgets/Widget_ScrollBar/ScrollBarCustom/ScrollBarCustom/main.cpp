#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include <QListView>
#include <QTableView>
#include <QStandardItemModel>
#include "ScrollBarCustom.h"
#include <QListWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QIcon icon1("E:\\WorkSpace\\icons\\unbrella_outline.png");
    QIcon icon2("E:\\WorkSpace\\icons\\unbrella_filled.png");

    // 创建模型
    QStandardItemModel* model = new QStandardItemModel();

    // 设置列标题
    QStringList header{ "user" };
    //设置表头
    model->setHorizontalHeaderLabels(header);

    // 填充数据
    for (int i = 0; i < 30; ++i) {
        QString username = "user" + QString::number(i);

        // 创建行数据
        QStandardItem* row1 = new QStandardItem(icon1, username);
        row1->setTextAlignment(Qt::AlignCenter);

        // 将数据项添加到模型
        model->appendRow(row1);
    }

    ScrollBarCustom* barVertical = new ScrollBarCustom(&w, 40); //垂直
    barVertical->setSingleStep(1);
    ScrollBarCustom* barHorizontal = new ScrollBarCustom(&w);   //水平
    barHorizontal->setSingleStep(1);


    // 创建视图并设置模型
    QListView* view = new QListView(&w);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);   //view不可编辑
    view->setStyleSheet("border: none");    //无边框
    view->move(200, 200);
    view->resize(800, 800);
    view->setModel(model);  //给view设定model
    view->setIconSize(QSize(100, 100)); //view设定图标大小
    view->setViewMode(QListView::ListMode); // 设置为列表模式
    view->setSelectionMode(QAbstractItemView::SingleSelection); // 设置为单选
    view->setSelectionBehavior(QAbstractItemView::SelectRows); // 选择整行
    view->setResizeMode(QListView::Adjust); // 调整视图大小以适应内容
    view->setSpacing(10); // 设置项之间的间隔为10像素


    //拖动
    view->setDragEnabled(true);
    view->setAcceptDrops(true);
    view->setDropIndicatorShown(true);  //启动拖动可视的指示器
    view->setDragDropMode(QAbstractItemView::InternalMove);

    //qss美化
    //padding:10px;padding-right:0px;为了让Scrollbar不会距离右边太远
    const QString style_list = "QListView{border:1px solid gray; color:black;font-size:20px;\
        padding:10px;padding-right:0px; outline:0px;background:transparent }\
        QListView::Item{height:42px;padding-left:8px;}\
        QListView::Item:hover{background:gray; border-radius:10px; }\
        QListView::item:selected{background:darkgray; color:white;border-radius:10px; }";
    view->setStyleSheet(style_list);

    QObject::connect(view, &QListView::clicked, view, [view, model, icon1, icon2](const QModelIndex& index) {
        for (int i = 0; i < model->rowCount(); i++)
        {
            QStandardItem* item = model->item(i);
            item->setIcon(icon1);
        }

        QStandardItem* item = model->itemFromIndex(index);
        if (item)
        {
            // 更改图标
            item->setIcon(icon2);
        }
        });

    view->setVerticalScrollBar(barVertical);
    view->setHorizontalScrollBar(barHorizontal);
    view->show();

    w.show();
    return a.exec();
}
