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

//��ڸ��Ը�ģ��
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

	int m_frameRatio = 60;		//֡��

	int m_curFrameIndex = -1;	//��ǰ֡���
	int curFrameIndex();	
	void setcurFrameIndex(int frameIndex);	

	const double m_step = 5.0;	//һ֡ǰ���Ĳ���

	const int boneCount = 40;	//����������
	
	QList<QPointF*> m_bonePoints;	//����������

	const double angleConstraint = M_PI_4/1;	//�Ƕ�Լ��
	
	QList<qreal> m_constraintRadius;	//������Լ���뾶

	//�ڹ����������Բ
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

	double calBonePointsAngle(int pointIndex);	//���ݹ�����������������Ƕ�

	static void createNBezierCurve(const QList<QPointF>& src, QList<QPointF>& dest, qreal precision)	//����N�α���������
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


	//�������������߾��ԽǶȣ�������������̣�����angle0=angle1��
	QList<double> m_bonePointsAngle;
	
	//��������������
	QList<QPointF> m_bodyPointsL;
	QList<QPointF> m_bodyPointsR;

	Direction m_direction = Direction::Right;
	Direction direction();
	void setDirection(Direction dirc);

	QPointF firstBonePos();
	void setFirstBonePos(QPointF firstPos);	//�޸ĵ�һ�����������꣬���������������

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
