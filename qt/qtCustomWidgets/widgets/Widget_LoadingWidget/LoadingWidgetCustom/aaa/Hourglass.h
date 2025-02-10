#ifndef HOURGLASS_H
#define HOURGLASS_H
#include "LoadingWidget.h"
class Hourglass : public LoadingWidget
{
public:
    Hourglass(QWidget* parent = nullptr);
    void setColumnVisibility(bool vis);//设置柱子可见性
protected:
    virtual void paintEvent(QPaintEvent * ev) override;
private:
    bool m_columnVisible;
};

#endif // !HOURGLASS_H