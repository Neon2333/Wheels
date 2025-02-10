#include "navibuttons.h"
#include <QPainter>
#include <QStyleOption>

NaviButtons::NaviButtons(QWidget *parent)
    : QWidget(parent)
{
    hlay_buttons = new QHBoxLayout;
    this->setLayout(hlay_buttons);
}

NaviButtons::~NaviButtons()
{
    delete hlay_buttons;
}

void NaviButtons::paintEvent(QPaintEvent *ev)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
