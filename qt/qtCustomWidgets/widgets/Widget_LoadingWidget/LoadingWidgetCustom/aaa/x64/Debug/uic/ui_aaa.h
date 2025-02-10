/********************************************************************************
** Form generated from reading UI file 'aaa.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AAA_H
#define UI_AAA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_aaaClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *aaaClass)
    {
        if (aaaClass->objectName().isEmpty())
            aaaClass->setObjectName("aaaClass");
        aaaClass->resize(600, 400);
        menuBar = new QMenuBar(aaaClass);
        menuBar->setObjectName("menuBar");
        aaaClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(aaaClass);
        mainToolBar->setObjectName("mainToolBar");
        aaaClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(aaaClass);
        centralWidget->setObjectName("centralWidget");
        aaaClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(aaaClass);
        statusBar->setObjectName("statusBar");
        aaaClass->setStatusBar(statusBar);

        retranslateUi(aaaClass);

        QMetaObject::connectSlotsByName(aaaClass);
    } // setupUi

    void retranslateUi(QMainWindow *aaaClass)
    {
        aaaClass->setWindowTitle(QCoreApplication::translate("aaaClass", "aaa", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aaaClass: public Ui_aaaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AAA_H
