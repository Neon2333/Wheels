#ifndef NAVIBUTTONGROUP_H
#define NAVIBUTTONGROUP_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
// namespace Ui {
// class NaviButtons;
// }

//按钮组
class NaviButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit NaviButtonGroup(QWidget *parent = nullptr);
    ~NaviButtonGroup();

    QHBoxLayout* hlay;
    QButtonGroup* btngroup;
private:

protected:
    void paintEvent(QPaintEvent* ev);
};

#endif // NAVIBUTTONGROUP_H
