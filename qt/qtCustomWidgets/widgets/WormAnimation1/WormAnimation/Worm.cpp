#include "Worm.h"

Worm::Worm(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    init();

    m_animation = new QPropertyAnimation(this, "firstBonePos");
    m_animation->setDuration(100);
    m_animation->setLoopCount(1);
    moveStepDirection(Worm::Direction::Right);

    QObject::connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        moveStepDirection(m_direction);
        });
}

Worm::~Worm()
{
    for (auto bonePoint : m_bonePoints)
    {
        delete bonePoint;
    }
}

void Worm::init()
{
    for (int i = 0; i < boneCount; i++)
    {
        m_bonePoints.append(new QPointF(200.0 - 20.0 * i, 100.0));
        m_constraintRadius.append(20);
    }

    for (int i = 0; i < m_bonePoints.size(); i++)
    {
        double angleBonePoint = calBonePointsAngle(i);
        m_bonePointsAngle.append(angleBonePoint);
    }

}

float Worm::InvSqrt(float x)
{
    //卡马克平方根倒数算法
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf * x * x);
    return x;
}

void Worm::calculate(QPointF* anchor, QPointF* target, float r)
{
    float deltax = target->x() - anchor->x();
    float deltay = target->y() - anchor->y();
    float k = r * InvSqrt(deltax * deltax + deltay * deltay);

    float x_ = k * target->x() + (1.0 - k) * anchor->x();
    float y_ = k * target->y() + (1.0 - k) * anchor->y();
    target->setX(x_);
    target->setY(y_);
}

double Worm::calBonePointsAngle(int pointIndex)
{
    double angleBonePoint = 0.0;
    //计算骨骼点角度
    if (pointIndex < 2)
    {
        double deltay = m_bonePoints.at(1)->y() - m_bonePoints.at(0)->y();
        double deltax = m_bonePoints.at(1)->x() - m_bonePoints.at(0)->x();
        angleBonePoint = atan2(deltay, deltax);
    }
    else
    {
        double deltay = m_bonePoints.at(pointIndex)->y() - m_bonePoints.at(pointIndex - 1)->y();  //向量起点是i-1，终点是i
        double deltax = m_bonePoints.at(pointIndex)->x() - m_bonePoints.at(pointIndex - 1)->x();
        angleBonePoint = atan2(deltay, deltax);
    }

    return angleBonePoint;
}

Worm::Direction Worm::direction()
{
    return m_direction;
}

void Worm::moveStepDirection(Direction dirc)
{
    if (m_direction != dirc)
    {
        m_direction = dirc;
        emit dirEctionChanged(dirc);
    }

    switch (m_direction)
    {
    case Worm::Direction::Up:
        if (m_animation->state() == QAbstractAnimation::Running) m_animation->stop();
        m_animation->setStartValue(*m_bonePoints.at(0));
        m_animation->setEndValue(QPointF(m_bonePoints.at(0)->x(), m_bonePoints.at(0)->y() - step));
        m_animation->start();
        break;
    case Worm::Direction::Down:
        if (m_animation->state() == QAbstractAnimation::Running) m_animation->stop();
        m_animation->setStartValue(*m_bonePoints.at(0));
        m_animation->setEndValue(QPointF(m_bonePoints.at(0)->x(), m_bonePoints.at(0)->y() + step));
        m_animation->start();
        break;
    case Worm::Direction::Left:
        if (m_animation->state() == QAbstractAnimation::Running) m_animation->stop();
        m_animation->setStartValue(*m_bonePoints.at(0));
        m_animation->setEndValue(QPointF(m_bonePoints.at(0)->x() - step, m_bonePoints.at(0)->y()));
        m_animation->start();
        break;
    case Worm::Direction::Right:
        if (m_animation->state() == QAbstractAnimation::Running) m_animation->stop();
        m_animation->setStartValue(*m_bonePoints.at(0));
        m_animation->setEndValue(QPointF(m_bonePoints.at(0)->x() + step, m_bonePoints.at(0)->y()));
        m_animation->start();
        break;
    default:
        break;
    }
}

QPointF Worm::firstBonePos()
{
    return *m_bonePoints.at(0);
}

void Worm::setFirstBonePos(QPointF firstPos)
{
    if (*m_bonePoints.at(0) != firstPos)
    {
        m_bonePoints[0]->setX(firstPos.x());
        m_bonePoints[0]->setY(firstPos.y());

        //刷新骨骼点坐标前，清空所有坐标记录
        m_bonePointsAngle.clear();
        m_bodyPointsL.clear();
        m_bodyPointsR.clear();
        
        //刷新所有骨骼点坐标
        for (int i = 0; i < m_bonePoints.size() - 1; i++)
        {
            //半径约束：刷新所有骨骼点坐标
            calculate(m_bonePoints[i], m_bonePoints[i + 1], m_constraintRadius[i]);
        }

        for (int i = 0; i < m_bonePoints.size(); i++)
        {
            //计算骨骼点角度
            double currentAngle = calBonePointsAngle(i);
            double prevAngle = calBonePointsAngle(i-1);

            //角度约束：矫正骨骼点坐标和角度
            if (i >= 2)
            {
                double deltaAngle = 0.0;
                deltaAngle = currentAngle - m_bonePointsAngle.at(i - 1);
                //deltaAngle = fmod(currentAngle - prevAngle + M_PI, 2 * M_PI) - M_PI;
                deltaAngle = currentAngle - prevAngle;

                if (fabs(deltaAngle) > angleConstraint)
                {
                    if (deltaAngle > 0)
                    {
                        currentAngle = prevAngle + angleConstraint;
                    }
                    else
                    {
                        currentAngle = prevAngle - angleConstraint;
                    }

                    double newX = m_bonePoints.at(i - 1)->x() + m_constraintRadius.at(i - 1) * cos(currentAngle);
                    double newY = m_bonePoints.at(i - 1)->y() + m_constraintRadius.at(i - 1) * sin(currentAngle);
                    m_bonePoints[i]->setX(newX);
                    m_bonePoints[i]->setY(newY);
                }
            }
            m_bonePointsAngle.append(currentAngle);


            //记录轮廓点
            if (i == 0)
            {
                //头部前端3个点
                double angleHead = m_bonePointsAngle.at(i) + M_PI;
                double angle1 = m_bonePointsAngle.at(i) + 3 * M_PI_4;
                double angle2 = m_bonePointsAngle.at(i) - 3 * M_PI_4;
                QPointF bodyPointHead(m_bonePoints.at(i)->x() + m_bodyRadius.at(i) * cos(angleHead), m_bonePoints.at(i)->y() + m_bodyRadius.at(i) * sin(angleHead));
                QPointF bodyPoint1(m_bonePoints.at(i)->x() + m_bodyRadius.at(i) * cos(angle1), m_bonePoints.at(i)->y() + m_bodyRadius.at(i) * sin(angle1));
                QPointF bodyPoint2(m_bonePoints.at(i)->x() + m_bodyRadius.at(i) * cos(angle2), m_bonePoints.at(i)->y() + m_bodyRadius.at(i) * sin(angle2));
                m_bodyPointsL.append(bodyPointHead);
                m_bodyPointsL.append(bodyPoint1);
                m_bodyPointsR.append(bodyPoint2);
            }
            
            double angleLeft = m_bonePointsAngle.at(i) + M_PI_2;
            double angleRight = m_bonePointsAngle.at(i) - M_PI_2;
            QPointF bodyPointLeft(m_bonePoints.at(i)->x() + m_bodyRadius.at(i) * cos(angleLeft), m_bonePoints.at(i)->y() + m_bodyRadius.at(i) * sin(angleLeft));
            QPointF bodyPointRight(m_bonePoints.at(i)->x() + m_bodyRadius.at(i) * cos(angleRight), m_bonePoints.at(i)->y() + m_bodyRadius.at(i) * sin(angleRight));
            m_bodyPointsL.append(bodyPointLeft);
            m_bodyPointsR.append(bodyPointRight);
           
            if (i == m_bonePoints.size() - 1)
            {
                double angleTail = m_bonePointsAngle.at(i);
                QPointF bodyPointTail(m_bonePoints.at(i)->x() + m_bodyRadius.at(i) * cos(angleTail), m_bonePoints.at(i)->y() + m_bodyRadius.at(i) * sin(angleTail));
                m_bodyPointsL.append(bodyPointTail);
            }
            /* painter.drawEllipse(bodyPointLeft, 2, 2);
             painter.drawEllipse(bodyPointRight, 2, 2);*/
        }

        //重绘
        update();

        emit firstBonePosChanged(firstPos);
    }
}

void Worm::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    

    //绘制骨架
    for (int i=0;i< m_bonePoints.size();i++)
    {
        painter.setBrush(QColor("lightblue"));
        QPen pen(QColor("lightblue")); 
        pen.setWidth(5);
        painter.setPen(pen);
        //painter.drawEllipse(*m_bonePoints.at(i), m_bodyRadius.at(i), m_bodyRadius.at(i));
        painter.drawEllipse(*m_bonePoints.at(i), 2, 2);
    }
    for (int i = 0; i < m_bonePoints.size() - 1; i++)
    {
        painter.drawLine(*m_bonePoints.at(i), *m_bonePoints.at(i + 1));
    }


    //绘制轮廓
    /*QPen pen(QColor("red"));
    painter.setPen(pen);*/
    std::reverse(m_bodyPointsR.begin(), m_bodyPointsR.end());
    QList<QPointF> bodyPoints = m_bodyPointsL + m_bodyPointsR;
    
    //painter.drawPolygon(bodyPoints);  //直线

    //QList<QPointF> bodyPoints;
    //createNBezierCurve(bodyPointsTmp, bodyPoints, 0.01);  //N次贝塞尔曲线

    //QPainterPath path;
    //for (int i = 0;i < bodyPoints.size()-2;i++)
    //{
    //    if(i == 0)    path.moveTo(bodyPoints.at(0)); // 设置起始点
    //    path.cubicTo(bodyPoints.at(i), bodyPoints.at(i+1), bodyPoints.at(i+2)); // 3次贝塞尔曲线
    //    if(i == bodyPoints.size() - 3)  path.cubicTo(bodyPoints.at(i+1), bodyPoints.at(i + 2), bodyPoints.at(0));
    //}
    //painter.drawPath(path);


    //绘制眼睛
    painter.setPen(QColor("green"));
    painter.setBrush(QColor("green"));
    double eye0Angle = m_bonePointsAngle.at(0) + M_PI_2;
    double eye1Angle = m_bonePointsAngle.at(0) - M_PI_2;
    double eyeRadius = m_bodyRadius.at(0) - 5; //眼睛所在圆半径小一点
    QPointF eye0(m_bonePoints.at(0)->x() + eyeRadius * cos(eye0Angle), m_bonePoints.at(0)->y() + eyeRadius * sin(eye0Angle));
    QPointF eye1(m_bonePoints.at(0)->x() + eyeRadius * cos(eye1Angle), m_bonePoints.at(0)->y() + eyeRadius * sin(eye1Angle));
    painter.drawEllipse(eye0, 2, 2);
    painter.drawEllipse(eye1, 2, 2);

}

void Worm::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
    case Qt::Key_W:
        //setFirstBonePos(QPointF(m_bonePoints[0]->x(), m_bonePoints[0]->y() - 10.0));
        moveStepDirection(Direction::Up);
        break;
    case Qt::Key_S:
        moveStepDirection(Direction::Down);
        break;
    case Qt::Key_A:
        moveStepDirection(Direction::Left);
        break;
    case Qt::Key_D:
        moveStepDirection(Direction::Right);
        break;
    case Qt::Key_Up:
        if (m_animation->state() == QAbstractAnimation::Running) m_animation->stop();
        break;
    case Qt::Key_Down:
        if (m_animation->state() == QAbstractAnimation::Stopped) m_animation->start();
        break;
    default:
        break;
    }

    //update();
}
