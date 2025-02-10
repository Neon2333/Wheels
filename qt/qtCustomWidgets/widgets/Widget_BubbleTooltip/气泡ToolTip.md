# 1. 结构

![image-20240926023044227](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409260230377.png)

* 继承QWidget，容器Widget（水平布局），内部两个label
* 红色部分：透明部分，和灰黑色部分之间留有不上色部分供画三角形。这里为了方便看，整个上了红色。
* 绿色：label_icon显示图标，居中
* 蓝色：label_tips，居中、换行

* 根据icon的实际高度+上下透明部分、多行文本显示实际高度+上下透明部分，取较大值，resize整个ToolTip的高度。宽度设为固定值较为美观，可在构造函数中设置宽度。

* 灰黑色：paint绘制的一个圆角矩形，用来作为背景色
* 三角形：三个点
* 动画使得有慢慢的出现效果，不突兀

不画灰黑色的话就是这种效果：

![image-20240926024234737](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202409260242781.png)

# 2. 函数

```cpp
BubbleTipsWidget(QWidget *parent = nullptr, int widthFixed = 300);
~BubbleTipsWidget();

//背景色
QColor backColor() const;
void setBackColor(QColor color);

// 设置三角方向(左上右下)，位置系数(宽度 * 系数)
void setDirect(DIRECT direct = DIRECT::DIRECT_TOP, double size = 0.75);

//文本内容
void setContent(const QString& content, QColor color = {});

//文本font
void setContentFont(QFont font = {});

//文本边距
void setLeftTopMargin(int leftMargin = LEFT_MARGIN, int topMargin = TOP_MARGIN);

//设定图标、尺寸（尺寸要设定适当，确保图标完整显示）
void setIcon(QIcon icon, int w=100, int h=100);

//根据三角形顶点，确定整个bubbletips的左上角坐标
void setPositionByTriangle(int x, int y);

//设定要弹出tooltip的目标控件，自动按照鼠标进入目标控件的位置设置箭头方向、位置
void setAutoPosition(bool isAuto, QWidget* target);

//动画弹出显示
void animeShow();

//动画消失
void animeClose();
```

# 3. 使用

* 在父窗口重载`eventFilter`，给需要弹出tooltip的控件安装事件过滤器。
* 在`QEvent::HoverEnter`事件中创建对象，并`animeShow()`
* 若想要使用`setAutoPosition`，需在事件过滤器中把`obj`传入`target`参数

```cpp
#include "mainWindow.h"
#include <QHoverEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setMouseTracking(true);

    button = new QPushButton(this);
    button->move(0, 0);
    button->resize(100, 50);
    button->setText("tool button");
    button->installEventFilter(this);

    button1 = new QPushButton(this);
    button1->move(400, 400);
    button1->resize(100, 50);
    button1->setText("test");
    button1->installEventFilter(this);
}

MainWindow::~MainWindow()
{}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if(obj==tips) return QMainWindow::eventFilter(obj, event);  //防止移动到tips上触发hoverleave

    if (event->type() == QEvent::HoverEnter)
    {
        qDebug() << "HoverEnter";

        QHoverEvent* hoverEvent = dynamic_cast<QHoverEvent*>(event);

        tips = new BubbleTipsWidget(this, 200);
       
        QFont f;
        f.setFamily("Microsoft YaHei UI");
        f.setPixelSize(14);
        tips->setContentFont(f);

        tips->setBackColor(QColor(48, 49, 51, 240));
        tips->setDirect(DIRECT::DIRECT_LEFT, 0.4);
        tips->setIcon(QIcon("E:\\WorkSpace\\icons\\unbrella_filled"));
        //tips->setContent(tr("this is a tool tip...this is a tool tip...this is a tool tip...this is a tool tip..."), QColor(Qt::white));
        tips->setContent(tr("this is a tool tip..."), QColor(Qt::white));
        tips->setAutoPosition(true, button1);
        //tips->show();
        tips->animeShow();

        return true;
    }
    else if (event->type() == QEvent::HoverLeave)
    {
        qDebug() << "HoverLeave";
        tips->animeClose();
        return true;
    }

    return QMainWindow::eventFilter(obj, event);	//没安装过滤器的，调用默认的过滤器
}   
```

