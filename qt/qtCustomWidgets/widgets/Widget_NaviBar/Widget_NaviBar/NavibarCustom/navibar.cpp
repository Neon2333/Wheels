#include "navibar.h"
#include <QApplication>
#include <navibuttongroup.h>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>

NaviBar::NaviBar(QWidget *parent)
    : QWidget(parent)
{
    m_btnIDMax=1023;   //[0,m_btnIDMax]
    m_btnSize.setWidth(100);    //默认尺寸
    m_iconSize=QSize(32,32);
    m_textSize=10;
    m_btnsIDPool=std::make_unique<Bitmap>(m_btnIDMax-0+1);
    m_moveSpeed=300;
    initUI();
}

NaviBar::~NaviBar()
{
}

void NaviBar::initUI()
{
    // this->setStyleSheet("QWidget{background-color:transparent;}");
    this->setStyleSheet("QWidget{border-radius:5px;}");
    this->resize(1000,100);

    //初始化按钮组
    m_btnsGroup = new NaviButtonGroup(this);
    // m_btnsGroup->setStyleSheet("QWidget{background-color:green;}");
    m_btnsGroup->setStyleSheet("QWidget{background-color:transparent;}");
    m_btnsGroup->hlay->setSpacing(50);
    m_btnsGroup->hlay->setContentsMargins(40,15,40,15);
    m_btnsGroup->btngroup->setExclusive(true);   //按钮互斥

    //初始化控件背景色
    m_label_background = new QLabel(this);
    setBackGround(QColor("black"));

    //初始化阴影
    m_curBtnShadow = new QGraphicsDropShadowEffect(this);
    m_curBtnShadow->setBlurRadius(80);
    m_curBtnShadow->setOffset(0,0);

    //初始化高亮
    m_label_highlight=new QLabel(this);
    m_label_highlight->setGeometry(0,0,0,0);
    m_label_highlight->setGraphicsEffect(m_curBtnShadow);//当前按钮设定阴影

    //高亮移动动画
    m_aniHighlightMove = new QPropertyAnimation(m_label_highlight, "pos");
    m_aniHighlightMove->setDirection(QPropertyAnimation::Forward);
    m_aniHighlightMove->setLoopCount(1);
    //高亮、阴影颜色改变动画
    m_aniHighlightColorChange = new QPropertyAnimation(this, "curBtnColor");
    m_aniHighlightColorChange->setDirection(QPropertyAnimation::Forward);
    m_aniHighlightColorChange->setLoopCount(1);

    m_paralAniGroup = new QParallelAnimationGroup(this);
    m_paralAniGroup->addAnimation(m_aniHighlightMove);
    m_paralAniGroup->addAnimation(m_aniHighlightColorChange);

    //按钮选中
    m_curBtn = nullptr;
    connect(m_btnsGroup->btngroup, &QButtonGroup::buttonClicked, this, [=](QAbstractButton* button){
        bool isHighLightVisible = false;
        //以m_curBtn是否为nullptr判断是否是第一次按下或当前按钮已被删除（visible为false，未显示）。控制高亮是show还是move
        if(m_curBtn)
        {
            m_highlightStartPos = m_curBtn->pos();
            isHighLightVisible = true;
            // m_lastBtnID = m_btnsGroup->btngroup->id(m_curBtn);//记录上次按下按钮的ID
        }

        m_curBtn = static_cast<QToolButton*>(button);   //改变当前选中按钮
        if(isHighLightVisible)
        {
            moveHighLight(m_curBtn);//移动位置
        }
        else
        {
            showHighLight(m_curBtn);//根据颜色、位置显示
        }
    });
}

//修改icon颜色
QIcon NaviBar::changeIconColor(QIcon icon, QColor newColor)
{
    QPixmap pixmap = icon.pixmap(QSize(64, 64));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    painter.setBrush(newColor);
    painter.drawRect(pixmap.rect());
    QIcon _icon = QIcon(pixmap);
    return _icon;
}

//设定控件背景色
void NaviBar::setBackGround(QColor bgcolor)
{
    QString qssbg = QString("QLabel{background-color:%1;}").arg(bgcolor.name());
    m_label_background->setStyleSheet(qssbg);
}

//根据颜色、位置、尺寸，直接显示高亮
void NaviBar::showHighLight(QToolButton* curBtn)
{
    if(curBtn)
    {
        m_label_highlight->setVisible(true);

        //获取颜色
        int curBtnID = m_btnsGroup->btngroup->id(curBtn);
        QColor curBtnColor = m_btnColors.at(curBtnID);

        //设定颜色
        this->setCurBtnColor(curBtnColor);
        m_lastBtnColor=m_curBtnColor; //高亮从不显示到显示，手动将上个按钮颜色记为当前按钮颜色

        //更新阴影尺寸、位置
        QPoint highlightStartPos = curBtn->pos();
        m_label_highlight->setGeometry(highlightStartPos.x(), highlightStartPos.y(), curBtn->width(), curBtn->height());//设定高亮m_label_highlight位置
    }
    else
    {
        m_label_highlight->setVisible(false);
    }
    m_label_highlight->repaint();//立即重绘高亮阴影
}

//以动画更新高亮的位置
void NaviBar::moveHighLight(QToolButton *curBtn)
{
    if(curBtn)
    {
        //更新阴影尺寸、位置
        m_highlightEndPos=curBtn->pos();
        m_label_highlight->setVisible(true);

        //这行代码会导致动画未结束时append有一个明显停顿
        // if(m_aniHighlightMove->state() == QAbstractAnimation::Running)
        // {
        //     m_aniHighlightMove->stop();
        // }
        m_aniHighlightMove->setDuration(m_moveSpeed);
        m_highlightStartPos = m_label_highlight->pos();
        m_aniHighlightMove->setStartValue(m_highlightStartPos);
        m_aniHighlightMove->setEndValue(m_highlightEndPos);
        // m_aniHighlightMove->start();

        //设定颜色
        int curBtnID = m_btnsGroup->btngroup->id(curBtn);
        m_aniHighlightColorChange->setDuration(m_moveSpeed);
        m_aniHighlightColorChange->setStartValue(m_lastBtnColor);
        m_aniHighlightColorChange->setEndValue(m_btnColors.at(curBtnID));
        // m_aniHighlightColorChange->start();

        m_paralAniGroup->start();
    }
    else
    {
        m_label_highlight->setVisible(false);
    }
    m_label_highlight->repaint();//立即重绘高亮阴影
}

void NaviBar::appendButton(QIcon icon, QString text, QColor iconColor, QColor textColor, QColor btnColor)
{
    assert(!icon.isNull()&&!text.isEmpty());

    //更新数据结构（放在最前判断是否有可用ID）
    int appendBtnID = createID();
    if(appendBtnID == -1)
    {
        qDebug()<<"The number of buttons exceeds the specified limit and there are no available IDs...";
        return;
    }
    m_btnsID.append(appendBtnID);
    m_btnColors.insert(std::make_pair(appendBtnID,btnColor));

    //这行代码是动画正在运行时append时的一个解决试法：动画未结束禁用添加、插入、删除。但这会丢掉操作。
    // if(m_aniHighlightMove->state() == QAbstractAnimation::Running)  return;

    QToolButton* btn = new QToolButton(this);
    QString qssBtn = QString("QToolButton{background-color:transparent;color:%1;border:none;border-radius:15px;font-size:%2px;}")
                         .arg(textColor.name())
                         .arg(m_textSize);
    btn->setStyleSheet(qssBtn);
    //按照navibar高度设定高度，减去上下边缘距离
    m_btnSize.setHeight(height() - m_btnsGroup->hlay->contentsMargins().top() - m_btnsGroup->hlay->contentsMargins().bottom());

    btn->setMinimumSize(m_btnSize);
    btn->setAutoRaise(false);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setIcon(changeIconColor(icon, iconColor));
    btn->setIconSize(m_iconSize);
    btn->setText(text);


    //添加按钮
    m_btnsGroup->btngroup->addButton(btn,appendBtnID);
    m_btnsGroup->hlay->addWidget(btn);


    //刷新显示按钮增加
    repaint();
    m_btnsGroup->hlay->activate();//立即强制布局更新
    m_btnsGroup->repaint();
    QCoreApplication::processEvents();
    // showHighLight(m_curBtn);
    //动画正在运行时append的一个解决试法
    if(m_aniHighlightMove->state() == QAbstractAnimation::Running)
    {
        moveHighLight(m_curBtn);  //添加时若动画正在运行，则更新起始坐标重新开始动画
    }
    else
    {
        showHighLight(m_curBtn);    //添加时若动画未运行，则根据当前选中按钮大小、位置改变，直接设定背景高亮
    }

}

void NaviBar::insertButton(int index, QIcon icon, QString text, QColor iconColor, QColor textColor, QColor btnColor)
{
    assert(!icon.isNull()&&!text.isEmpty());

    int insertBtnID = createID();
    if(insertBtnID == -1)
    {
        qDebug()<<"The number of buttons exceeds the specified limit and there are no available IDs...";
        return;
    }
    m_btnsID.insert(index, insertBtnID);
    m_btnColors.insert(std::make_pair(insertBtnID, btnColor));

    // if(m_aniHighlightMove->state() == QAbstractAnimation::Running)  return;

    QToolButton* btn = new QToolButton(this);
    QString qssBtn = QString("QToolButton{background-color:transparent;color:%1;border:none;border-radius:15px;font-size:%2px;}")
                         .arg(textColor.name())
                         .arg(m_textSize);

    btn->setStyleSheet(qssBtn);
    m_btnSize.setHeight(height() - m_btnsGroup->hlay->contentsMargins().top() - m_btnsGroup->hlay->contentsMargins().bottom());
    btn->setMinimumSize(m_btnSize);
    btn->setAutoRaise(false);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setIcon(changeIconColor(icon, iconColor));
    btn->setIconSize(m_iconSize);
    btn->setText(text);


    m_btnsGroup->btngroup->addButton(btn,insertBtnID);
    m_btnsGroup->hlay->insertWidget(index, btn);

    //刷新按钮增加
    repaint();
    m_btnsGroup->hlay->activate();//立即强制布局更新
    m_btnsGroup->repaint();
    QCoreApplication::processEvents();
    // showHighLight(m_curBtn);
    if(m_aniHighlightMove->state() == QAbstractAnimation::Running)
    {
        moveHighLight(m_curBtn);
    }
    else
    {
        showHighLight(m_curBtn);
    }

}

void NaviBar::removeButton(int index, int id)
{
    if(id<0) return;

    if(m_aniHighlightMove->state() == QAbstractAnimation::Running)  return;

    QAbstractButton* btnRemove = m_btnsGroup->btngroup->button(id);
    if(!btnRemove)  return;

    m_btnsGroup->hlay->removeWidget(btnRemove);
    m_btnsGroup->btngroup->removeButton(btnRemove);
    //销毁按钮
    if(btnRemove==m_curBtn)
    {
        m_curBtn=nullptr;//如果删除的按钮和当前选中是同一个
    }
    delete btnRemove;
    //更新数据结构
    m_btnsID.removeAt(index);
    m_btnColors.erase(id);
    m_btnsIDPool->clear(id);

    //刷新按钮移除
    m_btnsGroup->hlay->activate();
    repaint();
    showHighLight(m_curBtn);
}

//获取当前按下的按钮（不返回指针防止被用户delete）
QToolButton& NaviBar::curBtn() const
{
    return *m_curBtn;
}

//根据ID获取按钮
QToolButton& NaviBar::btn(int btnID) const
{
    assert(btnID>=0);
    return *static_cast<QToolButton*>(m_btnsGroup->btngroup->button(btnID));
}

 //设定btn的尺寸
void NaviBar::setButtonMinWidth(int w)
{
    if(w!=m_btnSize.width())
    {
        m_btnSize.setWidth(w);
    }
}

void NaviBar::setIconSize(QSize iconSize)
{
    if(m_iconSize!=iconSize)
    {
        m_iconSize=iconSize;
    }
}

void NaviBar::setTextSize(int pixel)
{
    if(m_textSize!=pixel)
    {
        m_textSize=pixel;
    }
}

void NaviBar::setMoveSpeed(int milliseconds)
{
    if(m_moveSpeed!=milliseconds)
    {
        m_moveSpeed=milliseconds;
    }
}

//设定btn可添加的最大数量
void NaviBar::setBtnCountMax(int maxCount)
{
    //@TODO:当maxCount<9999时要考虑已用的id的拷贝

    if(m_btnIDMax!=maxCount)
    {
        m_btnIDMax=maxCount;
        m_btnsIDPool=std::make_unique<Bitmap>(m_btnIDMax-0+1);
    }
}

//获取设定的btn可添加的最大数量
int NaviBar::btnCountMax() const
{
    return m_btnIDMax;
}

void NaviBar::setPaddings(int left, int top, int right, int bottom)
{
    m_btnsGroup->hlay->setContentsMargins(left,top,right,bottom);
}

//根据index获取ID
int NaviBar::btnID(int btnIndex) const
{
    if(m_btnsID.size()==0)  return -1;
    return m_btnsID.at(btnIndex);
}

QColor NaviBar::curBtnColor() const
{
    return m_curBtnColor;
}

void NaviBar::setCurBtnColor(QColor color)
{
    if(m_curBtnColor==color)    return;
    m_lastBtnColor=m_curBtnColor;
    m_curBtnColor=color;
    //高亮颜色
    QString qsshl = QString("QLabel{background-color:%1;border:none;border-radius:15px;}").arg(m_curBtnColor.name());
    m_label_highlight->setStyleSheet(qsshl);
    //阴影颜色
    m_curBtnShadow->setColor(m_curBtnColor);
    update();
    emit curBtnColorChanged(color);
}

//获取可用ID
int NaviBar::createID() const
{
    for(int ii=0;ii<=m_btnIDMax;++ii)
    {
        if(!m_btnsIDPool->test(ii))
        {
            m_btnsIDPool->set(ii);//按钮分配id，置1
            return ii;
        }
    }
    return -1;
}

void NaviBar::showEvent(QShowEvent* se)
{
    Q_UNUSED(se);

    int w = this->width();
    int h = this->height();
    qDebug()<<"w="<<w;
    qDebug()<<"h="<<h;
    //背景fill整个navibar
    m_label_background->setGeometry(0,0,w,h);
    m_label_background->lower();//背景z=0

    //按钮组fill整个navibar
    m_btnsGroup->setGeometry(0,0,w,h);//被m_navibtns->adjustSize()调整尺寸效果覆盖
    m_btnsGroup->raise();//按钮组z=2

    //高亮z=1
    m_label_highlight->stackUnder(m_btnsGroup);
}

void NaviBar::paintEvent(QPaintEvent *ev)
{
    // Q_UNUSED(ev);
    QWidget::paintEvent(ev);

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    // m_btnsGroup->update();//刷新按钮组显示
    m_btnsGroup->adjustSize();//按钮组尺寸适应子内容大小
}
