#include "qanimationstackedwidget.h"

QAnimationStackedWidget::QAnimationStackedWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    m_aniDuration = 500;
    m_isNext=true;
    m_lastIndex=0;
    m_leftWidth=0;
    m_topHeight=0;
    m_aniMode=aniMode::Switch;
    m_switchDirection=switchDirection::Horizontal;

    m_aniSwitchPage = new QPropertyAnimation(this, "leftWidth");
    m_aniSwitchPage->setDuration(m_aniDuration);

    connect(m_aniSwitchPage, &QPropertyAnimation::finished, this, [this](){
        this->widget(currentIndex())->show();   //动画结束，隐藏的页面显示
    });
}

QAnimationStackedWidget::~QAnimationStackedWidget()
{
}

void QAnimationStackedWidget::setDuration(int ms)
{
    if(m_aniDuration==ms)  return;
    m_aniDuration=ms;
    m_aniSwitchPage->setDuration(m_aniDuration);
}

void QAnimationStackedWidget::setAniMode(aniMode mode)
{
    if(m_aniMode==mode) return;
    m_aniMode=mode;
}

void QAnimationStackedWidget::setSwitchDirection(switchDirection dir)
{
    if(m_switchDirection==dir)  return;
    m_switchDirection=dir;
    if(m_switchDirection==switchDirection::Vertical)
    {
        m_aniSwitchPage->setPropertyName("topHeight");
    }
    else if(m_switchDirection==switchDirection::Horizontal)
    {
        m_aniSwitchPage->setPropertyName("leftWidth");
    }

}

QAnimationStackedWidget::aniMode QAnimationStackedWidget::getAniMode()
{
    return m_aniMode;
}

QAnimationStackedWidget::switchDirection QAnimationStackedWidget::getSwitchDirection()
{
    return m_switchDirection;
}

void QAnimationStackedWidget::setLeftWidth(int w)
{
    if(m_leftWidth==w)  return;
    m_leftWidth=w;
    update();
}

int QAnimationStackedWidget::leftWidth()
{
    return m_leftWidth;
}

void QAnimationStackedWidget::setTopHeight(int h)
{
    if(m_topHeight==h)  return;
    m_topHeight=h;
    update();
}

int QAnimationStackedWidget::topHeight()
{
    return m_topHeight;
}

/*
切页bug：初始化后，若页面初次切到，是没有被渲染的，setCurrentIndex切到时显示不全。这个渲染需要一定时间。
这里的思路是先播放动画，动画结束再将页切到新页。
尝试0：在showEvent事先遍历把所有页面都setCurrentIndex。（失败）
尝试1：先切页，让它渲染，但隐藏新页（此时currentIndex为新页的索引）。播放动画，动画结束，取消隐藏。（成功）
*/
void QAnimationStackedWidget::switchPage(bool isNext)
{
    //如果正在动画，那么return
    if(m_aniSwitchPage->state()==QPropertyAnimation::State::Running)
    {
        return;
    }

    m_isNext=isNext;

    int curIndex = currentIndex();
    int widthStackedWidget = this->width();
    int heightStackedWidget = this->height();

    //隐藏当前的widget
    widget(curIndex)->hide();

    //计算即将切到的页面的索引
    int switchIndex=0;
    if(m_isNext)
    {
        //切下一页
        switchIndex= ((curIndex+1)==this->count())? 0 : curIndex+1;

        if(m_switchDirection==switchDirection::Horizontal)
        {
            //右侧向左移动
            m_aniSwitchPage->setStartValue(widthStackedWidget);
            m_aniSwitchPage->setEndValue(0);
        }
        else if(m_switchDirection==switchDirection::Vertical)
        {
            //下侧向上移动
            m_aniSwitchPage->setStartValue(heightStackedWidget);
            m_aniSwitchPage->setEndValue(0);
        }
    }
    else
    {
        //切上一页
        switchIndex= ((curIndex-1)==-1)? this->count()-1 : curIndex-1;

        if(m_switchDirection==switchDirection::Horizontal)
        {
            //左侧向右移动
            m_aniSwitchPage->setStartValue(0);
            m_aniSwitchPage->setEndValue(widthStackedWidget);
        }
        else if(m_switchDirection==switchDirection::Vertical)
        {
            //上侧向下移动
            m_aniSwitchPage->setStartValue(0);
            m_aniSwitchPage->setEndValue(heightStackedWidget);
        }
    }

    //切到新页面，但隐藏
    m_lastIndex = currentIndex();//记录旧页index
    this->setCurrentIndex(switchIndex);
    this->widget(currentIndex())->hide();

    //启动动画
    m_aniSwitchPage->start();
}

void QAnimationStackedWidget::paintLeft(QPainter& painter, int pageIndex)
{
    //获得希望在左侧绘制的widget
    QWidget* widgetLeft = widget(pageIndex);
    QRect r = widgetLeft->geometry();
    //定义widget同尺寸的图片
    QPixmap pixmapLeft(widgetLeft->size());
    //将Widget的内容渲染到QPixmap对象中，即将Widget变成一张图片
    widgetLeft->render(&pixmapLeft);

    //绘制左侧的Widget
    double lw = leftWidth();
    QRectF rTarget(0.0, 0.0, lw, r.height());   //绘制位置（同aniMode无关）
    if(m_aniMode==aniMode::Switch)
    {
        QRectF rSource(r.width() - lw, 0.0, lw, r.height());//采样矩形为pixmap的右边lw部分
        painter.drawPixmap(rTarget, pixmapLeft, rSource);//pixmap的source绘制到target矩形处
    }
    else if(m_aniMode==aniMode::Cover)
    {
        QRectF rSource(0.0, 0.0, lw, r.height());//采样矩形为pixmap的左边lw部分
        painter.drawPixmap(rTarget, pixmapLeft, rSource);
    }

}

void QAnimationStackedWidget::paintRight(QPainter& painter, int pageIndex)
{
    QWidget* widgetRight = widget(pageIndex);
    QRect r = geometry();
    QPixmap pixmapRight(widgetRight->size());
    widgetRight->render(&pixmapRight);

    double lw = leftWidth();
    QRectF rTarget(lw, 0.0, r.width() - lw, r.height());
    if(m_aniMode==aniMode::Switch)
    {
        QRectF rSource(0.0, 0.0, r.width() - lw, r.height());//采样矩形为pixmap的左边width-lw部分
        painter.drawPixmap(rTarget, pixmapRight, rSource);
    }
    else if(m_aniMode==aniMode::Cover)
    {
        QRectF rSource(lw, 0.0, r.width() - lw, r.height());//采样矩形为pixmap的右侧width-lw部分
        painter.drawPixmap(rTarget, pixmapRight, rSource);
    }
}

void QAnimationStackedWidget::paintTop(QPainter &painter, int pageIndex)
{
    QWidget* widgetTop = widget(pageIndex);
    QRect r = geometry();
    QPixmap pixmapTop(widgetTop->size());
    widgetTop->render(&pixmapTop);

    double th = topHeight();
    QRectF rTarget(0.0, 0.0, r.width(), th);
    if(m_aniMode==aniMode::Switch)
    {
        QRectF rSource(0.0, r.height()-th, r.width(), th);
        painter.drawPixmap(rTarget, pixmapTop, rSource);
    }
    else if(m_aniMode==aniMode::Cover)
    {
        QRectF rSource(0.0, 0.0, r.width(), th);
        painter.drawPixmap(rTarget, pixmapTop, rSource);
    }
}

void QAnimationStackedWidget::paintBottom(QPainter &painter, int pageIndex)
{
    QWidget* widgetTop = widget(pageIndex);
    QRect r = geometry();
    QPixmap pixmapTop(widgetTop->size());
    widgetTop->render(&pixmapTop);

    double th = topHeight();
    QRectF rTarget(0.0, th, r.width(), r.height()-th);
    if(m_aniMode==aniMode::Switch)
    {
        QRectF rSource(0.0, 0.0, r.width(), r.height()-th);
        painter.drawPixmap(rTarget, pixmapTop, rSource);
    }
    else if(m_aniMode==aniMode::Cover)
    {
        QRectF rSource(0.0, th, r.width(), r.height()-th);
        painter.drawPixmap(rTarget, pixmapTop, rSource);
    }
}

void QAnimationStackedWidget::paintEvent(QPaintEvent * ev)
{
    QStackedWidget::paintEvent(ev);

    if(m_aniSwitchPage->state()==QPropertyAnimation::State::Running)
    {
        QPainter painter(this);
        if(m_switchDirection==switchDirection::Horizontal)
        {
            if(m_isNext)
            {
                //旧页在左侧
                paintLeft(painter, m_lastIndex);
                //新页在右侧
                paintRight(painter, currentIndex());
            }
            else
            {
                //旧页在右侧
                paintRight(painter,m_lastIndex);
                //新页在左侧
                paintLeft(painter,currentIndex());
            }
        }
        else if(m_switchDirection==switchDirection::Vertical)
        {
            if(m_isNext)
            {
                //旧页在上侧
                paintTop(painter, m_lastIndex);
                //新页在下侧
                paintBottom(painter, currentIndex());
            }
            else
            {
                //旧页在下侧
                paintBottom(painter, m_lastIndex);
                //新页在上侧
                paintTop(painter, currentIndex());
            }
        }

    }
}

