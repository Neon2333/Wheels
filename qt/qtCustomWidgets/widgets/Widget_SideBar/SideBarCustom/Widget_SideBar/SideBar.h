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
/// 包含固定区域，宽度=m_fixedWidth。右侧为网状布局glay_innerLayRight
/// 添加控件：addWidget，addFixedSizeWidget。添加的控件分别是会随sidebar宽度改变而改变宽度，固定宽度。
/// </summary>
class SideBar : public QWidget
{
	Q_OBJECT

public:
	//SideBar(QWidget *parent = nullptr);
	SideBar(QWidget* parent = nullptr, int fixedWidth = 30, int leftMargin = 0, int rightMargin = 0, int verticalSpacing = 0, int horizontalSpacing = 0);
	~SideBar();

	bool isExpanded = false;	//当前状态，是否处于伸展
	
	bool isAnimationRunning = false;	//动画是否正在进行

	int increasedWidth = 200;	//伸展增加的宽度
	int getIncreasedWidth();	
	void setIncreasedWidth(quint32 increasedWidth);	//设定在收缩状态宽度基础上伸展多少

	int getShrinkWidth() const;
	void setShrinkWidth(const int shrinkWidth);

	int getFixedWidth() const;

	void setIsInit(bool isInit);
	bool getIsInit();

	void shrink();	//收缩

	void expand();	//伸展

	void addWidget(QWidget* widget, QSize widgetSize, int row, int column, Qt::Alignment alignment = Qt::Alignment());
	void addFixedSizeWidget(QWidget* widget, QSize widgetSize, int row, int column, Qt::Alignment alignment = Qt::Alignment());
	
	void addWidget(QWidget* widget, QSize widgetSize, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment());
	void addFixedSizeWidget(QWidget* widget, QSize widgetSize, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment());

	void setSideBarContentsHeightMargins(int top, int bottom);
	
private:
	Ui::SideBarClass ui;

	QPropertyAnimation* animation;	//收缩、伸展动画

	bool m_isInit = true;		//是否是初始化过程，用于设定初始宽度。在第一次调用shrink()或expand()之后置为false。

	int m_shrinkWidth = 0;		//收缩状态sidebar宽度

	QSize shrinkSize;			//收缩状态下尺寸，宽度=m_fixedWidth+glay_innerLayRight宽度（添加的widget和spacing、margin决定）

	QSize expandSize;			//伸展状态下宽度，shrinkSize+increasedWidth

	QSpacerItem* placeholder_fixedBar;  //固定区域占位
	int m_fixedWidth = 0;				//固定区域宽度

	QHBoxLayout* hlay_innerLay;			//内部布局=placeholder_fixedBar+glay_innerLayRight
	QGridLayout* glay_innerLayRight;	//内部布局活动区域

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void showEvent(QShowEvent* event) override;
	virtual void paintEvent(QPaintEvent* event);

signals:
	void expandFinished();
	void shrinkFinished();
	void finished();
	void expandStart();
	void shrinkStart();
	void widthChanged(int width);
	void shrinkWidthChanged(int newShrinkWidth);
	void hasShown();
};
