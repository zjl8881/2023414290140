/********************************************************************************
** Form generated from reading UI file 'ordermanager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERMANAGER_H
#define UI_ORDERMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderManager
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leOrderSearch;
    QPushButton *btnSearch;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QDateEdit *deStartDate;
    QLabel *label_2;
    QDateEdit *deEndDate;
    QLabel *label_3;
    QComboBox *cmbOrderStatus;
    QLabel *label_4;
    QComboBox *cmbRoomType;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnResetFilter;
    QPushButton *btnClose;
    QTableView *tableView;

    void setupUi(QDialog *OrderManager)
    {
        if (OrderManager->objectName().isEmpty())
            OrderManager->setObjectName(QString::fromUtf8("OrderManager"));
        OrderManager->resize(800, 600);
        verticalLayoutWidget = new QWidget(OrderManager);
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

        btnSearch = new QPushButton(verticalLayoutWidget);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));

        horizontalLayout->addWidget(btnSearch);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        deStartDate = new QDateEdit(groupBox);
        deStartDate->setObjectName(QString::fromUtf8("deStartDate"));
        deStartDate->setCalendarPopup(true);

        horizontalLayout_3->addWidget(deStartDate);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        deEndDate = new QDateEdit(groupBox);
        deEndDate->setObjectName(QString::fromUtf8("deEndDate"));
        deEndDate->setCalendarPopup(true);

        horizontalLayout_3->addWidget(deEndDate);


        verticalLayout_2->addLayout(horizontalLayout_3);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        cmbOrderStatus = new QComboBox(groupBox);
        cmbOrderStatus->setObjectName(QString::fromUtf8("cmbOrderStatus"));

        verticalLayout_2->addWidget(cmbOrderStatus);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        cmbRoomType = new QComboBox(groupBox);
        cmbRoomType->setObjectName(QString::fromUtf8("cmbRoomType"));

        verticalLayout_2->addWidget(cmbRoomType);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btnResetFilter = new QPushButton(groupBox);
        btnResetFilter->setObjectName(QString::fromUtf8("btnResetFilter"));

        verticalLayout_3->addWidget(btnResetFilter);

        btnClose = new QPushButton(groupBox);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        verticalLayout_3->addWidget(btnClose);


        verticalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_2->addWidget(groupBox);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);

        horizontalLayout_2->addWidget(tableView);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(OrderManager);

        QMetaObject::connectSlotsByName(OrderManager);
    } // setupUi

    void retranslateUi(QDialog *OrderManager)
    {
        OrderManager->setWindowTitle(QCoreApplication::translate("OrderManager", "\350\256\242\345\215\225\347\256\241\347\220\206", nullptr));
        leOrderSearch->setPlaceholderText(QCoreApplication::translate("OrderManager", "\350\276\223\345\205\245\350\256\242\345\215\225\345\217\267\343\200\201\345\256\242\346\210\267\345\247\223\345\220\215\346\210\226\346\210\277\351\227\264\345\217\267\346\220\234\347\264\242...", nullptr));
        btnSearch->setText(QCoreApplication::translate("OrderManager", "\346\220\234\347\264\242", nullptr));
        groupBox->setTitle(QCoreApplication::translate("OrderManager", "\347\255\233\351\200\211\346\235\241\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("OrderManager", "\345\205\245\344\275\217\346\227\245\346\234\237\350\214\203\345\233\264:", nullptr));
        label_2->setText(QCoreApplication::translate("OrderManager", "\350\207\263", nullptr));
        label_3->setText(QCoreApplication::translate("OrderManager", "\350\256\242\345\215\225\347\212\266\346\200\201:", nullptr));
        label_4->setText(QCoreApplication::translate("OrderManager", "\346\210\277\345\236\213:", nullptr));
        btnResetFilter->setText(QCoreApplication::translate("OrderManager", "\351\207\215\347\275\256\347\255\233\351\200\211", nullptr));
        btnClose->setText(QCoreApplication::translate("OrderManager", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderManager: public Ui_OrderManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERMANAGER_H
