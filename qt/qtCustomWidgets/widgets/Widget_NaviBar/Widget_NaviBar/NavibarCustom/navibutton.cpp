#if 0

#include "navibutton.h"
#include <QPainter>


NaviButton::NaviButton(QWidget *parent)
    : QPushButton(parent)
{
    m_font = QFont("Microsoft Yahei",10);//默认字体
    m_shadowEffect = new QGraphicsDropShadowEffect(this);// 设置阴影效果
    m_shadowEffect->setBlurRadius(150); // 模糊半径
    m_shadowEffect->setOffset(0, 0); // 阴影偏移
    m_shadowEffect->setColor(QColor(m_btnColor.red(), m_btnColor.green(), m_btnColor.blue(),180)); // 阴影颜色和透明度
    setGraphicsEffect(m_shadowEffect);
}

NaviButton::~NaviButton()
{
}

void NaviButton::setColor(QColor btnColor)
{
    m_btnColor=btnColor;
}

void NaviButton::setIcon(QIcon icon, QSize iconSize)
{
    m_iconNormal=icon;
    m_iconSizeNormal=iconSize;
    update();
}

void NaviButton::setText(QString text, QColor textColor, QFont font)
{
    m_text=text;
    m_textColor=textColor;
    update();
}

void NaviButton::paintEvent(QPaintEvent *ev)
{
    int w = width();
    int h = height();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_btnColor));
    painter.drawRoundedRect(rect().adjusted(5, 5, -5, -5), 10, 10); // 绘制圆角矩形

    if (!m_iconNormal.isNull())
    {
        QSize iconSize(w * 0.3, h * 0.3);
        QPixmap icon = m_iconNormal.pixmap(iconSize);
        painter.drawPixmap(QRect(w / 2 - iconSize.width() / 2, h / 2 - iconSize.height() / 2, w * 0.3,h * 0.3), icon);
    }

    if(!m_text.isEmpty())
    {
        QFontMetrics fm(m_font);
        qreal textw = fm.horizontalAdvance(m_text);
        qreal texth = fm.height();
        painter.setPen(m_textColor);
        painter.setFont(m_font);
        painter.drawText(QPointF((w - textw) / 2, 0.5 * h + texth / 4), m_text);
    }
}

#endif
