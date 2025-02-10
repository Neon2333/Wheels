/********************************************************************************
** Form generated from reading UI file 'SideBar.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBAR_H
#define UI_SIDEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideBarClass
{
public:

    void setupUi(QWidget *SideBarClass)
    {
        if (SideBarClass->objectName().isEmpty())
            SideBarClass->setObjectName("SideBarClass");
        SideBarClass->resize(600, 400);

        retranslateUi(SideBarClass);

        QMetaObject::connectSlotsByName(SideBarClass);
    } // setupUi

    void retranslateUi(QWidget *SideBarClass)
    {
        SideBarClass->setWindowTitle(QCoreApplication::translate("SideBarClass", "SideBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideBarClass: public Ui_SideBarClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBAR_H
