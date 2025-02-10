#if 0
#ifndef NAVIBUTTON_H
#define NAVIBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class NavigationButton;
}

class NaviButton : public QPushButton
{
    Q_OBJECT

public:
    explicit NaviButton(QWidget *parent = nullptr);
    ~NaviButton();

    void setColor(QColor btnColor);
    void setIcon(QIcon icon, QSize iconSize);
    void setText(QString text, QColor textColor, QFont font);

private:
    QColor m_btnColor;

    QIcon m_iconNormal;
    QSize m_iconSizeNormal;

    QString m_text;
    QColor m_textColor;
    QFont m_font;

    QGraphicsDropShadowEffect* m_shadowEffect;

protected:
    void paintEvent(QPaintEvent* ev);
};

#endif // NAVIBUTTON_H

#endif
