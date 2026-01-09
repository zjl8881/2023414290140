/********************************************************************************
** Form generated from reading UI file 'dialogadddevice.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDDEVICE_H
#define UI_DIALOGADDDEVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogAddDevice
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QLineEdit *editName;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelModel;
    QLineEdit *editModel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelTotal;
    QLineEdit *editCount;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelStatus;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *editNormalQty;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *editFaultQty;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogAddDevice)
    {
        if (DialogAddDevice->objectName().isEmpty())
            DialogAddDevice->setObjectName(QString::fromUtf8("DialogAddDevice"));
        DialogAddDevice->resize(359, 301);
        verticalLayout_2 = new QVBoxLayout(DialogAddDevice);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelName = new QLabel(DialogAddDevice);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        horizontalLayout->addWidget(labelName);

        editName = new QLineEdit(DialogAddDevice);
        editName->setObjectName(QString::fromUtf8("editName"));

        horizontalLayout->addWidget(editName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelModel = new QLabel(DialogAddDevice);
        labelModel->setObjectName(QString::fromUtf8("labelModel"));

        horizontalLayout_5->addWidget(labelModel);

        editModel = new QLineEdit(DialogAddDevice);
        editModel->setObjectName(QString::fromUtf8("editModel"));

        horizontalLayout_5->addWidget(editModel);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelTotal = new QLabel(DialogAddDevice);
        labelTotal->setObjectName(QString::fromUtf8("labelTotal"));

        horizontalLayout_6->addWidget(labelTotal);

        editCount = new QLineEdit(DialogAddDevice);
        editCount->setObjectName(QString::fromUtf8("editCount"));

        horizontalLayout_6->addWidget(editCount);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelStatus = new QLabel(DialogAddDevice);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));

        horizontalLayout_4->addWidget(labelStatus);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(DialogAddDevice);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        editNormalQty = new QLineEdit(DialogAddDevice);
        editNormalQty->setObjectName(QString::fromUtf8("editNormalQty"));

        horizontalLayout_3->addWidget(editNormalQty);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(DialogAddDevice);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        editFaultQty = new QLineEdit(DialogAddDevice);
        editFaultQty->setObjectName(QString::fromUtf8("editFaultQty"));

        horizontalLayout_2->addWidget(editFaultQty);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 139, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(DialogAddDevice);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(DialogAddDevice);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogAddDevice, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogAddDevice, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAddDevice);
    } // setupUi

    void retranslateUi(QDialog *DialogAddDevice)
    {
        DialogAddDevice->setWindowTitle(QCoreApplication::translate("DialogAddDevice", "Dialog", nullptr));
        labelName->setText(QCoreApplication::translate("DialogAddDevice", "\350\256\276\345\244\207\345\220\215\347\247\260\357\274\232", nullptr));
        labelModel->setText(QCoreApplication::translate("DialogAddDevice", "\350\256\276\345\244\207\350\247\204\346\240\274\357\274\232", nullptr));
        labelTotal->setText(QCoreApplication::translate("DialogAddDevice", "\350\256\276\345\244\207\346\200\273\346\225\260\357\274\232", nullptr));
        labelStatus->setText(QCoreApplication::translate("DialogAddDevice", "\350\256\276\345\244\207\347\212\266\346\200\201\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("DialogAddDevice", "\346\255\243\345\270\270\346\225\260\351\207\217\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("DialogAddDevice", "\346\225\205\351\232\234\346\225\260\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogAddDevice: public Ui_DialogAddDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDDEVICE_H
