#pragma once

#include <QWidget>
#include "ui_SideBar.h"
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QStyleOption>
#include <QPainter>

/// <summary>
/// 由fixedWidth和leftMargin、rightMargin相加自动决定宽度
/// </summary>
class SideBar : public QWidget
{
	Q_OBJECT

public:
	SideBar(QWidget *parent = nullptr);
	SideBar(QWidget* parent = nullptr, bool adaptive=false, int leftMargin = 0, int rightMargin = 0, int verticalSpacing = 0, int horizontalSpacing = 0, int fixedWidth = 0);
	~SideBar();


	int increasedWidth = 200;	//伸展长度

	bool isExpanded = false;	//当前状态，是否处于伸展

	void shrink();	//收缩

	void expand();	//伸展

	void setIncreasedWidth(quint32 increasedWidth);	//设定在固定长度基础上伸展多少
	
	int getIncreasedWidth();
	
	void addWidget(QWidget* item, QSize itemSize = QSize(0,0));

	void setSideBarContentsHeightMargins(int top, int bottom);
	
	virtual void resizeEvent(QResizeEvent* event) override;

	virtual void paintEvent(QPaintEvent* event);

	int getFixedWidth();

private:
	Ui::SideBarClass ui;
	
	bool m_adaptive = false;	//内部控件宽度是否自适应
	
	QPropertyAnimation* animation;	//收缩、伸展动画

	bool isAnimationRunning = false;

	int m_fixedWidth = 0;		//收缩状态sidebar宽度
	
	bool m_isInit = true;		//是否是初始化，m_fixedWidth只在初始化时设定大小

	QSize shrinkSize;
	
	QSize expandSize;

	QVBoxLayout* glay_innerLay;	//内部布局

signals:
	void expandFinished();
	void shrinkFinished();
	void finished();
	void expandStart();
	void shrinkStart();
	void widthChanged(int width);
};
