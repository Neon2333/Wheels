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
        TubeCircle = 0,       //连续环
        TubeGradiantCircle,   //渐变色连续环
        SpotCircle,           //单个点环带小尾巴
        SpotsCircle,          //多个点环
        StickCircle,          //多个小棍组成环
        TextCircle,           //文字围绕环旋转
        SlinkyCircle,         //弹簧圈
        ZoomingBalls,         //依次放大小球
        ThreeMovingZoomingBalls,  //小球先大后小
        RippleWave,            //涟漪形
        TextInBouncingBox,       //跳动文本框
        ExpandingScroll,         //圆环转动两圈后，卷轴展示
        ThreeRevolvingBalls,     //三色小球旋转
        InfinityLoop,            //无穷符号
        FourRotatingFireBall,    //四个旋转的火球
        Pacman,                 //吃豆人
        PendulumClock,          //钟摆
        JellyInBox,            //伸缩果冻条
        LoopedRingWithText,     //三个旋转环加中间文字
        Radar,                   //雷达
        VolumeBar,               //音量柱
        VolumeBarTiny,            //音量柱简化版
        FillGlassBead,           //球里注水
        Hourglass,               //漏斗
        RhombusShift,             //移动的4个菱形
        TiltingBricks,             //滚动的3个菱形
        TextPoint                   //Loading...点点循环加载
    };

    enum class AnimationSpeed
    {
        VeryFast = 1000,    //动画周期（ms)
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