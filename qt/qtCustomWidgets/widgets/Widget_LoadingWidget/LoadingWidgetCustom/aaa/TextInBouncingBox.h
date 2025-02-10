#ifndef TEXTINBOUNCINGBOX_H
#define TEXTINBOUNCINGBOX_H

#include "LoadingWidget.h"

class TextInBouncingBox :public LoadingWidget {//显示装在上下跳动的盒子里的字符
public:
	TextInBouncingBox(QWidget* parent = nullptr, const QString& str = "Loading...");
protected:
	void paintEvent(QPaintEvent*);
private:
};

#endif