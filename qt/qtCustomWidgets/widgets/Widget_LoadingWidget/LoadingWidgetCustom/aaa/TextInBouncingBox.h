#ifndef TEXTINBOUNCINGBOX_H
#define TEXTINBOUNCINGBOX_H

#include "LoadingWidget.h"

class TextInBouncingBox :public LoadingWidget {//��ʾװ�����������ĺ�������ַ�
public:
	TextInBouncingBox(QWidget* parent = nullptr, const QString& str = "Loading...");
protected:
	void paintEvent(QPaintEvent*);
private:
};

#endif