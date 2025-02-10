#include "SideBar.h"

SideBar::SideBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

SideBar::SideBar(QWidget* parent, bool adaptive, int leftMargin, int rightMargin, int verticalSpacing, int horizontalSpacing, int fixedWidth)
{
	ui.setupUi(this);

	m_adaptive = adaptive;
	if (adaptive)
	{
		m_fixedWidth = fixedWidth;
	}

	glay_innerLay = new QVBoxLayout;
	glay_innerLay->setContentsMargins(leftMargin, 0, rightMargin, 0);
	//glay_innerLay->setSpacing(verticalSpacing);
	this->setLayout(glay_innerLay);

	shrinkSize.setWidth(m_fixedWidth);
	shrinkSize.setHeight(this->window()->height());
	expandSize.setWidth(shrinkSize.width() + increasedWidth);
	expandSize.setHeight(shrinkSize.height());


	qDebug() << "0 width=" << this->width() << ",height=" << this->height();
	qDebug() << "0 m_fixedWidth=" << m_fixedWidth;
	qDebug() << "0 shrinkSize=" << shrinkSize.width() << "," << shrinkSize.height();
	qDebug() << "0 expandSize=" << expandSize.width() << "," << expandSize.height();


	animation = new QPropertyAnimation(this, "size");
	this->animation->setStartValue(this->shrinkSize);
	this->animation->setEndValue(this->expandSize);
	animation->setDuration(150);
	connect(this->animation, &QPropertyAnimation::finished, this, [this] {
		if (this->shrinkSize.height() != this->window()->height())
		{
			//window高度改变时，修改动画设定的高度
			this->shrinkSize.setHeight(this->window()->height());
			this->expandSize.setHeight(this->window()->height());
			this->animation->setStartValue(this->shrinkSize);
			this->animation->setEndValue(this->expandSize);
		}
		this->isExpanded = !this->isExpanded;
		this->isAnimationRunning = false;
		if (this->isExpanded)
			emit this->expandFinished();
		else
			emit this->shrinkFinished();
		emit this->finished();
		});
}

SideBar::~SideBar()
{}

void SideBar::expand()
{
	if (!this->isExpanded && !this->isAnimationRunning)
	{
		animation->setDirection(QAbstractAnimation::Forward);
		animation->start();
		isAnimationRunning = true;
		emit this->expandStart();
	}
}

void SideBar::shrink()
{
	if (this->isExpanded && !this->isAnimationRunning)
	{
		this->animation->setDirection(QAbstractAnimation::Backward);
		this->animation->start();
		this->isAnimationRunning = true;
		emit this->shrinkStart();
	}
}

void SideBar::setIncreasedWidth(quint32 increasedWidth)
{
	this->increasedWidth = increasedWidth;
	this->expandSize.setWidth(this->shrinkSize.width() + this->increasedWidth);
}

int SideBar::getIncreasedWidth()
{
	return this->increasedWidth;
}

int SideBar::getFixedWidth()
{
	return m_fixedWidth;
}

void SideBar::addWidget(QWidget* item, QSize itemSize)
{
	if (!item)	return;
	
	this->glay_innerLay->addWidget(item);

	if (!m_adaptive)
	{
		if (itemSize == QSize(0, 0))
		{
			qDebug() << "item size=0";
			return;
		}
		item->setFixedSize(itemSize);
		//int rowCount = this->glay_innerLay
	}
	qDebug() << "1 this->width()=" << this->width();

	////更新收缩、扩展尺寸
	//m_fixedWidth += item->width();
	//shrinkSize.setWidth(m_fixedWidth);
	//qDebug() << "1 shrinkSize width=" << shrinkSize.width();

	//shrinkSize.setHeight(this->window()->height());
	//this->expandSize.setWidth(this->shrinkSize.width() + increasedWidth);
	//this->expandSize.setHeight(this->shrinkSize.height());

	//this->resize(shrinkSize);
}

void SideBar::setSideBarContentsHeightMargins(int top, int bottom)
{
	QMargins margins = this->glay_innerLay->contentsMargins();
	this->glay_innerLay->setContentsMargins(margins.left(), top, margins.right(), bottom);
	qDebug() << "2 this width=" << this->width();
}

void SideBar::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	if (!this->isAnimationRunning)
	{
		//更新收缩、扩展尺寸
		//this->shrinkSize.setWidth(m_fixedWidth);
		this->shrinkSize.setHeight(this->window()->height());
		//this->expandSize.setWidth(this->shrinkSize.width() + increasedWidth);
		this->expandSize.setHeight(this->window()->height());

		this->animation->setStartValue(this->shrinkSize);
		this->animation->setEndValue(this->expandSize);
	}

	if (m_isInit)
	{
		m_fixedWidth = this->width();
		shrinkSize.setWidth(m_fixedWidth);
		shrinkSize.setHeight(this->window()->height());
		expandSize.setWidth(shrinkSize.width() + increasedWidth);
		expandSize.setHeight(shrinkSize.height());
		this->resize(shrinkSize);
		m_isInit = false;
	}

	qDebug() << "4 size=" << this->size();
	emit widthChanged(this->width());
}

void SideBar::paintEvent(QPaintEvent* event)
{
	//令qss在QWidget型自定义控件中生效
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


