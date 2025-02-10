#pragma once

#include <QWidget>
#include "ui_Worm.h"
#include <QPointF> 
#include <QList>
#include <QPainter>
#include <QKeyEvent>
#include <cmath>
#include <QPropertyAnimation>
#include <algorithm>
#include <QPainterPath>
#include <thread>

//多节刚性杆模型
class Worm : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(int curFrameIndex READ curFrameIndex WRITE setcurFrameIndex NOTIFY curFrameIndexChanged)

public:
	Worm(QWidget *parent = nullptr);
	~Worm();

	enum class Direction
	{
		Up=0,
		Down,
		Left,
		Right
	};

private:
	Ui::WormClass ui;

	int m_frameRatio = 60;		//帧率

	int m_curFrameIndex = -1;	//当前帧序号
	int curFrameIndex();	
	void setcurFrameIndex(int frameIndex);	

	const double m_step = 5.0;	//一帧前进的步长

	const int boneCount = 40;	//骨骼点数量
	
	QList<QPointF*> m_bonePoints;	//骨骼点坐标

	const double angleConstraint = M_PI_4/1;	//角度约束
	
	QList<qreal> m_constraintRadius;	//骨骼点约束半径

	//在骨骼点外绘制圆
	QList<qreal> m_bodyRadius
	{ 
		20, 25, 20, 15, 15, 
		15, 15, 15, 15, 15, 
		15, 15, 15, 15, 15, 
		15, 15, 15, 15, 15, 
		15, 15, 15, 15, 15, 
		15, 15, 15, 15, 15, 
		15, 15, 15, 15, 15, 
		15, 15, 15, 10, 10 
	};


	void init();

	float InvSqrt(float x);
	
	void calculate(QPointF* anchor, QPointF* target, float r);

	double calBonePointsAngle(int pointIndex);	//根据骨骼点坐标计算骨骼点角度

	static void createNBezierCurve(const QList<QPointF>& src, QList<QPointF>& dest, qreal precision)	//计算N次贝塞尔曲线
	{
		if (src.size() <= 0) return;
		QList<QPointF>().swap(dest);
		for (qreal t = 0; t < 1.0000; t += precision) {
			int size = src.size();
			QVector<qreal> coefficient(size, 0);
			coefficient[0] = 1.000;
			qreal u1 = 1.0 - t;
			for (int j = 1; j <= size - 1; j++) {
				qreal saved = 0.0;
				for (int k = 0; k < j; k++) {
					qreal temp = coefficient[k];
					coefficient[k] = saved + u1 * temp;
					saved = t * temp;
				}
				coefficient[j] = saved;
			}
			QPointF resultPoint;
			for (int i = 0; i < size; i++) {
				QPointF point = src.at(i);
				resultPoint = resultPoint + point * coefficient[i];
			}
			dest.append(resultPoint);
		}
	}


	//两两骨骼点连线绝对角度（骨骼点参数方程，假设angle0=angle1）
	QList<double> m_bonePointsAngle;
	
	//身体两侧轮廓点
	QList<QPointF> m_bodyPointsL;
	QList<QPointF> m_bodyPointsR;

	Direction m_direction = Direction::Right;
	Direction direction();
	void setDirection(Direction dirc);

	QPointF firstBonePos();
	void setFirstBonePos(QPointF firstPos);	//修改第一个骨骼点坐标，引起所有坐标更新

	void moveDirection(double distance);

	QPropertyAnimation* m_animation;

protected:
	void virtual paintEvent(QPaintEvent* e) override;
	void virtual keyPressEvent(QKeyEvent* e) override;

signals:
	void firstBonePosChanged(QPointF firstPos);
	void dirEctionChanged(Direction dirction);
	void curFrameIndexChanged(int frameIndex);
};
