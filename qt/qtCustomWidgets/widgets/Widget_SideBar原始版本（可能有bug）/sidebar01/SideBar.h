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
/// ��fixedWidth��leftMargin��rightMargin����Զ��������
/// </summary>
class SideBar : public QWidget
{
	Q_OBJECT

public:
	SideBar(QWidget *parent = nullptr);
	SideBar(QWidget* parent = nullptr, bool adaptive=false, int leftMargin = 0, int rightMargin = 0, int verticalSpacing = 0, int horizontalSpacing = 0, int fixedWidth = 0);
	~SideBar();


	int increasedWidth = 200;	//��չ����

	bool isExpanded = false;	//��ǰ״̬���Ƿ�����չ

	void shrink();	//����

	void expand();	//��չ

	void setIncreasedWidth(quint32 increasedWidth);	//�趨�ڹ̶����Ȼ�������չ����
	
	int getIncreasedWidth();
	
	void addWidget(QWidget* item, QSize itemSize = QSize(0,0));

	void setSideBarContentsHeightMargins(int top, int bottom);
	
	virtual void resizeEvent(QResizeEvent* event) override;

	virtual void paintEvent(QPaintEvent* event);

	int getFixedWidth();

private:
	Ui::SideBarClass ui;
	
	bool m_adaptive = false;	//�ڲ��ؼ�����Ƿ�����Ӧ
	
	QPropertyAnimation* animation;	//��������չ����

	bool isAnimationRunning = false;

	int m_fixedWidth = 0;		//����״̬sidebar���
	
	bool m_isInit = true;		//�Ƿ��ǳ�ʼ����m_fixedWidthֻ�ڳ�ʼ��ʱ�趨��С

	QSize shrinkSize;
	
	QSize expandSize;

	QVBoxLayout* glay_innerLay;	//�ڲ�����

signals:
	void expandFinished();
	void shrinkFinished();
	void finished();
	void expandStart();
	void shrinkStart();
	void widthChanged(int width);
};
