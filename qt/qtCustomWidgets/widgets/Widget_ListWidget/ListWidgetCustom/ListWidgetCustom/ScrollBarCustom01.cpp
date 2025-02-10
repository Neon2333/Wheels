#include "ScrollBarCustom01.h"

ScrollBarCustom01::ScrollBarCustom01(QWidget *parent)
	: QScrollBar(parent)
{
	ui.setupUi(this);
}

ScrollBarCustom01::~ScrollBarCustom01()
{}

void ScrollBarCustom01::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.eraseRect(this->rect());  //��ջ���

    int x = width();
    int y = height();
    qreal ratio = this->value() * 1.0 / this->maximum();    //��ǰֵ�����ֵ�ı���

    p.setRenderHints(QPainter::Antialiasing);
    QPen pen;
    pen.setColor("black");  //��������ɫ
    p.setPen(pen);

    if (this->orientation() == Qt::Vertical)
    {
        //��ֱ���������
        //�����
        p.drawRoundedRect(QRectF(x / 2 - 1, 20, 2, y - 40), 1, 1); // w=2��h=y-40����������20����������x/2-1

        //��Բ��Բ�Ǿ��Σ�
        int R = x - 2;    //Բֱ����Բ�Ǿ���ģ��Բ��
        int _y = (y - 40 - R) * ratio;    //Բ���Ͻ�������
        p.setBrush(QBrush("gray"));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF((x - R) / 2, _y + 20, R, R), R, R);
    }
    else
    {
        //ˮƽ���������
        //�����
        p.drawRoundedRect(QRectF(20, y / 2 - 1, x - 40, 2), 1, 1); // w=2��h=y-40����������20����������x/2-1

        //��Բ��Բ�Ǿ��Σ�
        int R = y - 2;    //Բֱ����Բ�Ǿ���ģ��Բ��
        int _x = (x - 40 - R) * ratio;    //Բ���Ͻ�������
        p.setBrush(QBrush("gray"));
        pen.setWidth(2);
        p.drawRoundedRect(QRectF(_x + 20, (y - R) / 2, R, R), R, R);
    }

}