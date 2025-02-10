#ifndef LISTWIDGETCUSTOM01_H
#define LISTWIDGETCUSTOM01_H
#include <QWidget>
#include "ui_ListWidgetCustom01.h"
#include <QWidget>
#include <QlistWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QString>
#include "ScrollBarCustom01.h"
#include <QList>
#include <QModelIndexList>

//padding-right:10px�հ�����slider
const QString qssStyleView = "QListView{border:2px solid gray; color:black;font-size:20px;padding:4px;padding-right:10px; outline:4px;background:white }\
        QListView::Item{background:rgb(250,218,94);padding-left:4px; }\
        QListView::Item:hover{border: 3px solid white;background:rgb(232,88,39);color:white;border-radius:10px; padding-left:4px; }\
        QListView::item:selected{border: 2px solid black;background:rgb(232,88,39); color:white;border-radius:10px;padding:10px;padding-left:12px; }";

const QString qssStyleWidget = "QListWidget{border:2px solid gray; color:black;font-size:20px;padding:4px;padding-right:10px; outline:4px;background:white }\
        QListWidget::Item{background:rgb(250,218,94);padding-left:4px;}\
        QListWidget::Item:hover{border: 3px solid white;background:rgb(232,88,39);color:white;border-radius:10px; padding-left:4px;}\
        QListWidget::item:selected{border: 2px solid black;background:rgb(232,88,39); color:white;border-radius:10px;padding:10px;padding-left:12px;}";


class ListWidgetCustom01 : public QWidget
{
	Q_OBJECT

public:
	ListWidgetCustom01(QWidget* parent = nullptr, bool isView = false);
	~ListWidgetCustom01();

	//�޸�pngͼ����ɫ
	QIcon changeIconColor(QIcon icon, QColor newColor);

	/*
		����ʼ��ΪQListWidgetʱ
	*/
	//�ɸ�ÿ��item��Ӳ�ͬicon���ı�����
	void addItem(QString item, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItem(QString item, int index, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	
	//�ɸ�ÿ��item��Ӳ�ͬicon��ͨ����QListWidgetItem���ã��Զ����ı�λ�á�item��С�ȣ�
	void addItem(QListWidgetItem* item, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItem(QListWidgetItem* item, int index, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	
	//�Ƴ�һ��item
	QListWidgetItem* takeItem(int index);
	
	//��item���widget
	void addWidgetToItem(QListWidgetItem* item, QWidget* w);



	/*
		����ʼ��ΪQListViewʱ
	*/
	void addItemView(QString item, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItemView(QString item, int index, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void addItemView(QStandardItem* item, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItemView(QStandardItem* item, int index, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	QStandardItem* takeItemView(int index);
	bool removeItemFromModelView(int index);


	QListWidget* listwidget = nullptr;
	QListView* listview = nullptr;
	QStandardItemModel* m_model;		//listview��model
	ScrollBarCustom01* slider;
	QList<bool> selItemsIndexs;			//��ѡ�е�item��index��Ŀ���ǿ���selected��item��icon
	QListWidgetItem* lastHover = nullptr;				//listwidget�ϴα�hover��item��index
	QStandardItem* lastHoverView = nullptr;				//listview�ϴα�hover��item��index
	int itemCount = 0;				//item����

private:
	Ui::ListWidgetCustom01Class ui;

	QFont m_font;
	QFont m_fontHover;
	QFont m_fontSelected;


	bool m_isView = false;				//�Ƿ���view

	QList<QIcon> m_icons;				//��ͨͼ��
	QList<QIcon> m_iconsClicked;		//�����ͼ��
	QList<QIcon> m_iconsHover;			//�����ͣͼ�� 

protected:
	virtual bool eventFilter(QObject* watched, QEvent* event);	//�¼�������������hover�¼�

signals:
	void hoverItemChanged(QListWidgetItem* current, QListWidgetItem* previous);	//hover�ı䣨listwidget��
	void hoverItemChangedView(QStandardItem* current, QStandardItem* previous);	//hover�ı䣨listview)
};

#endif // !LISTWIDGETCUSTOM01_H