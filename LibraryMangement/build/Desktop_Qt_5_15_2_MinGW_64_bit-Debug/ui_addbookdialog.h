/********************************************************************************
** Form generated from reading UI file 'addbookdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDBOOKDIALOG_H
#define UI_ADDBOOKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_1;
    QLabel *labelId;
    QLineEdit *editId;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelName;
    QLineEdit *editName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelAuthor;
    QLineEdit *editAuthor;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelCount;
    QSpinBox *spinCount;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        labelId = new QLabel(Dialog);
        labelId->setObjectName(QString::fromUtf8("labelId"));

        horizontalLayout_1->addWidget(labelId);

        editId = new QLineEdit(Dialog);
        editId->setObjectName(QString::fromUtf8("editId"));

        horizontalLayout_1->addWidget(editId);


        verticalLayout->addLayout(horizontalLayout_1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelName = new QLabel(Dialog);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        horizontalLayout_2->addWidget(labelName);

        editName = new QLineEdit(Dialog);
        editName->setObjectName(QString::fromUtf8("editName"));

        horizontalLayout_2->addWidget(editName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelAuthor = new QLabel(Dialog);
        labelAuthor->setObjectName(QString::fromUtf8("labelAuthor"));

        horizontalLayout_3->addWidget(labelAuthor);

        editAuthor = new QLineEdit(Dialog);
        editAuthor->setObjectName(QString::fromUtf8("editAuthor"));

        horizontalLayout_3->addWidget(editAuthor);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelCount = new QLabel(Dialog);
        labelCount->setObjectName(QString::fromUtf8("labelCount"));

        horizontalLayout_4->addWidget(labelCount);

        spinCount = new QSpinBox(Dialog);
        spinCount->setObjectName(QString::fromUtf8("spinCount"));
        spinCount->setMinimum(0);
        spinCount->setValue(1);

        horizontalLayout_4->addWidget(spinCount);


        verticalLayout->addLayout(horizontalLayout_4);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "\346\267\273\345\212\240\345\233\276\344\271\246", nullptr));
        labelId->setText(QCoreApplication::translate("Dialog", "\345\233\276\344\271\246\347\274\226\345\217\267\357\274\232", nullptr));
        labelName->setText(QCoreApplication::translate("Dialog", "\345\233\276\344\271\246\345\220\215\347\247\260\357\274\232", nullptr));
        labelAuthor->setText(QCoreApplication::translate("Dialog", "\344\275\234\350\200\205\357\274\232", nullptr));
        labelCount->setText(QCoreApplication::translate("Dialog", "\345\272\223\345\255\230\346\225\260\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDBOOKDIALOG_H
