/********************************************************************************
** Form generated from reading UI file 'ASD.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASD_H
#define UI_ASD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ASDClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ASDClass)
    {
        if (ASDClass->objectName().isEmpty())
            ASDClass->setObjectName("ASDClass");
        ASDClass->resize(600, 400);
        menuBar = new QMenuBar(ASDClass);
        menuBar->setObjectName("menuBar");
        ASDClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ASDClass);
        mainToolBar->setObjectName("mainToolBar");
        ASDClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ASDClass);
        centralWidget->setObjectName("centralWidget");
        ASDClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ASDClass);
        statusBar->setObjectName("statusBar");
        ASDClass->setStatusBar(statusBar);

        retranslateUi(ASDClass);

        QMetaObject::connectSlotsByName(ASDClass);
    } // setupUi

    void retranslateUi(QMainWindow *ASDClass)
    {
        ASDClass->setWindowTitle(QCoreApplication::translate("ASDClass", "ASD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ASDClass: public Ui_ASDClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASD_H
