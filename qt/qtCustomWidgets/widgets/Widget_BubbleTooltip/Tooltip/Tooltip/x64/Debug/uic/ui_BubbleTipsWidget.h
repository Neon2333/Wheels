/********************************************************************************
** Form generated from reading UI file 'BubbleTipsWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUBBLETIPSWIDGET_H
#define UI_BUBBLETIPSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BubbleTipsWidgetClass
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_icon;
    QLabel *label_tips;

    void setupUi(QWidget *BubbleTipsWidgetClass)
    {
        if (BubbleTipsWidgetClass->objectName().isEmpty())
            BubbleTipsWidgetClass->setObjectName("BubbleTipsWidgetClass");
        BubbleTipsWidgetClass->resize(600, 400);
        horizontalLayout = new QHBoxLayout(BubbleTipsWidgetClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(BubbleTipsWidgetClass);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_icon = new QLabel(widget);
        label_icon->setObjectName("label_icon");

        horizontalLayout_2->addWidget(label_icon);

        label_tips = new QLabel(widget);
        label_tips->setObjectName("label_tips");

        horizontalLayout_2->addWidget(label_tips);


        horizontalLayout->addWidget(widget);


        retranslateUi(BubbleTipsWidgetClass);

        QMetaObject::connectSlotsByName(BubbleTipsWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *BubbleTipsWidgetClass)
    {
        BubbleTipsWidgetClass->setWindowTitle(QCoreApplication::translate("BubbleTipsWidgetClass", "BubbleTipsWidget", nullptr));
        label_icon->setText(QString());
        label_tips->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BubbleTipsWidgetClass: public Ui_BubbleTipsWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUBBLETIPSWIDGET_H
