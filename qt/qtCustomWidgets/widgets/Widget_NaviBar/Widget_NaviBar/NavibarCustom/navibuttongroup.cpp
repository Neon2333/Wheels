#include "navibuttongroup.h"
#include <QPainter>
#include <QStyleOption>

NaviButtonGroup::NaviButtonGroup(QWidget *parent)
    : QWidget(parent)
{
    btngroup=new QButtonGroup(this);

    hlay = new QHBoxLayout;
    this->setLayout(hlay);
}

NaviButtonGroup::~NaviButtonGroup()
{
    delete hlay;
}

void NaviButtonGroup::paintEvent(QPaintEvent *ev)
{
    // Q_UNUSED(ev);
    QWidget::paintEvent(ev);

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}
