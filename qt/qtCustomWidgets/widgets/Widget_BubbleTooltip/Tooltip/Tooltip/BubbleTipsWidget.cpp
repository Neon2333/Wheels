#include "BubbleTipsWidget.h"
#include <QPainter>
#include <QDebug>

BubbleTipsWidget::BubbleTipsWidget(QWidget* parent, int widthFixed)
    : QWidget(parent)
{
    ui.setupUi(this);

    /*setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);*/

    m_widthFixed = widthFixed;

    ui.label_tips->setAlignment(Qt::AlignCenter);
    ui.label_tips->setWordWrap(true);
    ui.label_icon->setAlignment(Qt::AlignCenter);

    QFont f;
    f.setFamily("Microsoft YaHei UI");
    f.setPixelSize(14);
    setContentFont(f);
    setContent("tooltip");

    setLeftTopMargin();

    m_animationEnter.setPropertyName("backColor");
    m_animationEnter.setTargetObject(this);
    m_animationEnter.setEasingCurve(QEasingCurve::Linear);
    m_animationEnter.setDuration(200);
    m_animationEnter.setLoopCount(1);


    m_animationLeave.setPropertyName("backColor");
    m_animationLeave.setTargetObject(this);
    m_animationLeave.setEasingCurve(QEasingCurve::Linear);
    m_animationLeave.setDuration(200);
    m_animationLeave.setLoopCount(1);
    connect(&m_animationLeave, &QPropertyAnimation::finished, this, [this]() {
        this->close();  //�����������ڹر�
        });
}

BubbleTipsWidget::~BubbleTipsWidget()
{}

QColor BubbleTipsWidget::backColor() const
{
    return m_backColor;
}

void BubbleTipsWidget::setBackColor(QColor color)
{
    m_backColor = color;
    update();
}

void BubbleTipsWidget::setDirect(DIRECT direct, double size)
{
    m_direct = direct;
    m_posRatio = size;
    update();
}

void BubbleTipsWidget::setContentFont(QFont font)
{
    m_font = font;
    ui.label_tips->setFont(m_font);
    update();
}

void BubbleTipsWidget::setLeftTopMargin(int leftMargin, int topMargin)
{
    m_leftMargin = leftMargin;
    m_topMargin = topMargin;
    /*this->setContentsMargins(m_leftMargin + TRANSPARENT_LENGTH,
        m_topMargin + TRANSPARENT_LENGTH,
        m_leftMargin + TRANSPARENT_LENGTH,
        m_topMargin + TRANSPARENT_LENGTH);*/
    this->setContentsMargins(m_leftMargin, m_topMargin, m_leftMargin, m_topMargin);
    update();
}

void BubbleTipsWidget::setContent(const QString& content, QColor color)
{
    //�ı����ݡ���ɫ
    ui.label_tips->setText(content);
    ui.label_tips->setStyleSheet(QString("color: rgb(%1, %2, %3)")
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue()));

    // ����Ӧ�ı��߶ȵ������ڴ�С
    int hh = ui.label_tips->width();
    m_textHeight = calculateTextHeight(content, m_font, ui.label_tips->width());    //�����ı�����߶�

    int labelHeight = TOP_MARGIN + TRANSPARENT_LENGTH * 2;
    if (m_iconHeight >= m_textHeight)
    {
        labelHeight += m_iconHeight;
    }
    else
    {

        labelHeight += m_textHeight;
    }
    //this->resize(width(), labelHeight);
    this->resize(m_widthFixed, labelHeight);

    update();
}

void BubbleTipsWidget::setIcon(QIcon icon, int w, int h)
{
    //ui.label_icon->setStyleSheet(QString("background: green"));
    m_icon = icon;
    //ui.label_icon->setPixmap(m_icon.pixmap(ui.label_icon->width(), ui.label_icon->height()));
    //m_iconHeight = m_icon.actualSize(QSize(ui.label_icon->width(), ui.label_icon->height())).height();
    ui.label_icon->setPixmap(m_icon.pixmap(w, h));
    m_iconHeight = m_icon.actualSize(QSize(w, h)).height(); //��ȡiconʵ�ʸ߶ȣ�<=h��������Ϊ����resize��С����

    update();
}

void BubbleTipsWidget::setPositionByTriangle(int x, int y)
{
    m_triposX = x;
    m_triposY = y;
    //���������ζ����������ؼ����Ͻ�����
    switch (m_direct)
    {
    case DIRECT::DIRECT_TOP:
        m_posX = m_triposX - width() * m_posRatio;
        m_posY = m_triposY - (TRANSPARENT_LENGTH - TRIANGLE_HEIGHT);
        this->move(m_posX, m_posY);
        break;
    case DIRECT::DIRECT_LEFT:
        m_posX = m_triposX - (TRANSPARENT_LENGTH - TRIANGLE_HEIGHT);
        m_posY = m_triposY - height() * m_posRatio;
        this->move(m_posX, m_posY);
        break;
    case DIRECT::DIRECT_BOTTOM:
        m_posX = m_triposX - width() * m_posRatio;
        m_posY = m_triposY - (height() - (TRANSPARENT_LENGTH - TRIANGLE_HEIGHT));
        this->move(m_posX, m_posY);
        break;
    case DIRECT::DIRECT_RIGHT:
        m_posX = m_triposX - (width() - (TRANSPARENT_LENGTH - TRIANGLE_HEIGHT));
        m_posY = m_triposY - height() * m_posRatio;
        this->move(m_posX, m_posY);
        break;
    default:
        break;
    }

    update();
}

void BubbleTipsWidget::setAutoPosition(bool isAuto, QWidget* target)
{
    m_autoPosition = isAuto;
    m_target = target;

    switch (m_direct)
    {
    case DIRECT::DIRECT_LEFT:
    {
        setPositionByTriangle(m_target->pos().x() + m_target->width(), m_target->pos().y() + m_target->height() * 0.5);
        break;
    }

    case DIRECT::DIRECT_TOP:
    {
        setPositionByTriangle(m_target->pos().x() + m_target->width() * 0.5, m_target->pos().y() + m_target->height());
        break;
    }

    case DIRECT::DIRECT_RIGHT:
    {
        setPositionByTriangle(m_target->pos().x(), m_target->pos().y() + m_target->height() * 0.5);
        break;
    }

    case DIRECT::DIRECT_BOTTOM:
    {
        setPositionByTriangle(m_target->pos().x() + m_target->width() * 0.5, m_target->pos().y());
        break;
    }

    default:
        break;
    }
}

void BubbleTipsWidget::animeShow()
{
    m_animationEnter.setStartValue(QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), 100));
    m_animationEnter.setEndValue(QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), 255));
    m_animationEnter.start();
    this->show();
}

void BubbleTipsWidget::animeClose()
{
    if (m_animationEnter.state() == QAbstractAnimation::State::Running)
    {
        m_animationEnter.stop();    //enter������û������ֹͣ
    }

    m_animationLeave.setStartValue(QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), 255));
    m_animationLeave.setEndValue(QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), 100));
    m_animationLeave.start();
}

void BubbleTipsWidget::paintEvent(QPaintEvent* event)
{
    //qDebug() << "paintEvent";
    Q_UNUSED(event)

    //������ƶ�������ڵ�ǰ����BubbleTips���Ͻ�����
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backColor);

    //���Ʊ���
    painter.drawRoundedRect(TRANSPARENT_LENGTH, TRANSPARENT_LENGTH, width() - TRANSPARENT_LENGTH * 2, height() - TRANSPARENT_LENGTH * 2, 4, 4);

    //����������
    QPointF points[3];
    switch (m_direct)
    {
    case DIRECT::DIRECT_LEFT:
    {
        //�ױ���
        points[0] = QPointF(TRANSPARENT_LENGTH, height() * m_posRatio - TRIANGLE_WIDTHHALF);
        //����
        points[1] = QPointF(TRANSPARENT_LENGTH - TRIANGLE_HEIGHT, height() * m_posRatio);
        //�ױ���
        points[2] = QPointF(TRANSPARENT_LENGTH, height() * m_posRatio + TRIANGLE_WIDTHHALF);
        break;
    }

    case DIRECT::DIRECT_TOP:
    {
        //�ױ���
        points[0] = QPointF(width() * m_posRatio - TRIANGLE_WIDTHHALF, TRANSPARENT_LENGTH);
        //����
        points[1] = QPointF(width() * m_posRatio, TRANSPARENT_LENGTH - TRIANGLE_HEIGHT);
        //�ױ���
        points[2] = QPointF(width() * m_posRatio + TRIANGLE_WIDTHHALF, TRANSPARENT_LENGTH);
        break;
    }

    case DIRECT::DIRECT_RIGHT:
    {
        //�ױ���
        points[0] = QPointF(width() - TRANSPARENT_LENGTH, height() * m_posRatio - TRIANGLE_WIDTHHALF);
        //����
        points[1] = QPointF(width() - (TRANSPARENT_LENGTH - TRIANGLE_HEIGHT), height() * m_posRatio);
        //�ױ���
        points[2] = QPointF(width() - TRANSPARENT_LENGTH, height() * m_posRatio + TRIANGLE_WIDTHHALF);
        break;
    }

    case DIRECT::DIRECT_BOTTOM:
    {
        //�ױ���
        points[0] = QPointF(width() * m_posRatio - TRIANGLE_WIDTHHALF, height() - TRANSPARENT_LENGTH);
        //����
        points[1] = QPointF(width() * m_posRatio, height() - (TRANSPARENT_LENGTH - TRIANGLE_HEIGHT));
        //�ױ���
        points[2] = QPointF(width() * m_posRatio + TRIANGLE_WIDTHHALF, height() - TRANSPARENT_LENGTH);
        break;
    }

    default:
        break;
    }

    painter.drawPolygon(points, 3);
}

void BubbleTipsWidget::closeEvent(QCloseEvent* event)
{
    qDebug() << "closeEvent";
}

int BubbleTipsWidget::calculateTextHeight(const QString& text, const QFont& font, int width)
{
    //text-�ı���font-������Ϣ��widith-�ı�������
    QFontMetrics fm(font);
    int flags = Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap;
    QRect rect = fm.boundingRect(0, 0, width, 9999, flags, text);
    return rect.height();
}
