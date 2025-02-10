# 1. 环形加载进度条

---

> LoadingWidget
>
> 

## （1）定时器实现思路实例

![image-20240913233420789](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409140015256.png)

* 定时器调用`update`重绘，在paintEvent函数中修改变量周期性变化，如m_angle。

```cpp
#ifndef ROTATEPROGRESSBAR_H
#define ROTATEPROGRESSBAR_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QPainterPath>

enum class RotateSpeed{very_fast =1, fast=3, medium=5, slow=10};	//旋转速度

class RotateProgressBar :
	public QDialog
{
	Q_OBJECT
public:
	RotateProgressBar(QWidget* pParent = nullptr, bool isModal=true);
	~RotateProgressBar();
protected:
	virtual void paintEvent(QPaintEvent* event) override;	
private slots:
	void  updaterRotation();	//旋转1°刷新显示
private:
	RotateSpeed m_speed = RotateSpeed::medium;	
	double m_angle = 0.0;	
	QColor m_colorStart = QColor("#3BB6FE");
	QColor m_colorEnd = QColor("#FFFFFF");
	QTimer* m_timer = nullptr;

public:
	void setRotateSpeed(RotateSpeed speed);	
	RotateSpeed getRotateSpeed();
	void setColor(QColor color);
	QColor getColor();
public slots:
	void close();
};

#endif
```

```cpp
#include "JcProcessBar.h"

RotateProgressBar::RotateProgressBar(QWidget* pParent, bool isModal) : QDialog(pParent)
{
	this->resize(100, 100);
	m_timer = new QTimer();
	connect(m_timer, &QTimer::timeout, this, &RotateProgressBar::updaterRotation);	// 定时旋转坐标系
	m_timer->start(static_cast<int>(m_speed));
	this->setModal(isModal);	//设置为模态，该窗口不关闭，父窗口不能操作
	//隐藏标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	//背景透明
	setAttribute(Qt::WA_TranslucentBackground, true);
}


RotateProgressBar::~RotateProgressBar()
{
	if (m_timer)
	{
		delete m_timer;
		m_timer = nullptr;
	}
}
void  RotateProgressBar::updaterRotation()
{
	//旋转1度
	m_angle++;
	if (m_angle == 360)
	{
		m_angle = 0;
	}
	update();
}
void RotateProgressBar::paintEvent(QPaintEvent* event)
{//根据QPaintPath画出渐变色的圆弧
	int width = this->width();
	int height = this->height();
	int side = qMin(width, height);

	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.translate(width / 2, height / 2);
	painter.scale(side / 200.0, side / 200.0);

	QConicalGradient gra(QPoint(0, 0), 0);
	gra.setColorAt(0, m_colorStart);
	gra.setColorAt(1, m_colorEnd);
	QBrush brush(gra);

	int radis = 40;
	int sider = 10;
	QRect rect(-radis, -radis, radis * 2, radis * 2);
	QPainterPath path;
	path.arcTo(rect, 0, 270);

	QPainterPath subPath;
	subPath.addEllipse(rect.adjusted(sider, sider, -sider, -sider));
	//这行注释掉就是圆形，加上去就是环形
	path = path - subPath;
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);
	painter.rotate(m_angle);
	painter.drawPath(path);
}

void RotateProgressBar::setRotateSpeed(RotateSpeed speed)
{
	m_speed = speed;
	m_timer->stop();
	m_timer->start(static_cast<int>(m_speed));
}

RotateSpeed RotateProgressBar::getRotateSpeed()
{
	return m_speed;
}

void RotateProgressBar::setColor(QColor color)
{
	m_colorStart = color;
	update();
}

QColor RotateProgressBar::getColor()
{
	return m_colorStart;
}

void RotateProgressBar::close()
{
	QDialog::close();
}
```

```cpp
//main.cpp
 RotateProgressBar* bar = new RotateProgressBar(&w, false);
 bar->setRotateSpeed(RotateSpeed::very_fast);
 bar->move(w.pos().x(), w.pos().y());
 bar->resize(100, 100);
 bar->show();
 bar->setColor(QColor("green"));
```



## （2）动画实现思路

* `Q_PROPERTY`指定成员字段的【读、写】函数名

* `QPropertyAnimation::setPropertyName`设定动画改变的字段值

  ```cpp
  m_animation.setPropertyName("angle");	//动画改变的字段值
  m_animation.setTargetObject(this);		//
  m_animation.setDuration(static_cast<int>(m_speed));	//动画循环一次所需时间（ms)
  m_animation.setLoopCount(-1);	//循环次数，-1表示一直循环
  m_animation.setEasingCurve(QEasingCurve::Linear);	//
  ```

* 使用动画替代手动设定定时器，动画会自动循环调用setXXX修改指定字段的值，在set方法里调用`update`就会重绘产生动画效果。

## （3）多种类加载动画

```cpp
//main.cpp
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
	//sc->resize(200, 200);
	sc->setSpeed(LoadingWidget::AnimationSpeed::VeryFast);
	sc->move(100, 200);
	sc->setColor(QColor("lightblue"));
	//sc->setColor(QList<QColor>{"#3BB6FE", "red", "green", "blue", "yellow"});
	sc->setText(QString("loading"));
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
```

```cpp
#ifndef LOADINGANIMWIDGET_H
#define LOADINGANIMWIDGET_H
#include <QPropertyAnimation>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>


class LoadingWidget :public QWidget
{
    Q_OBJECT
        Q_PROPERTY(qreal angle READ angle WRITE setAngle)

public:
    enum class LoadingWidgetStyle
    {
        TubeCircle = 0,       //连续环
        TubeGradiantCircle,   //渐变色连续环
        SpotCircle,           //单个点环带小尾巴
        SpotsCircle,          //多个点环
        StickCircle,          //多个小棍组成环
        TextCircle,           //文字围绕环旋转
        SlinkyCircle,         //弹簧圈
        ZoomingBalls,         //依次放大小球
        ThreeMovingZoomingBalls,  //小球先大后小
        RippleWave,            //涟漪形
        TextInBouncingBox,       //跳动文本框
        ExpandingScroll,         //圆环转动两圈后，卷轴展示
        ThreeRevolvingBalls,     //三色小球旋转
        InfinityLoop,            //无穷符号
        FourRotatingFireBall,    //四个旋转的火球
        Pacman,                 //吃豆人
        PendulumClock,          //钟摆
        JellyInBox,            //伸缩果冻条
        LoopedRingWithText,     //三个旋转环加中间文字
        Radar,                   //雷达
        VolumeBar,               //音量柱
        VolumeBarTiny,            //音量柱简化版
        FillGlassBead,           //球里注水
        Hourglass,               //漏斗
        RhombusShift,             //移动的4个菱形
        TiltingBricks             //滚动的3个菱形
    };

    enum class AnimationSpeed
    {
        VeryFast = 1000,    //动画周期（ms)
        Fast = 2000,
        Medium = 3000,
        Slow = 4000
    };

    LoadingWidget(QWidget* parent = nullptr);
    virtual ~LoadingWidget();

    qreal angle()const;
    void setAngle(qreal an);

    LoadingWidget::AnimationSpeed speed() const;
    void setSpeed(AnimationSpeed speed);

    QColor color() const;
    virtual void setColor(QColor color);
    virtual void setColor(const QList<QColor>& colorList);

    virtual void setTextColor(QColor color);

    virtual void setText(const QString& text);

    virtual void setFont(QFont font);

public slots:
    virtual void exec();
    virtual void start();
    virtual void stop();
protected:
    QPropertyAnimation m_animation;   
    qreal m_angle = 0;
    LoadingWidget::AnimationSpeed m_speed; 
    QColor m_color = QColor("black");
    QList<QColor> m_colorList;
    QString m_text = "";
    QColor m_textColor = QColor("black");
    QFont m_font;
};

#endif
```

```cpp
#include "LoadingWidget.h"

LoadingWidget::LoadingWidget(QWidget* parent) :QWidget(parent)
{
	resize(100, 100);
	m_speed = LoadingWidget::AnimationSpeed::Fast;
	m_colorList = QList<QColor>{ QColor::Invalid };

	m_animation.setPropertyName("angle");
	m_animation.setTargetObject(this);
	m_animation.setDuration(static_cast<int>(m_speed));
	m_animation.setLoopCount(-1);//run forever
	m_animation.setEasingCurve(QEasingCurve::Linear);
}
LoadingWidget::~LoadingWidget() {}

void LoadingWidget::exec() 
{
	if (m_animation.state() == QAbstractAnimation::State::Stopped) 
	{
		start();
	}
	else 
	{
		stop();
	}
}

void LoadingWidget::start() 
{
	m_animation.setStartValue(0);
	m_animation.setEndValue(360);
	m_animation.start();
}

void LoadingWidget::stop() 
{
	m_animation.stop();
}

qreal LoadingWidget::angle()const { return m_angle; }

void LoadingWidget::setAngle(qreal an) 
{
	if (m_angle != an)
	{
		m_angle = an;
		update();
	}
}

LoadingWidget::AnimationSpeed LoadingWidget::speed() const
{
	return m_speed;
}

void LoadingWidget::setSpeed(AnimationSpeed speed)
{
	if (m_speed != speed)
	{
		m_speed = speed;
		m_animation.setDuration(static_cast<int>(m_speed));
	}
}

QColor LoadingWidget::color() const
{
	return m_color;
}

void LoadingWidget::setColor(QColor color)
{
	if (m_color != color)
	{
		m_color = color;
		update();
	}
}

void LoadingWidget::setColor(const QList<QColor>& colorList)
{
	m_colorList = std::move(colorList);
	update();
}

void LoadingWidget::setTextColor(QColor color)
{
	if (m_textColor != color)
	{
		m_textColor = color;
		update();
	}
}

void LoadingWidget::setText(const QString& text)
{
	if (m_text != text)
	{
		m_text = text;
		update();
	}
}

void LoadingWidget::setFont(QFont font)
{
	if (m_font != font)
	{
		m_font = font;
		update();
	}
}
```

```cpp
//工厂类LoadingWidgetFactory.h
#ifndef LOADINGWIDGETFACTORY_H
#define LOADINGWIDGETFACTORY_H
#include <QObject>
#include "LoadingWidget.h"
#include "SpotCircle.h"
#include "SpotsCircle.h"
#include "TubeGradiantCircle.h"
#include "StickCircle.h"
#include "TextCircle.h"
#include "SlinkyCircle.h"
#include "ZoomingBalls.h"
#include "RippleWave.h"
#include "TextInBouncingBox.h"
#include "ExpandingScroll.h"
#include "ThreeRevolvingBalls.h"
#include "InfinityLoop.h"
#include "ThreeMovingZoomingBalls.h"
#include "FourRotatingFireBall.h"
#include "Pacman.h"
#include "PendulumClock.h"
#include "JellyInBox.h"
#include "LoopedRingWithText.h"
#include "Radar.h"
#include "VolumeBar.h"
#include "VolumeBarTiny.h"
#include "FillGlassBead.h"
#include "Hourglass.h"
#include "RhombusShift.h"
#include "TiltingBricks.h"

class LoadingWidgetFactory  : public QObject
{
	Q_OBJECT

public:
	LoadingWidgetFactory(QObject *parent);
	~LoadingWidgetFactory();

	static LoadingWidget* createLoadingWidget(LoadingWidget::LoadingWidgetStyle style, QWidget* parent = nullptr);
};

#endif
```

```cpp
//LoadingWidgetFactory.cpp
#include "LoadingWidgetFactory.h"



LoadingWidgetFactory::LoadingWidgetFactory(QObject *parent)
	: QObject(parent)
{}

LoadingWidgetFactory::~LoadingWidgetFactory()
{}

LoadingWidget* LoadingWidgetFactory::createLoadingWidget(LoadingWidget::LoadingWidgetStyle style, QWidget* parent)
{
	switch (style)
	{
	case LoadingWidget::LoadingWidgetStyle::TubeCircle:
		return new TubeGradiantCircle(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::TubeGradiantCircle:
		return new TubeGradiantCircle(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::SpotCircle:
		return new SpotCircle(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::SpotsCircle:
		return new SpotsCircle(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::StickCircle:
		return new StickCircle(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::TextCircle:
		return new TextCircle(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::SlinkyCircle:
		return new SlinkyCircle(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::ZoomingBalls:
		return new ZoomingBalls(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::RippleWave:
		return new RippleWave(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::TextInBouncingBox:
		return new TextInBouncingBox(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::ExpandingScroll:
		return new ExpandingScroll(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::ThreeRevolvingBalls:
		return new ThreeRevolvingBalls(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::InfinityLoop:
		return new InfinityLoop(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::ThreeMovingZoomingBalls:
		return new ThreeMovingZoomingBalls(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::FourRotatingFireBall:
		return new FourRotatingFireBall(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::Pacman:
		return new Pacman(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::PendulumClock:
		return new PendulumClock(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::JellyInBox:
		return new JellyInBox(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::LoopedRingWithText:
		return new LoopedRingWithText(parent);
	case LoadingWidget::LoadingWidgetStyle::Radar:
		return new Radar(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::VolumeBar:
		return new VolumeBar(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::VolumeBarTiny:
		return new VolumeBarTiny(parent);
	case LoadingWidget::LoadingWidgetStyle::FillGlassBead:
		return new FillGlassBead(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::Hourglass:
		return new Hourglass(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::RhombusShift:
		return new RhombusShift(parent);
		break;
	case LoadingWidget::LoadingWidgetStyle::TiltingBricks:
		return new TiltingBricks(parent);
		break;
	default:
		break;
	}

	return nullptr;
}
```

### TubeGradiantCircle

![image-20240913233420789](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409140015256.png)

```cpp
void setColor(QColor color);	//设定圆环颜色
void setText(QString& text);	//修改文本显示
void setTextColor(QColor text);	//设置文本颜色
void setFont(QFont font);	//设置文本字体、大小
void setSpeed(AnimationSpeed speed);	//设置动画速度
resize();	//大小
```

### SpotCircle

![image-20240915220216150](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409152202287.png)

```cpp
void setColor(QColor color);	//设定颜色
void setText(QString& text);	//修改文本显示
void setTextColor(QColor color);	//设定文字颜色
void setFont(QFont);		//设置字体大小
void setSpeed(AnimationSpeed speed);	//设定动画速度
resize();	//大小
```

### SpotsCircle

![image-20240915220310748](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409152203796.png)

```cpp
void setColor(QColor color);	//设定颜色
void setText(QString& text);	//修改文本显示
void setTextColor(QColor color);	//设定文字颜色
void setFont(QFont);		//设置字体大小
void setSpeed(AnimationSpeed speed);	//设定动画速度
resize();	//大小
```

### StickCircle

![image-20240915220419155](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409152204205.png)

```cpp
void setColor(QColor color);	//设定颜色
void setText(QString& text);	//修改文本显示
void setTextColor(QColor color);	//设定文字颜色
void setFont(QFont);		//设置字体大小
void setSpeed(AnimationSpeed speed);	//设定动画速度
resize();	//大小
```

### TextCircle

![image-20240915220504990](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409152205041.png)

```cpp
void setColor(QColor color);	//设定颜色
void setText(QString& text);	//修改文本显示
void setTextColor(QColor color);	//设定文字颜色
void setFont(QFont);		//设置字体大小
void setSpeed(AnimationSpeed speed);	//设定动画速度
```

### SlinkyCircle

![image-20240915224137761](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409152241835.png)

```cpp
void setColor(QColor color);	//设定颜色
void setText(const QString& text);
void setTextColor(QColor color);	//设定文字颜色
void setFont(QFont);		//设置字体大小
void setSpeed(AnimationSpeed speed);	//设定动画速度
resize();	//大小
```

### ZoomingBalls

![image-20240916105223152](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409161052279.png)

```cpp
void setColor(QList<QColor> colors);	//设定小球颜色，小球个数由colors.size()决定，显示不全注意调整resize()
resize();	//大小
```

### RippleWave

![image-20240916111709129](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409161117202.png)

```cpp
void setColor(QColor color);	//设定颜色
resize();	//大小
```

### TextInBouncingBox

![image-20240918164540261](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409181645404.png)

```cpp
TextInBouncingBox(QWidget* parent, const QString& str);	//构造
void setColor(QList<QColor> colors);	//设定每个字符的背景色，若指定的颜色数量<字符数，则以指定的第一个颜色作为所有字符的背景色
void setText(QString& text);		//设定显示字符
void setTextColor(QColor color);	//设定文本颜色
void setFont(QFont("Microsoft YaHei", 16, 2));				//设定方框大小、文本字体、字号、字体风格
resize();	//大小
```

### ExpandingScroll

![image-20240916173628760](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409161736883.png)![image-20240916173643990](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409161736070.png)

```cpp
void setText(QString& str);	//设定文字
void setTextColor(QColor color);	//设定文字颜色
void setColor(QColor color);	//设定背景颜色
void setFont(QFont);		//设置字体大小
void setSpeed(AnimationSpeed speed);	//设定动画速度
resize();	//大小
```

### ThreeRevolvingBalls

![image-20240916214055846](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409162141996.png)

```cpp
void setColor(QList<QColor> colors);	//设定每个小球的颜色，小球个数由colors.size()决定
resize();	//大小
```

### InfinityLoop

![image-20240916214953026](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409162149105.png)

```cpp
void setColor(QList<QColor> colors);	//设定颜色：背景、移动部分
resize();	//大小
```

### ThreeMovingZoomingBalls

![image-20240916220027778](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409162200853.png)

```cpp
void setColor(QColor color);	//设定小球颜色
resize();	//大小
```

### PendulumClock

![image-20240916223006608](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409162230675.png)

```cpp
void setColor(QColor color);	//设定颜色
```

### FourRotatingFireBall

![image-20240916223200031](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409162232096.png)

```cpp
void setColor(QList<QColor> colors);	//设定颜色
void setText(const QString& text);
void setTextColor(QColor color);	//设定文字颜色
void setFont(QFont);		//设置字体大小
void setSpeed(AnimationSpeed speed);	//设定动画速度
resize();	//大小
```

### Pacman

![image-20240916223330499](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409162233564.png)

```cpp
void setColor(QList<QColor> colors);	//设定颜色：眼睛、身体、豆子
```

### LoopedRingWithText

文本有移动灯光效果

![image-20240917111021763](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409171110844.png)

```cpp
void setText(QString& text);	//设定文本
void setColor(QList<QColor> colors);	//设定颜色：背景、内部
resize();	//大小
```

### JellyInBox

![image-20240917111141156](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409171111232.png)

```cpp
void setColor(QList<QColor> colors);	//设定颜色：外框、内部移动部分
```

### Radar

![image-20240917112743650](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409171127738.png)

```cpp
void setColor(QColor colors);	//设定颜色，背景透明
resize();	//大小
```

### VolumeBar

![image-20240917160128601](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409171601731.png)

```cpp
void setColor(QColor color);	//设定颜色
resize();	//大小
```

### VolumeBarTiny

![image-20240917160717146](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409171607231.png)

```cpp
void setColor(QColor color);	//设定颜色
```

### Hourglass

![image-20240917231146459](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409172311623.png)

```cpp
void setColor(QList<QColor> colors);	//设定颜色：外框、沙
void setColumnVisibility(bool);			//外框两边是否封闭
resize();	//大小
```

### FillGlassBead

![image-20240917231423429](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409172314522.png)

```cpp
void setColor(QColor color);	//设定颜色
void setWaveType(bool);			//设定水面波动、平静
```

### RhombusShift

![image-20240918101102255](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409181011592.png)

```cpp
void setColor(QList<QColor> colors);	//设定四个菱形的颜色
resize();	//大小
```

### TiltingBricks

![image-20240918101951189](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409181019291.png)

```cpp
void setColor(QList<QColor> colors);	//设定三个菱形的颜色
resize();	//大小
```

### TextPoint

在指定的文本（默认是loading）后加三个点点点循环出现。

```cpp
 virtual void setTextColor(QColor color);
 virtual void setText(const QString& text);
 virtual void setFont(QFont font);
```

