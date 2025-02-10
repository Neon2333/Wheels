#pragma once

#include <QWidget>
#include "ui_bubbleTipsWidget.h"
#include <QIcon>
#include <QFontMetrics>
#include <QPropertyAnimation>

// �����εĸ߶Ⱥ͵ױ߳���
#define TRIANGLE_HEIGHT 15
#define TRIANGLE_WIDTHHALF  5
// ͸����ȣ���Ҫ����TRIANGLE_HEIGHT����������������ʾ��
#define TRANSPARENT_LENGTH 20
// ������߾�
#define LEFT_MARGIN 0
// �����ϱ߾�
#define TOP_MARGIN 0

enum class DIRECT
{
    DIRECT_LEFT = 1,
    DIRECT_TOP,
    DIRECT_RIGHT,
    DIRECT_BOTTOM
};

class BubbleTipsWidget : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(QColor backColor READ backColor WRITE setBackColor)

public:
    BubbleTipsWidget(QWidget* parent = nullptr, int widthFixed = 300);
    ~BubbleTipsWidget();

    //����ɫ
    QColor backColor() const;
    void setBackColor(QColor color);

    // �������Ƿ���(��������)��λ��ϵ��(��� * ϵ��)
    void setDirect(DIRECT direct = DIRECT::DIRECT_TOP, double size = 0.75);

    //�ı�����
    void setContent(const QString& content, QColor color = {});

    //�ı�font
    void setContentFont(QFont font = {});

    //�ı��߾�
    void setLeftTopMargin(int leftMargin = LEFT_MARGIN, int topMargin = TOP_MARGIN);

    //�趨ͼ�ꡢ�ߴ磨�ߴ�Ҫ�趨�ʵ���ȷ��ͼ��������ʾ��
    void setIcon(QIcon icon, int w = 100, int h = 100);

    //���������ζ��㣬ȷ������bubbletips�����Ͻ�����
    void setPositionByTriangle(int x, int y);

    //�趨Ŀ��ؼ����Զ�����������Ŀ��ؼ���λ�����ü�ͷ����λ��
    void setAutoPosition(bool isAuto, QWidget* target);

    //����������ʾ
    void animeShow();

    //������ʧ
    void animeClose();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void closeEvent(QCloseEvent* event) override;

private:
    Ui::BubbleTipsWidgetClass ui;

    QPropertyAnimation m_animationEnter;
    QPropertyAnimation m_animationLeave;

    int m_widthFixed;                       //��ʾ���ȣ���Ȳ�Ҫ̫�󣬸߶�����Ӧ��
    int m_leftMargin = LEFT_MARGIN;         //�������ұ߾�
    int m_topMargin = TOP_MARGIN;           //�������±߾�
    int m_textHeight;   //�ı���ʾʵ�ʸ߶ȣ���m_iconHeight����ȷ���ϴ�����Ϊheight()ʵ��ȡֵ��
    int m_iconHeight;   //iconʵ�ʸ߶�

    int m_triposX = 0;  //�����ζ������꣨�����Ļ�ľ������꣩
    int m_triposY = 0;  //�����ζ�������
    int m_posX = 0;     //this���ڵ����꣨�����Ļ�ľ������꣩
    int m_posY = 0;     //this���ڵ�����

    QFont m_font;                             //�ı�������Ϣ
    QColor  m_backColor{ 255, 0, 255, 255 };  //����ɫ

    DIRECT  m_direct = DIRECT::DIRECT_TOP;    //������λ��
    double m_posRatio = 0.75;                 //������λ�ã���������ռ�߳�������

    bool m_autoPosition = false;              //�Ƿ��Զ���target�ؼ���Ѱ��λ����ʾ
    QWidget* m_target;  //����tips�Ŀؼ������������趨�������ģ�

    QIcon m_icon;       //ͼ��
    int calculateTextHeight(const QString& text, const QFont& font, int width); //�����ı���ʾ�߶�
};
