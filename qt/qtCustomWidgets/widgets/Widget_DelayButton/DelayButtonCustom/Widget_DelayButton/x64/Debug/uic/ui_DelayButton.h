/********************************************************************************
** Form generated from reading UI file 'DelayButton.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELAYBUTTON_H
#define UI_DELAYBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DelayButtonClass
{
public:

    void setupUi(QWidget *DelayButtonClass)
    {
        if (DelayButtonClass->objectName().isEmpty())
            DelayButtonClass->setObjectName("DelayButtonClass");
        DelayButtonClass->resize(600, 400);

        retranslateUi(DelayButtonClass);

        QMetaObject::connectSlotsByName(DelayButtonClass);
    } // setupUi

    void retranslateUi(QWidget *DelayButtonClass)
    {
        DelayButtonClass->setWindowTitle(QCoreApplication::translate("DelayButtonClass", "DelayButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DelayButtonClass: public Ui_DelayButtonClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELAYBUTTON_H
