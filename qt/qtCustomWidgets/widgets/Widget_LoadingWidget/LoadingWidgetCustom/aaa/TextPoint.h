#pragma once

#include <QWidget>
#include "LoadingWidget.h"
#include "ui_TextPoint.h"

class TextPoint : public LoadingWidget
{
	Q_OBJECT

public:
	TextPoint(QWidget *parent = nullptr, const QString& str = "Loading");
	~TextPoint();

protected:
	void paintEvent(QPaintEvent*);

private:
	Ui::TextPointClass ui;
};
