# 1. 结构

---

* 封装了`listwidget`和`listview+QStandardItemModel`，都是public可访问自己定义
* 使用自定义滚动条`ScrollBarCustom01`
* 通过三个`QList`分别管理每个item的icon、iconClicked、iconHover
* 通过`lastHover`管理上次被鼠标hover的item
* 通过clicked事件处理selected的item。包括：icon改变、颜色改变、字体颜色改变、字体大小改变、边缘颜色（模拟选中框）。
* 通过事件过滤器处理hover的item。包括：icon改变、颜色改变、字体颜色改变、字体大小改变、边缘颜色（模拟按压效果）。
* 通过listwidget的currentItemChanged信号可控制selected时播放动画，未selected时动画停止。
* 通过自定义hoverItemChanged控制hover时播放动画，未selected时动画停止。
* 通过`QList<bool> selItemsIndexs;`管理被选中的item的index

* 注意点：删除item的函数，若删除的item是lastHover或是被选中的（在selItemsIndexs中对应位置是true）

  同样需要移除该item

  ```cpp
  //如果删除项是lastHover或selected，删除集合中记录
  if (delItem == lastHoverView) lastHoverView = nullptr;
  selItemsIndexs.removeAt(index);
  ```

# 2. 使用

---

* listwidget、listview、m_model都是【public】的，可以自行设定qss。

需要添加`ScrollBarCustom01`作为滚动条。

```cpp
//构造
//isView：内部使用的是listwidget还是listview
ListWidgetCustom01(QWidget* parent = nullptr, bool isView = false);
```

## （1）使用listwidget

```cpp
//文本居中，可设置icon、点击后icon、鼠标悬停hover时icon
//可给每个item添加不同icon，文本居中
void addItem(QString item, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
void insertItem(QString item, int index, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
```

```cpp
//自己定义QListWidgetItem添加item
//可在定义QListWidgetItem时自定义item属性
//可给每个item添加不同icon
void addItem(QListWidgetItem* item, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
void insertItem(QListWidgetItem* item, int index, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
```

* listwidget的takeItem会自动删除list中的项

```cpp
//移除并获取一个item
QListWidgetItem* takeItem(int index);
```

* 为了控制添加的widget的大小、位置，最好使用布局。并且添加的widget需要额外设置qss样式。
* 可用`setFixedSize()`设置固定大小，`setSizeHint()`设置推荐大小（尺寸最小值）

```cpp
//给item添加其他小组件
void addWidgetToItem(QListWidgetItem* item, QWidget* w);

//设置icon和clickicon、hovericon、进度条、checkbox
QString user = "user" + QString::number(i);
QListWidgetItem* item = new QListWidgetItem(icon1.pixmap(50, 50), user);
item->setTextAlignment(Qt::AlignCenter);

list->addItem(item, icon2, icon2);			
int index = list->listwidget->count() - 1;			//获取最新添加的item的index

/*
* 添加其他控件，并设置qss
*/
QCheckBox* check = new QCheckBox;					//添加checkbox
const QString qssStyleCheck = "QCheckBox{height:10px; width:50; background:transparent;}\
	QCheckBox::indicator{height:10px; width:50px;}\
	QCheckBox::hover{background:blue; border-radius:10px; }\
	QCheckBox::checked{background:green; color:white;border-radius:10px; }";
check->setStyleSheet(qssStyleCheck);	//checkbox的样式不被listwidget的指定，需要单独指定
check->setFixedWidth(100);	//指定checkbox大小

QProgressBar* bar = new QProgressBar;	//bar也可指定样式
const QString qssStyleBar= "QProgressBar{height:22px; text-align:center; font-size:14px; color:white; border-radius:11px; background:#1D5573;}\
	QProgressBar::chunk{border-radius:11px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1 #9900ff);}";
bar->setStyleSheet(qssStyleBar);
bar->setMaximum(100);
bar->setValue(50);
bar->move(300, 10);			//在布局中move无效
bar->setFixedWidth(100);	//设定progressbar的宽度

QWidget* container = new QWidget;
QHBoxLayout* layout = new QHBoxLayout;
layout->addWidget(check);
layout->addWidget(bar);
container->setLayout(layout);

list->addWidgetToItem(list->listwidget->item(index), container);	//获取最新添加的item，并将widget容器添加到item
```

## （2）使用listview

* 默认，双击可编辑item

```cpp
void addItemView(QString item, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
void insertItemView(QString item, int index, QIcon icon = QIcon(), QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
void addItemView(QStandardItem* item, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
void insertItemView(QStandardItem* item, int index, QIcon iconClicked = QIcon(), QIcon iconHover = QIcon());
//获取指定项，不删除
QStandardItem* takeItemView(int index);
//删除指定项
bool removeItemFromModelView(int index);
```

## （3）使用代码

```cpp
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "ListWidgetCustom01.h"
#include <QCheckBox>
#include <QPushButton>
#include <QMovie>
#include <QLabel>
#include <QProgressBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.resize(800, 800);

	QIcon icon1(":/icon_normal");
	QIcon icon2(":/icon_hover_selected");
	QIcon icon3(":/icon3");
	
	///*
	//	widget
	//*/
	//ListWidgetCustom01* list = new ListWidgetCustom01(&w);
	//list->resize(800, 600);
	//list->move(200, 200);
	//list->listwidget->setIconSize(QSize(50, 50));			//设定icon大小
	//list->listwidget->setViewMode(QListView::ListMode);		//可自行设定显示模式
	////list->listwidget->setViewMode(QListView::IconMode);   //可自行设定显示模式
	////list->listwidget->setSpacing(10);						//设定item之间间距
	////list->listwidget->setSelectionMode(QAbstractItemView::MultiSelection);    //可自行设定单多选

	//QList<QMovie*> movies;	//为了实现按下/hover时才播放gif

	//for (int i = 0; i < 100; i++)
	//{
	//	//设置icon和clickicon、hovericon、进度条、checkbox
	//	QString user = "user" + QString::number(i);
	//	QListWidgetItem* item = new QListWidgetItem(icon1.pixmap(50, 50), user);
	//	item->setTextAlignment(Qt::AlignCenter);

	//	list->addItem(item, icon2, icon2);					
	//	int index = list->listwidget->count() - 1;			//获取最新添加的item的index

	//	/*
	//	* 添加其他控件，并设置qss
	//	*/
	//	QCheckBox* check = new QCheckBox;					//添加checkbox
	//	const QString qssStyleCheck = "QCheckBox{height:10px; width:50; background:transparent;}\
	//		QCheckBox::indicator{height:10px; width:50px;}\
	//		QCheckBox::hover{background:blue; border-radius:10px; }\
	//		QCheckBox::checked{background:green; color:white;border-radius:10px; }";
	//	check->setStyleSheet(qssStyleCheck);	//checkbox的样式不被listwidget指定
	//	check->setFixedWidth(100);

	//	QProgressBar* bar = new QProgressBar;	//bar也可指定样式
	//	const QString qssStyleBar= "QProgressBar{height:22px; text-align:center; font-size:14px; color:white; border-radius:11px; background:#1D5573;}\
	//		QProgressBar::chunk{border-radius:11px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1 #9900ff);}";
	//	bar->setStyleSheet(qssStyleBar);
	//	bar->setMaximum(100);
	//	bar->setValue(i);
	//	//bar->move(0, 10);	//无效
	//	bar->setFixedWidth(100);
	//	
	//	QWidget* container = new QWidget;
	//	QHBoxLayout* layout = new QHBoxLayout;
	//	layout->addWidget(check);
	//	layout->addWidget(bar);
	//	container->setLayout(layout);

	//	list->addWidgetToItem(list->listwidget->item(index), container);	//获取最新添加的item


	//	movies.append(nullptr);
	//}


	//for (int i = 100; i < 120; i++)
	//{
	//	//设置无文本、item大小为icon实际大小，没设置clickedIcon、hoverIcon
	//	QListWidgetItem* item = new QListWidgetItem(icon1.pixmap(50, 50), "aaa");
	//	//item->setSizeHint(icon1.actualSize(QSize(50, 50)));
	//	list->addItem(item,icon2);


	//	movies.append(nullptr);
	//}

	//for (int i = 120; i < 130; i++)
	//{
	//	//显示动态图，设定了clickicon，未设定icon
	//	QString user = "user" + QString::number(i);
	//	QListWidgetItem* item = new QListWidgetItem(user);
	//	item->setTextAlignment(Qt::AlignCenter); //设定文本居右
	//	item->setSizeHint(QSize(100, 120));		//gif设定高度100，item高度略高于gif
	//	list->addItem(item, icon2);				

	//	QMovie* movie = new QMovie("G:\\Pictures\\ASUS2013\\snake.gif");
	//	movie->setScaledSize(QSize(100, 100));	//设定gif尺寸
	//	QLabel* label = new QLabel;
	//	if(movie->isValid())	label->setMovie(movie);
	//	
	//	QWidget* container = new QWidget;
	//	QHBoxLayout* layout = new QHBoxLayout;
	//	layout->addWidget(label);
	//	container->setLayout(layout);
	//	int index = list->listwidget->count() - 1;
	//	list->addWidgetToItem(list->listwidget->item(index), container);
	//	
	//	movie->jumpToFrame(0);	//没有start时没有这行不显示
	//	movies.append(movie);
	//}

	//for (int i = 130; i < 140; i++)
	//{
	//	//纯文本
	//	QString user = "user" + QString::number(i);
	//	QListWidgetItem* item = new QListWidgetItem(user);
	//	item->setTextAlignment(Qt::AlignCenter);
	//	list->addItem(item);


	//	movies.append(nullptr);
	//}

	//QObject::connect(list->listwidget, &QListWidget::currentItemChanged, list->listwidget, [list, movies](QListWidgetItem* current, QListWidgetItem* previous) {
	//	int preIndex = list->listwidget->row(previous);
	//	int curIndex = list->listwidget->row(current);
	//	if (preIndex >= 0 && movies.at(preIndex) != nullptr)
	//	{
	//		QMovie* pre = movies.at(preIndex);
	//		pre->stop();	//上一个停止
	//		pre->jumpToFrame(0);	//跳到开始画面
	//	}
	//	if (curIndex >= 0 && movies.at(curIndex) != nullptr)
	//	{
	//		QMovie* cur = movies.at(curIndex);
	//		cur->start();	//当前开始
	//	}
	//	});

	////删除指定项
	//QPushButton* button = new QPushButton(&w);  
	//button->setText("delitem0");
	//button->resize(100, 100);
	//QObject::connect(button, &QPushButton::clicked, list, [list]() {
	//	QListWidgetItem* itemDel = list->takeItem(0);
	//	if (itemDel != nullptr)    delete itemDel;
	//	});



	/*
		view
	*/
	 ListWidgetCustom01* list = new ListWidgetCustom01(&w, true);
	 list->resize(800, 500);
	 list->move(200, 200);

	 for (int i = 0; i < 10; i++)
	 {
		 QString user = "user" + QString::number(i);

		 list->addItemView(user, icon1, icon2, icon2);
	 }

	 QPushButton* button = new QPushButton(&w);
	 button->setText("delitem0");
	 button->resize(100, 100);
	 QObject::connect(button, &QPushButton::clicked, list, [list]() {
		 list->removeItemFromModelView(1);
		 });


    w.show();
    return a.exec();
}
```

