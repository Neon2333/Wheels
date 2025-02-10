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

//padding-right:10px空白留给slider
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

	//修改png图标颜色
	QIcon changeIconColor(QIcon icon, QColor newColor);

	/*
		当初始化为QListWidget时
	*/
	//可给每个item添加不同icon，文本居中
	void addItem(QString item, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItem(QString item, int index, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	
	//可给每个item添加不同icon（通过对QListWidgetItem设置，自定义文本位置、item大小等）
	void addItem(QListWidgetItem* item, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItem(QListWidgetItem* item, int index, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	
	//移除一个item
	QListWidgetItem* takeItem(int index);
	
	//给item添加widget
	void addWidgetToItem(QListWidgetItem* item, QWidget* w);



	/*
		当初始化为QListView时
	*/
	void addItemView(QString item, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItemView(QString item, int index, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void addItemView(QStandardItem* item, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	void insertItemView(QStandardItem* item, int index, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
	QStandardItem* takeItemView(int index);
	bool removeItemFromModelView(int index);


	QListWidget* listwidget = nullptr;
	QListView* listview = nullptr;
	QStandardItemModel* m_model;		//listview的model
	ScrollBarCustom01* slider;
	QList<bool> selItemsIndexs;			//被选中的item的index，目的是控制selected的item的icon
	QListWidgetItem* lastHover = nullptr;				//listwidget上次被hover的item的index
	QStandardItem* lastHoverView = nullptr;				//listview上次被hover的item的index
	int itemCount = 0;				//item个数

private:
	Ui::ListWidgetCustom01Class ui;

	QFont m_font;
	QFont m_fontHover;
	QFont m_fontSelected;


	bool m_isView = false;				//是否是view

	QList<QIcon> m_icons;				//普通图标
	QList<QIcon> m_iconsClicked;		//点击后图标
	QList<QIcon> m_iconsHover;			//鼠标悬停图标 

protected:
	virtual bool eventFilter(QObject* watched, QEvent* event);	//事件过滤器，处理hover事件

signals:
	void hoverItemChanged(QListWidgetItem* current, QListWidgetItem* previous);	//hover改变（listwidget）
	void hoverItemChangedView(QStandardItem* current, QStandardItem* previous);	//hover改变（listview)
};

#endif // !LISTWIDGETCUSTOM01_H