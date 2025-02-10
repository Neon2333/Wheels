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
	m_colorList = colorList;
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
