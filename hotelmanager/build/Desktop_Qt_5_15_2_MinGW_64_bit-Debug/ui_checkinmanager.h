/********************************************************************************
** Form generated from reading UI file 'checkinmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKINMANAGER_H
#define UI_CHECKINMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckInManager
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leCustomerName;
    QLabel *label_2;
    QLineEdit *leIdCard;
    QLabel *label_3;
    QLineEdit *lePhone;
    QLineEdit *leCustomerSearch;
    QPushButton *btnSearchCustomer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QComboBox *cmbRoomType;
    QLabel *label_5;
    QComboBox *cmbRoom;
    QLabel *label_6;
    QDateEdit *deCheckIn;
    QLabel *label_7;
    QDateEdit *deCheckOut;
    QLabel *label_8;
    QLineEdit *leExpectedAmount;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCheckIn;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCancel;
    QLabel *labelStatus;

    void setupUi(QDialog *CheckInManager)
    {
        if (CheckInManager->objectName().isEmpty())
            CheckInManager->setObjectName(QString::fromUtf8("CheckInManager"));
        CheckInManager->resize(800, 600);
        verticalLayoutWidget = new QWidget(CheckInManager);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 780, 580));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leCustomerName = new QLineEdit(groupBox);
        leCustomerName->setObjectName(QString::fromUtf8("leCustomerName"));

        gridLayout->addWidget(leCustomerName, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        leIdCard = new QLineEdit(groupBox);
        leIdCard->setObjectName(QString::fromUtf8("leIdCard"));

        gridLayout->addWidget(leIdCard, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        lePhone = new QLineEdit(groupBox);
        lePhone->setObjectName(QString::fromUtf8("lePhone"));

        gridLayout->addWidget(lePhone, 1, 1, 1, 1);

        leCustomerSearch = new QLineEdit(groupBox);
        leCustomerSearch->setObjectName(QString::fromUtf8("leCustomerSearch"));

        gridLayout->addWidget(leCustomerSearch, 1, 2, 1, 1);

        btnSearchCustomer = new QPushButton(groupBox);
        btnSearchCustomer->setObjectName(QString::fromUtf8("btnSearchCustomer"));

        gridLayout->addWidget(btnSearchCustomer, 1, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        cmbRoomType = new QComboBox(groupBox_2);
        cmbRoomType->setObjectName(QString::fromUtf8("cmbRoomType"));

        gridLayout_2->addWidget(cmbRoomType, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 2, 1, 1);

        cmbRoom = new QComboBox(groupBox_2);
        cmbRoom->setObjectName(QString::fromUtf8("cmbRoom"));

        gridLayout_2->addWidget(cmbRoom, 0, 3, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        deCheckIn = new QDateEdit(groupBox_2);
        deCheckIn->setObjectName(QString::fromUtf8("deCheckIn"));
        deCheckIn->setCalendarPopup(true);

        gridLayout_2->addWidget(deCheckIn, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 1, 2, 1, 1);

        deCheckOut = new QDateEdit(groupBox_2);
        deCheckOut->setObjectName(QString::fromUtf8("deCheckOut"));
        deCheckOut->setCalendarPopup(true);

        gridLayout_2->addWidget(deCheckOut, 1, 3, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        leExpectedAmount = new QLineEdit(groupBox_2);
        leExpectedAmount->setObjectName(QString::fromUtf8("leExpectedAmount"));
        leExpectedAmount->setReadOnly(true);

        gridLayout_2->addWidget(leExpectedAmount, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 2, 1, 2);


        verticalLayout->addWidget(groupBox_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnCheckIn = new QPushButton(verticalLayoutWidget);
        btnCheckIn->setObjectName(QString::fromUtf8("btnCheckIn"));

        horizontalLayout->addWidget(btnCheckIn);

        btnRefresh = new QPushButton(verticalLayoutWidget);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));

        horizontalLayout->addWidget(btnRefresh);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnCancel = new QPushButton(verticalLayoutWidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);

        labelStatus = new QLabel(verticalLayoutWidget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setAlignment(Qt::AlignCenter);
        labelStatus->setStyleSheet(QString::fromUtf8("color: #666666;"));

        verticalLayout->addWidget(labelStatus);


        retranslateUi(CheckInManager);

        btnCheckIn->setDefault(true);


        QMetaObject::connectSlotsByName(CheckInManager);
    } // setupUi

    void retranslateUi(QDialog *CheckInManager)
    {
        CheckInManager->setWindowTitle(QCoreApplication::translate("CheckInManager", "\345\256\242\346\210\267\345\205\245\344\275\217\347\231\273\350\256\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CheckInManager", "\345\256\242\346\210\267\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("CheckInManager", "\345\256\242\346\210\267\345\247\223\345\220\215:", nullptr));
        label_2->setText(QCoreApplication::translate("CheckInManager", "\350\272\253\344\273\275\350\257\201\345\217\267:", nullptr));
        label_3->setText(QCoreApplication::translate("CheckInManager", "\350\201\224\347\263\273\346\226\271\345\274\217:", nullptr));
        leCustomerSearch->setPlaceholderText(QCoreApplication::translate("CheckInManager", "\350\276\223\345\205\245\345\256\242\346\210\267\345\247\223\345\220\215\346\210\226\350\272\253\344\273\275\350\257\201\345\217\267\346\220\234\347\264\242...", nullptr));
        btnSearchCustomer->setText(QCoreApplication::translate("CheckInManager", "\346\220\234\347\264\242", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CheckInManager", "\345\205\245\344\275\217\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("CheckInManager", "\346\210\277\345\236\213:", nullptr));
        label_5->setText(QCoreApplication::translate("CheckInManager", "\346\210\277\351\227\264\345\217\267:", nullptr));
        label_6->setText(QCoreApplication::translate("CheckInManager", "\345\205\245\344\275\217\346\227\245\346\234\237:", nullptr));
        label_7->setText(QCoreApplication::translate("CheckInManager", "\351\200\200\346\210\277\346\227\245\346\234\237:", nullptr));
        label_8->setText(QCoreApplication::translate("CheckInManager", "\351\242\204\350\256\241\351\207\221\351\242\235:", nullptr));
        btnCheckIn->setText(QCoreApplication::translate("CheckInManager", "\345\212\236\347\220\206\345\205\245\344\275\217", nullptr));
        btnRefresh->setText(QCoreApplication::translate("CheckInManager", "\345\210\267\346\226\260\346\225\260\346\215\256", nullptr));
        btnCancel->setText(QCoreApplication::translate("CheckInManager", "\345\217\226\346\266\210", nullptr));
        labelStatus->setText(QCoreApplication::translate("CheckInManager", "\350\257\267\345\241\253\345\206\231\345\256\214\346\225\264\347\232\204\345\205\245\344\275\217\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckInManager: public Ui_CheckInManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKINMANAGER_H
