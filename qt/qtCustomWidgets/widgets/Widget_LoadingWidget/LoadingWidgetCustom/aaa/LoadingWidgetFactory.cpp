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
	case LoadingWidget::LoadingWidgetStyle::TextPoint:
		return new TextPoint(parent);
		break;
	default:
		break;
	}

	return nullptr;
}
