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
#include "TextPoint.h"

class LoadingWidgetFactory  : public QObject
{
	Q_OBJECT

public:
	LoadingWidgetFactory(QObject *parent);
	~LoadingWidgetFactory();

	static LoadingWidget* createLoadingWidget(LoadingWidget::LoadingWidgetStyle style, QWidget* parent = nullptr);
};

#endif