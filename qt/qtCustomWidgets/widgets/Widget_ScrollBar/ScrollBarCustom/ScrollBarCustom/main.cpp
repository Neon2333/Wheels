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

    // ����ģ��
    QStandardItemModel* model = new QStandardItemModel();

    // �����б���
    QStringList header{ "user" };
    //���ñ�ͷ
    model->setHorizontalHeaderLabels(header);

    // �������
    for (int i = 0; i < 30; ++i) {
        QString username = "user" + QString::number(i);

        // ����������
        QStandardItem* row1 = new QStandardItem(icon1, username);
        row1->setTextAlignment(Qt::AlignCenter);

        // ����������ӵ�ģ��
        model->appendRow(row1);
    }

    ScrollBarCustom* barVertical = new ScrollBarCustom(&w, 40); //��ֱ
    barVertical->setSingleStep(1);
    ScrollBarCustom* barHorizontal = new ScrollBarCustom(&w);   //ˮƽ
    barHorizontal->setSingleStep(1);


    // ������ͼ������ģ��
    QListView* view = new QListView(&w);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);   //view���ɱ༭
    view->setStyleSheet("border: none");    //�ޱ߿�
    view->move(200, 200);
    view->resize(800, 800);
    view->setModel(model);  //��view�趨model
    view->setIconSize(QSize(100, 100)); //view�趨ͼ���С
    view->setViewMode(QListView::ListMode); // ����Ϊ�б�ģʽ
    view->setSelectionMode(QAbstractItemView::SingleSelection); // ����Ϊ��ѡ
    view->setSelectionBehavior(QAbstractItemView::SelectRows); // ѡ������
    view->setResizeMode(QListView::Adjust); // ������ͼ��С����Ӧ����
    view->setSpacing(10); // ������֮��ļ��Ϊ10����


    //�϶�
    view->setDragEnabled(true);
    view->setAcceptDrops(true);
    view->setDropIndicatorShown(true);  //�����϶����ӵ�ָʾ��
    view->setDragDropMode(QAbstractItemView::InternalMove);

    //qss����
    //padding:10px;padding-right:0px;Ϊ����Scrollbar��������ұ�̫Զ
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
            // ����ͼ��
            item->setIcon(icon2);
        }
        });

    view->setVerticalScrollBar(barVertical);
    view->setHorizontalScrollBar(barHorizontal);
    view->show();

    w.show();
    return a.exec();
}
