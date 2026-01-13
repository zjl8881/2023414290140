/********************************************************************************
** Form generated from reading UI file 'roomstatusmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMSTATUSMANAGER_H
#define UI_ROOMSTATUSMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoomStatusManager
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cmbStatus;
    QLabel *label_2;
    QComboBox *cmbFloor;
    QLabel *label_3;
    QComboBox *cmbRoomType;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnRefresh;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;
    QLabel *labelStatus;

    void setupUi(QDialog *RoomStatusManager)
    {
        if (RoomStatusManager->objectName().isEmpty())
            RoomStatusManager->setObjectName(QString::fromUtf8("RoomStatusManager"));
        RoomStatusManager->resize(800, 600);
        verticalLayoutWidget = new QWidget(RoomStatusManager);
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

        cmbStatus = new QComboBox(groupBox);
        cmbStatus->setObjectName(QString::fromUtf8("cmbStatus"));

        gridLayout->addWidget(cmbStatus, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        cmbFloor = new QComboBox(groupBox);
        cmbFloor->setObjectName(QString::fromUtf8("cmbFloor"));

        gridLayout->addWidget(cmbFloor, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        cmbRoomType = new QComboBox(groupBox);
        cmbRoomType->setObjectName(QString::fromUtf8("cmbRoomType"));

        gridLayout->addWidget(cmbRoomType, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnRefresh = new QPushButton(groupBox);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));

        horizontalLayout->addWidget(btnRefresh);

        btnClose = new QPushButton(groupBox);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout->addWidget(btnClose);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 1, 2, 1, 2);


        verticalLayout->addWidget(groupBox);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);

        verticalLayout->addWidget(tableView);

        labelStatus = new QLabel(verticalLayoutWidget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setAlignment(Qt::AlignCenter);
        labelStatus->setStyleSheet(QString::fromUtf8("color: #666666;"));

        verticalLayout->addWidget(labelStatus);


        retranslateUi(RoomStatusManager);

        QMetaObject::connectSlotsByName(RoomStatusManager);
    } // setupUi

    void retranslateUi(QDialog *RoomStatusManager)
    {
        RoomStatusManager->setWindowTitle(QCoreApplication::translate("RoomStatusManager", "\346\210\277\351\227\264\347\212\266\346\200\201\347\256\241\347\220\206", nullptr));
        groupBox->setTitle(QCoreApplication::translate("RoomStatusManager", "\347\255\233\351\200\211\346\235\241\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("RoomStatusManager", "\346\210\277\351\227\264\347\212\266\346\200\201:", nullptr));
        label_2->setText(QCoreApplication::translate("RoomStatusManager", "\346\245\274\345\261\202:", nullptr));
        label_3->setText(QCoreApplication::translate("RoomStatusManager", "\346\210\277\345\236\213:", nullptr));
        btnRefresh->setText(QCoreApplication::translate("RoomStatusManager", "\345\210\267\346\226\260\346\225\260\346\215\256", nullptr));
        btnClose->setText(QCoreApplication::translate("RoomStatusManager", "\345\205\263\351\227\255", nullptr));
        labelStatus->setText(QCoreApplication::translate("RoomStatusManager", "\346\210\277\351\227\264\347\212\266\346\200\201\345\256\236\346\227\266\346\233\264\346\226\260\344\270\255\357\274\214\346\257\21730\347\247\222\350\207\252\345\212\250\345\210\267\346\226\260\344\270\200\346\254\241...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoomStatusManager: public Ui_RoomStatusManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMSTATUSMANAGER_H
