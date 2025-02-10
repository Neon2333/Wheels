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
	QColor colorBorder;	//边框颜色
	QColor colorGroove;	//槽颜色
	QColor colorHandler;//滑块颜色
	int m_widthGroove = 0;	//槽宽度
	int m_widthHandler = 0;	//滑块的宽度（在槽的宽度m_widthGroove基础上多的数值）
	int m_lenHandler = 0;	//滑块的长度（0表示是个圆）

protected:
	virtual void paintEvent(QPaintEvent* e) override;
};

#endif