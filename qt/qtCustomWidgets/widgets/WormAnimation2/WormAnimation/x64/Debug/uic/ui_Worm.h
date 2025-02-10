/********************************************************************************
** Form generated from reading UI file 'Worm.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORM_H
#define UI_WORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WormClass
{
public:

    void setupUi(QWidget *WormClass)
    {
        if (WormClass->objectName().isEmpty())
            WormClass->setObjectName("WormClass");
        WormClass->resize(600, 400);

        retranslateUi(WormClass);

        QMetaObject::connectSlotsByName(WormClass);
    } // setupUi

    void retranslateUi(QWidget *WormClass)
    {
        WormClass->setWindowTitle(QCoreApplication::translate("WormClass", "Worm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WormClass: public Ui_WormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORM_H
