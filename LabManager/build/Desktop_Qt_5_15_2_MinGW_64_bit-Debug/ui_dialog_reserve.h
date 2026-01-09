/********************************************************************************
** Form generated from reading UI file 'dialog_reserve.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_RESERVE_H
#define UI_DIALOG_RESERVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogReserve
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboName;
    QLineEdit *editUser;
    QLineEdit *editCount;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogReserve)
    {
        if (DialogReserve->objectName().isEmpty())
            DialogReserve->setObjectName(QString::fromUtf8("DialogReserve"));
        DialogReserve->resize(467, 343);
        verticalLayout_3 = new QVBoxLayout(DialogReserve);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(DialogReserve);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_4 = new QLabel(DialogReserve);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label_3 = new QLabel(DialogReserve);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        comboName = new QComboBox(DialogReserve);
        comboName->setObjectName(QString::fromUtf8("comboName"));

        verticalLayout_2->addWidget(comboName);

        editUser = new QLineEdit(DialogReserve);
        editUser->setObjectName(QString::fromUtf8("editUser"));

        verticalLayout_2->addWidget(editUser);

        editCount = new QLineEdit(DialogReserve);
        editCount->setObjectName(QString::fromUtf8("editCount"));

        verticalLayout_2->addWidget(editCount);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(DialogReserve);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(DialogReserve);

        QMetaObject::connectSlotsByName(DialogReserve);
    } // setupUi

    void retranslateUi(QDialog *DialogReserve)
    {
        DialogReserve->setWindowTitle(QCoreApplication::translate("DialogReserve", "\346\226\260\345\242\236\350\256\276\345\244\207\345\205\245\345\272\223", nullptr));
        label->setText(QCoreApplication::translate("DialogReserve", "\350\256\276\345\244\207\345\220\215\347\247\260\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("DialogReserve", "\344\275\277\347\224\250\350\200\205\345\220\215\347\247\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("DialogReserve", "\350\256\276\345\244\207\346\225\260\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogReserve: public Ui_DialogReserve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_RESERVE_H
