/********************************************************************************
** Form generated from reading UI file 'TextPoint.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTPOINT_H
#define UI_TEXTPOINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextPointClass
{
public:

    void setupUi(QWidget *TextPointClass)
    {
        if (TextPointClass->objectName().isEmpty())
            TextPointClass->setObjectName("TextPointClass");
        TextPointClass->resize(600, 400);

        retranslateUi(TextPointClass);

        QMetaObject::connectSlotsByName(TextPointClass);
    } // setupUi

    void retranslateUi(QWidget *TextPointClass)
    {
        TextPointClass->setWindowTitle(QCoreApplication::translate("TextPointClass", "TextPoint", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextPointClass: public Ui_TextPointClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTPOINT_H
