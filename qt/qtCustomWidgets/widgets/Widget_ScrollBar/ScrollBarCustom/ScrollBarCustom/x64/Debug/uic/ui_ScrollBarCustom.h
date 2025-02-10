/********************************************************************************
** Form generated from reading UI file 'ScrollBarCustom.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCROLLBARCUSTOM_H
#define UI_SCROLLBARCUSTOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScrollBarCustomClass
{
public:

    void setupUi(QWidget *ScrollBarCustomClass)
    {
        if (ScrollBarCustomClass->objectName().isEmpty())
            ScrollBarCustomClass->setObjectName("ScrollBarCustomClass");
        ScrollBarCustomClass->resize(600, 400);

        retranslateUi(ScrollBarCustomClass);

        QMetaObject::connectSlotsByName(ScrollBarCustomClass);
    } // setupUi

    void retranslateUi(QWidget *ScrollBarCustomClass)
    {
        ScrollBarCustomClass->setWindowTitle(QCoreApplication::translate("ScrollBarCustomClass", "ScrollBarCustom", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScrollBarCustomClass: public Ui_ScrollBarCustomClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCROLLBARCUSTOM_H
