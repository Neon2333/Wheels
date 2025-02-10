#include "DelayButton.h"

DelayButton::DelayButton(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);

	animation = new QPropertyAnimation(this, "progress");
	animation->setDuration(2000);   
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);

    //connect(this, &DelayButton::pressed, this, [this]() {
    //    animation->stop();
    //    animation->setStartValue(progress);
    //    animation->setEndValue(1.0);
    //    animation->setDirection(QPropertyAnimation::Forward);
    //    animation->start();
    //   /* if (!checked)
    //    {
    //    }*/
    //    });

    //connect(this, &DelayButton::released, this, [this]() {
    //    animation->stop();
    //    animation->setStartValue(0.0);
    //    animation->setEndValue(progress);
    //    //progress = 0.0;
    //    animation->setDirection(QPropertyAnimation::Backward);
    //    animation->start();
    //    /*if (!checked)
    //    {
    //       
    //    }*/
    //    });

    connect(this, &DelayButton::pressed, this, [this]() {
        if (progress == 0 && !checked)
        {
            animation->setDirection(QPropertyAnimation::Forward);
            animation->start();
        }
        });

    connect(this, &DelayButton::released, this, [this]() {
        if (progress!=0 && !checked)
        {
            animation->pause();
            animation->setDirection(QPropertyAnimation::Backward);
            animation->resume();
        }
        });
}

DelayButton::~DelayButton()
{
	delete animation;
}

void DelayButton::setUnchecked()
{
    if (checked)    checked = false;

    setProgress(0.0);
}

void DelayButton::setProgress(qreal p)
{
	if (progress != p) 
	{
		progress = p;
        qDebug() << "progress=" << progress;
        if (progress == 1.0)
        {
            checked = true;
        }
        else
        {
            checked = false;
        }
		update();
	}
}

qreal DelayButton::getProgress()
{
    return progress;
}

void DelayButton::paintEvent(QPaintEvent * event)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制圆形按钮背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("royalblue")));
    painter.drawEllipse(arcWidth, arcWidth, width()-2*arcWidth, height()-2*arcWidth);

    // 绘制圆环
    qreal radius = width() / 2.0;
    qreal startAngle = 90;
    qreal spanAngle = 360 * progress;
    QPen p(QColor("pink"));
    p.setWidth(arcWidth);
    painter.setPen(p);
    painter.drawArc(QRectF(0.5 * arcWidth, 0.5 * arcWidth, width() - arcWidth, height() - arcWidth), startAngle*16, spanAngle *16);

    // 绘制图标
    if (!icon_normal.isNull())
    {
        QSize iconSize(width() * 0.9, height() * 0.9);
        QPixmap icon = icon_normal.pixmap(iconSize);
        painter.drawPixmap(QRect(width() / 2 - iconSize.width() / 2, height() / 2 - iconSize.height() / 2, width() * 0.9, height() * 0.9), icon);
    }
}
