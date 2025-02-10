### 设计：

* **纯中文环境下，纯文本的导航图标比icon+文本的图标射击更简明、易于理解。**



# 1. 样式1

---

> * 横向、导航按钮列表、点击按钮时背景高亮和阴影会连续移动到点击按钮处、按钮对应高亮颜色不同、移动过程中颜色渐变。
>
> ![image-20250204170132052](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202502041701134.png)
>
> ![image-20250204170229289](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202502041702376.png)
>
> ![image-20250204170846374](https://raw.githubusercontent.com/Neon2333/ImageHost/main/202502041708445.png)

## （1）实现思路

* QLabel作为背景颜色，填充整个控件，z=0。
* QLabel作为高亮，应用阴影，尺寸同添加的按钮，z=1。
* 按钮使用`QToolButton`可设置icon和text相对位置，通过`QButtonGroup`管理按钮，以`QHBoxLayout`管理布局，颜色`transparent`，填充整个控件，z=2。
* 无按钮选中时，高亮部分不显示。
* 高亮部分不显示时，当前选中按钮为`nullptr`。此时选中按钮，高亮部分直接显示在选中按钮位置。
* **高亮部分不显示有2种情况：没有任何按钮被选中，已有的选中按钮被删除。**
* 高亮部分已显示时，当前选中按钮非`nullptr`。此时选中其他按钮，高亮部分通过动画移动位置、改变颜色。

* 定义`append()、insert()、delete()`函数实现添加、插入、删除按钮。

* 添加、插入：

  高亮部分未处于移动过程中时，要保持在当前选中按钮`m_curBtn`上。处于移动过程中时，要在移动结束时，保持在当前选中按钮`m_curBtn`上。

  新增按钮通过bitmap自动分配`id`，存储`id`和视觉上的`index`之间的对应关系：`(id,index)`。

  存储`id`和按钮颜色之间对应关系：`(id, color)`。

  新增按钮时，超出可分配ID最大数量时无效。

* 删除：

  删除的是当前选中按钮`m_curBtn`时，高亮部分消失。直到再次点击时，直接出现在选中按钮位置。

  当前无按钮时，删除无效。

* 定义设定背景色的函数
* 定义设定icon尺寸的函数
* 定义设定text尺寸的函数
* 定义设定高亮移动动画速度的函数
* 定义设定按钮数量最大值的函数
* 定义设定内边距的函数（按钮组相对于控件边框的外边距`setMargins()`）

* 按钮尺寸和控件尺寸关系：

  高度：`控件高度-marginTop-marginBottom`

  宽度：默认尺寸宽度100（设为`setMinimumSize`）、定义设定宽度的函数

* 动画：移动高亮部分
* 动画：改变高亮、阴影颜色
* 定义获取按钮的函数，用于`connect`

## （2）函数

```cpp
//设定可增加按钮最大数量
void setBtnCountMax(int maxCount);
const int btnCountMax() const;

//设定背景颜色
void setBackGround(QColor bgcolor=QColor("black"));
//设定按钮最小宽度
void setButtonMinWidth(int w);
//设定内边距
void setPaddings(int left, int top, int right, int bottom);
//设定icon尺寸
void setIconSize(QSize iconSize);
//设定文本尺寸（px)
void setTextSize(int pixel);
//设定动画移速(ms)
void setMoveSpeed(int milliseconds);

//添加按钮
void appendButton(QIcon icon, QString text, QColor iconColor=QColor("white"), QColor textColor=QColor("white"), QColor btnColor=QColor(qRgba(247, 59, 89, 150)));
//插入按钮
void insertButton(int index, QIcon icon, QString text, QColor iconColor=QColor("white"), QColor textColor=QColor("white"), QColor btnColor=QColor(qRgba(247, 59, 89, 150)));
//移除按钮
void removeButton(int index, int id);
//根据index获取按钮唯一ID
int btnID(int btnIndex) const;
//根据ID获取按钮
QPushButton& btn(int btnID) const;
//获取当前按钮
QPushButton& curBtn() const;
```









