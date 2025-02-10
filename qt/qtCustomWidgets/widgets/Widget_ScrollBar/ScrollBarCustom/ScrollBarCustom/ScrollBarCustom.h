#ifndef SCROLLBARCUSTOM_H
#define SCROLLBARCUSTOM_H

#include <QWidget>
#include "ui_ScrollBarCustom.h"
#include <QScrollBar>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class ScrollBarCustom : public QScrollBar
{
	Q_OBJECT

public:
	ScrollBarCustom(QWidget *parent = nullptr, int lenHandler = 0, int widthGroove = 5,int widthHandler = 2);
	~ScrollBarCustom();

private:
	Ui::ScrollBarCustomClass ui;
	QColor colorBorder;	//�߿���ɫ
	QColor colorGroove;	//����ɫ
	QColor colorHandler;//������ɫ
	int m_widthGroove = 0;	//�ۿ��
	int m_widthHandler = 0;	//����Ŀ�ȣ��ڲ۵Ŀ��m_widthGroove�����϶����ֵ��
	int m_lenHandler = 0;	//����ĳ��ȣ�0��ʾ�Ǹ�Բ��

protected:
	virtual void paintEvent(QPaintEvent* e) override;
};

#endif