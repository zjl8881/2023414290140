/********************************************************************************
** Form generated from reading UI file 'checkoutmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKOUTMANAGER_H
#define UI_CHECKOUTMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckOutManager
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leOrderSearch;
    QPushButton *btnSearchOrder;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leCustomerName;
    QLabel *label_2;
    QLineEdit *leRoomNumber;
    QLabel *label_3;
    QLineEdit *leCheckInDate;
    QLabel *label_4;
    QLineEdit *leCheckOutDate;
    QLabel *label_5;
    QDateEdit *deActualCheckOut;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QLineEdit *leTotalAmount;
    QLabel *label_7;
    QComboBox *cmbPaymentMethod;
    QLabel *label_8;
    QLineEdit *lePaymentAmount;
    QLabel *label_9;
    QLineEdit *leChange;
    QTableView *tableView_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *teNotes;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCheckOut;
    QPushButton *btnCancel;

    void setupUi(QDialog *CheckOutManager)
    {
        if (CheckOutManager->objectName().isEmpty())
            CheckOutManager->setObjectName(QString::fromUtf8("CheckOutManager"));
        CheckOutManager->resize(800, 600);
        verticalLayoutWidget = new QWidget(CheckOutManager);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 780, 580));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leOrderSearch = new QLineEdit(verticalLayoutWidget);
        leOrderSearch->setObjectName(QString::fromUtf8("leOrderSearch"));

        horizontalLayout->addWidget(leOrderSearch);

        btnSearchOrder = new QPushButton(verticalLayoutWidget);
        btnSearchOrder->setObjectName(QString::fromUtf8("btnSearchOrder"));

        horizontalLayout->addWidget(btnSearchOrder);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leCustomerName = new QLineEdit(groupBox);
        leCustomerName->setObjectName(QString::fromUtf8("leCustomerName"));
        leCustomerName->setReadOnly(true);

        gridLayout->addWidget(leCustomerName, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leRoomNumber = new QLineEdit(groupBox);
        leRoomNumber->setObjectName(QString::fromUtf8("leRoomNumber"));
        leRoomNumber->setReadOnly(true);

        gridLayout->addWidget(leRoomNumber, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        leCheckInDate = new QLineEdit(groupBox);
        leCheckInDate->setObjectName(QString::fromUtf8("leCheckInDate"));
        leCheckInDate->setReadOnly(true);

        gridLayout->addWidget(leCheckInDate, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        leCheckOutDate = new QLineEdit(groupBox);
        leCheckOutDate->setObjectName(QString::fromUtf8("leCheckOutDate"));
        leCheckOutDate->setReadOnly(true);

        gridLayout->addWidget(leCheckOutDate, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        deActualCheckOut = new QDateEdit(groupBox);
        deActualCheckOut->setObjectName(QString::fromUtf8("deActualCheckOut"));
        deActualCheckOut->setCalendarPopup(true);

        gridLayout->addWidget(deActualCheckOut, 4, 1, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        leTotalAmount = new QLineEdit(groupBox_2);
        leTotalAmount->setObjectName(QString::fromUtf8("leTotalAmount"));
        leTotalAmount->setReadOnly(true);

        gridLayout_2->addWidget(leTotalAmount, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        cmbPaymentMethod = new QComboBox(groupBox_2);
        cmbPaymentMethod->setObjectName(QString::fromUtf8("cmbPaymentMethod"));

        gridLayout_2->addWidget(cmbPaymentMethod, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        lePaymentAmount = new QLineEdit(groupBox_2);
        lePaymentAmount->setObjectName(QString::fromUtf8("lePaymentAmount"));

        gridLayout_2->addWidget(lePaymentAmount, 2, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        leChange = new QLineEdit(groupBox_2);
        leChange->setObjectName(QString::fromUtf8("leChange"));
        leChange->setReadOnly(true);

        gridLayout_2->addWidget(leChange, 3, 1, 1, 1);


        horizontalLayout_2->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        tableView_2 = new QTableView(verticalLayoutWidget);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));
        tableView_2->setAlternatingRowColors(true);
        tableView_2->setSelectionMode(QAbstractItemView::NoSelection);
        tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableView_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_3 = new QGroupBox(verticalLayoutWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        teNotes = new QTextEdit(groupBox_3);
        teNotes->setObjectName(QString::fromUtf8("teNotes"));

        horizontalLayout_3->addWidget(teNotes);


        verticalLayout_2->addWidget(groupBox_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        btnCheckOut = new QPushButton(verticalLayoutWidget);
        btnCheckOut->setObjectName(QString::fromUtf8("btnCheckOut"));

        horizontalLayout_4->addWidget(btnCheckOut);

        btnCancel = new QPushButton(verticalLayoutWidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout_4->addWidget(btnCancel);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(CheckOutManager);

        btnCheckOut->setDefault(true);


        QMetaObject::connectSlotsByName(CheckOutManager);
    } // setupUi

    void retranslateUi(QDialog *CheckOutManager)
    {
        CheckOutManager->setWindowTitle(QCoreApplication::translate("CheckOutManager", "\345\256\242\346\210\267\351\200\200\346\210\277\347\273\223\347\256\227", nullptr));
        leOrderSearch->setPlaceholderText(QCoreApplication::translate("CheckOutManager", "\350\276\223\345\205\245\350\256\242\345\215\225\345\217\267\343\200\201\345\256\242\346\210\267\345\247\223\345\220\215\346\210\226\346\210\277\351\227\264\345\217\267\346\220\234\347\264\242...", nullptr));
        btnSearchOrder->setText(QCoreApplication::translate("CheckOutManager", "\346\220\234\347\264\242\350\256\242\345\215\225", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CheckOutManager", "\350\256\242\345\215\225\350\257\246\346\203\205", nullptr));
        label->setText(QCoreApplication::translate("CheckOutManager", "\345\256\242\346\210\267\345\247\223\345\220\215:", nullptr));
        label_2->setText(QCoreApplication::translate("CheckOutManager", "\346\210\277\351\227\264\345\217\267:", nullptr));
        label_3->setText(QCoreApplication::translate("CheckOutManager", "\345\205\245\344\275\217\346\227\245\346\234\237:", nullptr));
        label_4->setText(QCoreApplication::translate("CheckOutManager", "\351\200\200\346\210\277\346\227\245\346\234\237:", nullptr));
        label_5->setText(QCoreApplication::translate("CheckOutManager", "\345\256\236\351\231\205\351\200\200\346\210\277\346\227\245\346\234\237:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CheckOutManager", "\347\273\223\347\256\227\344\277\241\346\201\257", nullptr));
        label_6->setText(QCoreApplication::translate("CheckOutManager", "\346\200\273\351\207\221\351\242\235:", nullptr));
        label_7->setText(QCoreApplication::translate("CheckOutManager", "\346\224\257\344\273\230\346\226\271\345\274\217:", nullptr));
        label_8->setText(QCoreApplication::translate("CheckOutManager", "\346\224\257\344\273\230\351\207\221\351\242\235:", nullptr));
        label_9->setText(QCoreApplication::translate("CheckOutManager", "\346\211\276\351\233\266:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CheckOutManager", "\345\244\207\346\263\250", nullptr));
        btnCheckOut->setText(QCoreApplication::translate("CheckOutManager", "\345\212\236\347\220\206\351\200\200\346\210\277", nullptr));
        btnCancel->setText(QCoreApplication::translate("CheckOutManager", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckOutManager: public Ui_CheckOutManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKOUTMANAGER_H
