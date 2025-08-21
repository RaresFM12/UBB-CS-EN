/********************************************************************************
** Form generated from reading UI file 'Assignement89.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSIGNEMENT89_H
#define UI_ASSIGNEMENT89_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Assignement89Class
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QListWidget *listWidget_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Assignement89Class)
    {
        if (Assignement89Class->objectName().isEmpty())
            Assignement89Class->setObjectName("Assignement89Class");
        Assignement89Class->resize(752, 601);
        centralWidget = new QWidget(Assignement89Class);
        centralWidget->setObjectName("centralWidget");
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 10, 331, 261));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(460, 60, 161, 26));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(460, 140, 161, 26));
        listWidget_2 = new QListWidget(centralWidget);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(30, 290, 281, 211));
        Assignement89Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Assignement89Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 752, 26));
        Assignement89Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Assignement89Class);
        mainToolBar->setObjectName("mainToolBar");
        Assignement89Class->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Assignement89Class);
        statusBar->setObjectName("statusBar");
        Assignement89Class->setStatusBar(statusBar);

        retranslateUi(Assignement89Class);

        QMetaObject::connectSlotsByName(Assignement89Class);
    } // setupUi

    void retranslateUi(QMainWindow *Assignement89Class)
    {
        Assignement89Class->setWindowTitle(QCoreApplication::translate("Assignement89Class", "Assignement89", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Assignement89Class: public Ui_Assignement89Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSIGNEMENT89_H
