#ifndef LOADINGANIMWIDGET_H
#define LOADINGANIMWIDGET_H
#include <QPropertyAnimation>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>


class LoadingWidget :public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle WRITE setAngle)

public:
    enum class LoadingWidgetStyle
    {
        TubeCircle = 0,       //������
        TubeGradiantCircle,   //����ɫ������
        SpotCircle,           //�����㻷��Сβ��
        SpotsCircle,          //����㻷
        StickCircle,          //���С����ɻ�
        TextCircle,           //����Χ�ƻ���ת
        SlinkyCircle,         //����Ȧ
        ZoomingBalls,         //���ηŴ�С��
        ThreeMovingZoomingBalls,  //С���ȴ��С
        RippleWave,            //������
        TextInBouncingBox,       //�����ı���
        ExpandingScroll,         //Բ��ת����Ȧ�󣬾���չʾ
        ThreeRevolvingBalls,     //��ɫС����ת
        InfinityLoop,            //�������
        FourRotatingFireBall,    //�ĸ���ת�Ļ���
        Pacman,                 //�Զ���
        PendulumClock,          //�Ӱ�
        JellyInBox,            //����������
        LoopedRingWithText,     //������ת�����м�����
        Radar,                   //�״�
        VolumeBar,               //������
        VolumeBarTiny,            //�������򻯰�
        FillGlassBead,           //����עˮ
        Hourglass,               //©��
        RhombusShift,             //�ƶ���4������
        TiltingBricks,             //������3������
        TextPoint                   //Loading...���ѭ������
    };

    enum class AnimationSpeed
    {
        VeryFast = 1000,    //�������ڣ�ms)
        Fast = 2000,
        Medium = 3000,
        Slow = 4000
    };

    LoadingWidget(QWidget* parent = nullptr);
    virtual ~LoadingWidget();

    qreal angle()const;
    void setAngle(qreal an);

    LoadingWidget::AnimationSpeed speed() const;
    void setSpeed(AnimationSpeed speed);

    QColor color() const;
    virtual void setColor(QColor color);
    virtual void setColor(const QList<QColor>& colorList);

    virtual void setTextColor(QColor color);

    virtual void setText(const QString& text);

    virtual void setFont(QFont font);

public slots:
    virtual void exec();
    virtual void start();
    virtual void stop();
protected:
    QPropertyAnimation m_animation;   
    qreal m_angle = 0;
    LoadingWidget::AnimationSpeed m_speed; 
    QColor m_color = QColor("black");
    QList<QColor> m_colorList;
    QString m_text = "";
    QColor m_textColor = QColor("black");
    QFont m_font;
};

#endif