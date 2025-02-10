#include "SideBar.h"

SideBar::SideBar(QWidget* parent, int fixedWidth, int leftMargin, int rightMargin, int verticalSpacing, int horizontalSpacing) : QWidget(parent)
{
	ui.setupUi(this);
	m_fixedWidth = fixedWidth;

	//�Ҳ�
	glay_innerLayRight = new QGridLayout;
	glay_innerLayRight->setContentsMargins(leftMargin, 0, rightMargin, 0);
	glay_innerLayRight->setVerticalSpacing(verticalSpacing);
	glay_innerLayRight->setHorizontalSpacing(horizontalSpacing);

	hlay_innerLay = new QHBoxLayout;
	hlay_innerLay->setContentsMargins(0, 0, 0, 0);
	hlay_innerLay->setSpacing(0);
	
	placeholder_fixedBar = new QSpacerItem(m_fixedWidth, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);;
	hlay_innerLay->addSpacerItem(placeholder_fixedBar);
	hlay_innerLay->addLayout(glay_innerLayRight);
	this->setLayout(hlay_innerLay);

	//����
	animation = new QPropertyAnimation(this, "size");
	this->animation->setStartValue(this->shrinkSize);
	this->animation->setEndValue(this->expandSize);
	animation->setDuration(150);
	connect(this->animation, &QPropertyAnimation::finished, this, [this] {
		if (this->shrinkSize.height() != this->window()->height())
		{
			//window�߶ȸı�ʱ���޸Ķ����趨�ĸ߶�
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

	setShrinkWidth(m_fixedWidth);
	this->resize(shrinkSize);
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
		m_isInit = false;
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
		m_isInit = false;
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

void SideBar::addWidget(QWidget* widget, QSize widgetSize, int row, int column, Qt::Alignment alignment)
{
	if (!widget)	return;
	
	if (widgetSize == QSize(0, 0))
	{
		qDebug() << "item size=0";
		return;
	}
	widget->resize(widgetSize);
	this->glay_innerLayRight->addWidget(widget, row, column, alignment);
}

void SideBar::addFixedSizeWidget(QWidget* widget, QSize widgetSize, int row, int column, Qt::Alignment alignment)
{
	if (!widget)	return;

	if (widgetSize == QSize(0, 0))
	{
		qDebug() << "item size=0";
		return;
	}
	widget->setFixedSize(widgetSize);
	this->glay_innerLayRight->addWidget(widget, row, column, alignment);
}

void SideBar::addWidget(QWidget* widget, QSize widgetSize, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment)
{
	if (!widget)	return;

	if (widgetSize == QSize(0, 0))
	{
		qDebug() << "item size=0";
		return;
	}
	widget->resize(widgetSize);
	this->glay_innerLayRight->addWidget(widget, fromRow, fromColumn, rowSpan, columnSpan, alignment);
}

void SideBar::addFixedSizeWidget(QWidget* widget, QSize widgetSize, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment)
{
	if (!widget)	return;

	if (widgetSize == QSize(0, 0))
	{
		qDebug() << "item size=0";
		return;
	}
	widget->setFixedSize(widgetSize);
	this->glay_innerLayRight->addWidget(widget, fromRow, fromColumn, rowSpan, columnSpan, alignment);
}

void SideBar::setSideBarContentsHeightMargins(int top, int bottom)
{
	QMargins margins = this->glay_innerLayRight->contentsMargins();
	this->glay_innerLayRight->setContentsMargins(margins.left(), top, margins.right(), bottom);
	qDebug() << "2 this width=" << this->width();
}

void SideBar::resizeEvent(QResizeEvent* event)
{
	if (!this->isAnimationRunning)
	{
		//������������չ�ߴ�
		this->shrinkSize.setHeight(this->window()->height());
		this->expandSize.setHeight(this->window()->height());
		this->animation->setStartValue(this->shrinkSize);
		this->animation->setEndValue(this->expandSize);
		
	}

	//���������ȡwidth()��m_shrinkWidth��ֵ��ΪshrinkWidth���趨widget��fixSizeʱ�������resize֮ǰwidth��С��ʵ�ʴ�30��Ϊʲô��30ԭ��δ֪��
	if (m_isInit)
	{
		//setShrinkWidth(m_fixedWidth);
		setShrinkWidth(this->width());
		this->resize(shrinkSize);
		//emit widthChanged(this->m_shrinkWidth);
	}
	emit widthChanged(this->width());
	QWidget::resizeEvent(event);
}

void SideBar::showEvent(QShowEvent* event)
{
	emit hasShown();
	QWidget::showEvent(event);
}

void SideBar::paintEvent(QPaintEvent* event)
{
	//��qss��QWidget���Զ���ؼ�����Ч
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

int SideBar::getShrinkWidth() const
{
	return m_shrinkWidth;
}

int SideBar::getFixedWidth() const
{
	return m_fixedWidth;
}

void SideBar::setIsInit(bool isInit)
{
	m_isInit = isInit;
}

bool SideBar::getIsInit()
{
	return m_isInit;
}

void SideBar::setShrinkWidth(const int shrinkWidth)
{
	if (m_shrinkWidth != shrinkWidth)
	{
		m_shrinkWidth = shrinkWidth;
		shrinkSize.setWidth(m_shrinkWidth);
		shrinkSize.setHeight(this->window()->height());
		expandSize.setWidth(shrinkSize.width() + increasedWidth);
		expandSize.setHeight(shrinkSize.height());
		this->animation->setStartValue(this->shrinkSize);
		this->animation->setEndValue(this->expandSize);

		emit shrinkWidthChanged(shrinkWidth);
	}
}