#pragma once

#include <QWidget>
#include "ui_ScrollBarCustom01.h"
#include <QScrollBar>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class ScrollBarCustom01 : public QScrollBar
{
	Q_OBJECT

public:
	ScrollBarCustom01(QWidget *parent = nullptr);
	~ScrollBarCustom01();

private:
	Ui::ScrollBarCustom01Class ui;
	virtual void paintEvent(QPaintEvent* e) override;
};
