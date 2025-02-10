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

	////选中动画启动，未选中动画停止
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

	////hover动画启动，未hover动画停止
	//QObject::connect(list, &ListWidgetCustom01::hoverItemChanged, list, [list, movies](QListWidgetItem* current, QListWidgetItem* previous) {
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
