/********************************************************************************
** Form generated from reading UI file 'formgraphic.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMGRAPHIC_H
#define UI_FORMGRAPHIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormGraphic
{
public:

    void setupUi(QWidget *FormGraphic)
    {
        if (FormGraphic->objectName().isEmpty())
            FormGraphic->setObjectName("FormGraphic");
        FormGraphic->resize(602, 509);

        retranslateUi(FormGraphic);

        QMetaObject::connectSlotsByName(FormGraphic);
    } // setupUi

    void retranslateUi(QWidget *FormGraphic)
    {
        FormGraphic->setWindowTitle(QCoreApplication::translate("FormGraphic", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormGraphic: public Ui_FormGraphic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMGRAPHIC_H
