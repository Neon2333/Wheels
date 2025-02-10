#include "ScrollBarCustom.h"

ScrollBarCustom::ScrollBarCustom(QWidget *parent, int lenHandler, int widthGroove, int widthHandler)
	: QScrollBar(parent), m_lenHandler(lenHandler), m_widthGroove(widthGroove), m_widthHandler(widthHandler)
{
	ui.setupUi(this);

    colorBorder = QColor("transparent");
    colorGroove = QColor("red");
    colorHandler = QColor("gray");
}

ScrollBarCustom::~ScrollBarCustom()
{}

void ScrollBarCustom::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.eraseRect(this->rect());  //��ջ���

    int x = width();
    int y = height();
    qreal ratio = this->value() * 1.0 / this->maximum();    //��ǰֵ�����ֵ�ı���

    p.setRenderHints(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(colorBorder);  //�������߿���ɫ
    p.setPen(pen);

    if (this->orientation() == Qt::Vertical) //��ֱ���������
    {
        //��
        p.setBrush(QBrush(colorGroove));
        p.drawRoundedRect(QRectF((x - m_widthGroove)/2, 20, m_widthGroove, y - 40), m_widthGroove /2, m_widthGroove /2); // width=W��height=y-40����������20����������(x-W)/2

        //���飨Բ�λ�Բ�Ǿ��Σ�
        int R = m_widthGroove + m_widthHandler;    //Բ��ֱ��
        int _y = (y - 40 - R) * ratio;    //Բ���Ͻ�������
        p.setBrush(QBrush(colorHandler));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF((x - R) / 2, _y + 20, R, R + m_lenHandler), R * 0.5, R * 0.5);
    }
    else//ˮƽ���������
    {
        //��
        p.setBrush(QBrush(colorGroove));
        p.drawRoundedRect(QRectF(20, (y - m_widthGroove)/2, x - 40, m_widthGroove), m_widthGroove /2, m_widthGroove /2); // width=W��height=y-40����������20����������(x-W)/2

        //���飨Բ�λ�Բ�Ǿ��Σ�
        int R = m_widthGroove + m_widthHandler;    //Բ��ֱ��
        int _x = (x - 40 - R) * ratio;    //Բ���Ͻ�������
        p.setBrush(QBrush(colorHandler));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF(_x + 20, (y - R) / 2, R + m_lenHandler, R), R * 0.5, R * 0.5);
    }
}