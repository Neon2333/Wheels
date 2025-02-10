#pragma once

#include <QPushButton>
#include "ui_DelayButton.h"
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

class DelayButton : public QPushButton
{
	Q_OBJECT

	Q_PROPERTY(qreal progress READ getProgress WRITE setProgress)
		

public:
	DelayButton(QWidget *parent = nullptr);
	~DelayButton();
	bool checked = false;
	void setUnchecked();

	int arcWidth = 10;
	QIcon icon_normal;
	QIcon icon_hover;
	QIcon icon_checked;


private:
	Ui::DelayButtonClass ui;
	
	void setProgress(qreal p);
	qreal getProgress();
	qreal progress = 0.0;
	QPropertyAnimation* animation;

protected:
	void paintEvent(QPaintEvent* event) override;
};
