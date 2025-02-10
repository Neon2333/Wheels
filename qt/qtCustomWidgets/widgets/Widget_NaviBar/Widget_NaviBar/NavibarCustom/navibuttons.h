#ifndef NAVIBUTTONS_H
#define NAVIBUTTONS_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
namespace Ui {
class NaviButtons;
}

class NaviButtons : public QWidget
{
    Q_OBJECT

public:
    explicit NaviButtons(QWidget *parent = nullptr);
    ~NaviButtons();

    QHBoxLayout* hlay_buttons;
private:

protected:
    void paintEvent(QPaintEvent* ev);
};

#endif // NAVIBUTTONS_H
