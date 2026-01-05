/********************************************************************************
** Form generated from reading UI file 'patienteditview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTEDITVIEW_H
#define UI_PATIENTEDITVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientEditView
{
public:
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *dbEditID;
    QLineEdit *dbEditName;
    QLineEdit *dbEditIDCard;
    QComboBox *dbComboSex;
    QDateEdit *dbDataEditDOB;
    QSpinBox *dbSpinHeight;
    QSpinBox *dbSpinWeight;
    QLineEdit *dbEditMobile;
    QLineEdit *dbCreatedTimeStamp;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *PatientEditView)
    {
        if (PatientEditView->objectName().isEmpty())
            PatientEditView->setObjectName(QString::fromUtf8("PatientEditView"));
        PatientEditView->resize(654, 549);
        verticalLayout_4 = new QVBoxLayout(PatientEditView);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_3 = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(PatientEditView);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(PatientEditView);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(PatientEditView);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(PatientEditView);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(PatientEditView);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(PatientEditView);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(PatientEditView);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(PatientEditView);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(PatientEditView);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dbEditID = new QLineEdit(PatientEditView);
        dbEditID->setObjectName(QString::fromUtf8("dbEditID"));

        verticalLayout_2->addWidget(dbEditID);

        dbEditName = new QLineEdit(PatientEditView);
        dbEditName->setObjectName(QString::fromUtf8("dbEditName"));

        verticalLayout_2->addWidget(dbEditName);

        dbEditIDCard = new QLineEdit(PatientEditView);
        dbEditIDCard->setObjectName(QString::fromUtf8("dbEditIDCard"));

        verticalLayout_2->addWidget(dbEditIDCard);

        dbComboSex = new QComboBox(PatientEditView);
        dbComboSex->addItem(QString());
        dbComboSex->addItem(QString());
        dbComboSex->setObjectName(QString::fromUtf8("dbComboSex"));

        verticalLayout_2->addWidget(dbComboSex);

        dbDataEditDOB = new QDateEdit(PatientEditView);
        dbDataEditDOB->setObjectName(QString::fromUtf8("dbDataEditDOB"));

        verticalLayout_2->addWidget(dbDataEditDOB);

        dbSpinHeight = new QSpinBox(PatientEditView);
        dbSpinHeight->setObjectName(QString::fromUtf8("dbSpinHeight"));

        verticalLayout_2->addWidget(dbSpinHeight);

        dbSpinWeight = new QSpinBox(PatientEditView);
        dbSpinWeight->setObjectName(QString::fromUtf8("dbSpinWeight"));

        verticalLayout_2->addWidget(dbSpinWeight);

        dbEditMobile = new QLineEdit(PatientEditView);
        dbEditMobile->setObjectName(QString::fromUtf8("dbEditMobile"));

        verticalLayout_2->addWidget(dbEditMobile);

        dbCreatedTimeStamp = new QLineEdit(PatientEditView);
        dbCreatedTimeStamp->setObjectName(QString::fromUtf8("dbCreatedTimeStamp"));

        verticalLayout_2->addWidget(dbCreatedTimeStamp);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton = new QPushButton(PatientEditView);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(PatientEditView);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_3->addWidget(pushButton_2);


        horizontalLayout->addLayout(verticalLayout_3);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(77, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        retranslateUi(PatientEditView);

        QMetaObject::connectSlotsByName(PatientEditView);
    } // setupUi

    void retranslateUi(QWidget *PatientEditView)
    {
        PatientEditView->setWindowTitle(QCoreApplication::translate("PatientEditView", "\347\274\226\350\276\221\346\202\243\350\200\205\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("PatientEditView", "ID\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("PatientEditView", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("PatientEditView", "\350\272\253\344\273\275\350\257\201\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("PatientEditView", "\346\200\247\345\210\253\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("PatientEditView", "\345\207\272\347\224\237\346\227\245\346\234\237\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("PatientEditView", "\350\272\253\351\253\230\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("PatientEditView", "\344\275\223\351\207\215\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("PatientEditView", "\346\211\213\346\234\272\345\217\267\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("PatientEditView", "\345\210\233\345\273\272\346\227\266\351\227\264\357\274\232", nullptr));
        dbComboSex->setItemText(0, QCoreApplication::translate("PatientEditView", "\347\224\267", nullptr));
        dbComboSex->setItemText(1, QCoreApplication::translate("PatientEditView", "\345\245\263", nullptr));

        pushButton->setText(QCoreApplication::translate("PatientEditView", "\344\277\235\345\255\230", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PatientEditView", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientEditView: public Ui_PatientEditView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTEDITVIEW_H
