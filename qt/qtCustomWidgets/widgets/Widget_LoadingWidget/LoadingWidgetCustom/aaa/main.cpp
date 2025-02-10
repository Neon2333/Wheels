#include "aaa.h"
#include <QtWidgets/QApplication>
#include "LoadingWidgetFactory.h"
//#include <QTextCodec>
#include <QThread>
#include <QTimer>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

	aaa w;
	w.move(500, 500);
	w.resize(500, 500);

	LoadingWidget* sc = LoadingWidgetFactory::createLoadingWidget(LoadingWidget::LoadingWidgetStyle::TubeGradiantCircle, &w);
	sc->resize(400, 400);
	//sc->resize(100, 100);
	sc->setSpeed(LoadingWidget::AnimationSpeed::Fast);
	sc->move(0, 0);
	//sc->setColor(QColor("lightblue"));
	//sc->setColor(QList<QColor>{"#3BB6FE", "red", "green", "blue", "yellow"});
	//sc->setText(QString("loading"));
	sc->setTextColor(QColor("red"));
	sc->exec();
	w.show();

	/*QTimer timer(&w);
	timer.setInterval(1000);
	QObject::connect(&timer, &QTimer::timeout, sc, [=]() {
		static int n = 0;
		QString str = QString(QString::number(n++) + QString("%"));
		sc->setText(str);
		});
	timer.start();*/

	return a.exec();
}
