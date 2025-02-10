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
	//list->listwidget->setIconSize(QSize(50, 50));			//�趨icon��С
	//list->listwidget->setViewMode(QListView::ListMode);		//�������趨��ʾģʽ
	////list->listwidget->setViewMode(QListView::IconMode);   //�������趨��ʾģʽ
	////list->listwidget->setSpacing(10);						//�趨item֮����
	////list->listwidget->setSelectionMode(QAbstractItemView::MultiSelection);    //�������趨����ѡ

	//QList<QMovie*> movies;	//Ϊ��ʵ�ְ���/hoverʱ�Ų���gif

	//for (int i = 0; i < 100; i++)
	//{
	//	//����icon��clickicon��hovericon����������checkbox
	//	QString user = "user" + QString::number(i);
	//	QListWidgetItem* item = new QListWidgetItem(icon1.pixmap(50, 50), user);
	//	item->setTextAlignment(Qt::AlignCenter);

	//	list->addItem(item, icon2, icon2);					
	//	int index = list->listwidget->count() - 1;			//��ȡ������ӵ�item��index

	//	/*
	//	* ��������ؼ���������qss
	//	*/
	//	QCheckBox* check = new QCheckBox;					//���checkbox
	//	const QString qssStyleCheck = "QCheckBox{height:10px; width:50; background:transparent;}\
	//		QCheckBox::indicator{height:10px; width:50px;}\
	//		QCheckBox::hover{background:blue; border-radius:10px; }\
	//		QCheckBox::checked{background:green; color:white;border-radius:10px; }";
	//	check->setStyleSheet(qssStyleCheck);	//checkbox����ʽ����listwidgetָ��
	//	check->setFixedWidth(100);

	//	QProgressBar* bar = new QProgressBar;	//barҲ��ָ����ʽ
	//	const QString qssStyleBar= "QProgressBar{height:22px; text-align:center; font-size:14px; color:white; border-radius:11px; background:#1D5573;}\
	//		QProgressBar::chunk{border-radius:11px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1 #9900ff);}";
	//	bar->setStyleSheet(qssStyleBar);
	//	bar->setMaximum(100);
	//	bar->setValue(i);
	//	//bar->move(0, 10);	//��Ч
	//	bar->setFixedWidth(100);
	//	
	//	QWidget* container = new QWidget;
	//	QHBoxLayout* layout = new QHBoxLayout;
	//	layout->addWidget(check);
	//	layout->addWidget(bar);
	//	container->setLayout(layout);

	//	list->addWidgetToItem(list->listwidget->item(index), container);	//��ȡ������ӵ�item


	//	movies.append(nullptr);
	//}


	//for (int i = 100; i < 120; i++)
	//{
	//	//�������ı���item��СΪiconʵ�ʴ�С��û����clickedIcon��hoverIcon
	//	QListWidgetItem* item = new QListWidgetItem(icon1.pixmap(50, 50), "aaa");
	//	//item->setSizeHint(icon1.actualSize(QSize(50, 50)));
	//	list->addItem(item,icon2);


	//	movies.append(nullptr);
	//}

	//for (int i = 120; i < 130; i++)
	//{
	//	//��ʾ��̬ͼ���趨��clickicon��δ�趨icon
	//	QString user = "user" + QString::number(i);
	//	QListWidgetItem* item = new QListWidgetItem(user);
	//	item->setTextAlignment(Qt::AlignCenter); //�趨�ı�����
	//	item->setSizeHint(QSize(100, 120));		//gif�趨�߶�100��item�߶��Ը���gif
	//	list->addItem(item, icon2);				

	//	QMovie* movie = new QMovie("G:\\Pictures\\ASUS2013\\snake.gif");
	//	movie->setScaledSize(QSize(100, 100));	//�趨gif�ߴ�
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
	//	movie->jumpToFrame(0);	//û��startʱû�����в���ʾ
	//	movies.append(movie);
	//}

	//for (int i = 130; i < 140; i++)
	//{
	//	//���ı�
	//	QString user = "user" + QString::number(i);
	//	QListWidgetItem* item = new QListWidgetItem(user);
	//	item->setTextAlignment(Qt::AlignCenter);
	//	list->addItem(item);


	//	movies.append(nullptr);
	//}

	////ѡ�ж���������δѡ�ж���ֹͣ
	//QObject::connect(list->listwidget, &QListWidget::currentItemChanged, list->listwidget, [list, movies](QListWidgetItem* current, QListWidgetItem* previous) {
	//	int preIndex = list->listwidget->row(previous);
	//	int curIndex = list->listwidget->row(current);
	//	if (preIndex >= 0 && movies.at(preIndex) != nullptr)
	//	{
	//		QMovie* pre = movies.at(preIndex);
	//		pre->stop();	//��һ��ֹͣ
	//		pre->jumpToFrame(0);	//������ʼ����
	//	}
	//	if (curIndex >= 0 && movies.at(curIndex) != nullptr)
	//	{
	//		QMovie* cur = movies.at(curIndex);
	//		cur->start();	//��ǰ��ʼ
	//	}
	//	});

	////hover����������δhover����ֹͣ
	//QObject::connect(list, &ListWidgetCustom01::hoverItemChanged, list, [list, movies](QListWidgetItem* current, QListWidgetItem* previous) {
	//	int preIndex = list->listwidget->row(previous);
	//	int curIndex = list->listwidget->row(current);
	//	if (preIndex >= 0 && movies.at(preIndex) != nullptr)
	//	{
	//		QMovie* pre = movies.at(preIndex);
	//		pre->stop();	//��һ��ֹͣ
	//		pre->jumpToFrame(0);	//������ʼ����
	//	}
	//	if (curIndex >= 0 && movies.at(curIndex) != nullptr)
	//	{
	//		QMovie* cur = movies.at(curIndex);
	//		cur->start();	//��ǰ��ʼ
	//	}
	//	});

	////ɾ��ָ����
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
