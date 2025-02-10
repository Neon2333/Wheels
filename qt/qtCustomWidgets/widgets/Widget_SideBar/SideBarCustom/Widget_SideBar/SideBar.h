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
/// �����̶����򣬿��=m_fixedWidth���Ҳ�Ϊ��״����glay_innerLayRight
/// ��ӿؼ���addWidget��addFixedSizeWidget����ӵĿؼ��ֱ��ǻ���sidebar��ȸı���ı��ȣ��̶���ȡ�
/// </summary>
class SideBar : public QWidget
{
	Q_OBJECT

public:
	//SideBar(QWidget *parent = nullptr);
	SideBar(QWidget* parent = nullptr, int fixedWidth = 30, int leftMargin = 0, int rightMargin = 0, int verticalSpacing = 0, int horizontalSpacing = 0);
	~SideBar();

	bool isExpanded = false;	//��ǰ״̬���Ƿ�����չ
	
	bool isAnimationRunning = false;	//�����Ƿ����ڽ���

	int increasedWidth = 200;	//��չ���ӵĿ��
	int getIncreasedWidth();	
	void setIncreasedWidth(quint32 increasedWidth);	//�趨������״̬��Ȼ�������չ����

	int getShrinkWidth() const;
	void setShrinkWidth(const int shrinkWidth);

	int getFixedWidth() const;

	void setIsInit(bool isInit);
	bool getIsInit();

	void shrink();	//����

	void expand();	//��չ

	void addWidget(QWidget* widget, QSize widgetSize, int row, int column, Qt::Alignment alignment = Qt::Alignment());
	void addFixedSizeWidget(QWidget* widget, QSize widgetSize, int row, int column, Qt::Alignment alignment = Qt::Alignment());
	
	void addWidget(QWidget* widget, QSize widgetSize, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment());
	void addFixedSizeWidget(QWidget* widget, QSize widgetSize, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment());

	void setSideBarContentsHeightMargins(int top, int bottom);
	
private:
	Ui::SideBarClass ui;

	QPropertyAnimation* animation;	//��������չ����

	bool m_isInit = true;		//�Ƿ��ǳ�ʼ�����̣������趨��ʼ��ȡ��ڵ�һ�ε���shrink()��expand()֮����Ϊfalse��

	int m_shrinkWidth = 0;		//����״̬sidebar���

	QSize shrinkSize;			//����״̬�³ߴ磬���=m_fixedWidth+glay_innerLayRight��ȣ���ӵ�widget��spacing��margin������

	QSize expandSize;			//��չ״̬�¿�ȣ�shrinkSize+increasedWidth

	QSpacerItem* placeholder_fixedBar;  //�̶�����ռλ
	int m_fixedWidth = 0;				//�̶�������

	QHBoxLayout* hlay_innerLay;			//�ڲ�����=placeholder_fixedBar+glay_innerLayRight
	QGridLayout* glay_innerLayRight;	//�ڲ����ֻ����

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
