/********************************************************************************
** Form generated from reading UI file 'roomtypemanager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMTYPEMANAGER_H
#define UI_ROOMTYPEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoomTypeManager
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leSearch;
    QPushButton *btnSearch;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leName;
    QLabel *label_2;
    QDoubleSpinBox *dsbArea;
    QLabel *label_3;
    QLineEdit *leBedType;
    QLabel *label_4;
    QDoubleSpinBox *dsbPricePerDay;
    QLabel *label_5;
    QTextEdit *teFacilities;
    QLabel *label_6;
    QSpinBox *sbTotalRooms;
    QLabel *label_7;
    QSpinBox *sbAvailableRooms;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;
    QTableView *tableView;

    void setupUi(QDialog *RoomTypeManager)
    {
        if (RoomTypeManager->objectName().isEmpty())
            RoomTypeManager->setObjectName(QString::fromUtf8("RoomTypeManager"));
        RoomTypeManager->resize(800, 600);
        verticalLayoutWidget = new QWidget(RoomTypeManager);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 780, 580));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leSearch = new QLineEdit(verticalLayoutWidget);
        leSearch->setObjectName(QString::fromUtf8("leSearch"));

        horizontalLayout->addWidget(leSearch);

        btnSearch = new QPushButton(verticalLayoutWidget);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));

        horizontalLayout->addWidget(btnSearch);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leName = new QLineEdit(groupBox);
        leName->setObjectName(QString::fromUtf8("leName"));

        gridLayout->addWidget(leName, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        dsbArea = new QDoubleSpinBox(groupBox);
        dsbArea->setObjectName(QString::fromUtf8("dsbArea"));
        dsbArea->setDecimals(1);
        dsbArea->setMinimum(10.000000000000000);
        dsbArea->setMaximum(200.000000000000000);

        gridLayout->addWidget(dsbArea, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        leBedType = new QLineEdit(groupBox);
        leBedType->setObjectName(QString::fromUtf8("leBedType"));

        gridLayout->addWidget(leBedType, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        dsbPricePerDay = new QDoubleSpinBox(groupBox);
        dsbPricePerDay->setObjectName(QString::fromUtf8("dsbPricePerDay"));
        dsbPricePerDay->setDecimals(0);
        dsbPricePerDay->setMinimum(50.000000000000000);
        dsbPricePerDay->setMaximum(2000.000000000000000);

        gridLayout->addWidget(dsbPricePerDay, 1, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        teFacilities = new QTextEdit(groupBox);
        teFacilities->setObjectName(QString::fromUtf8("teFacilities"));

        gridLayout->addWidget(teFacilities, 2, 1, 1, 3);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        sbTotalRooms = new QSpinBox(groupBox);
        sbTotalRooms->setObjectName(QString::fromUtf8("sbTotalRooms"));
        sbTotalRooms->setMinimum(1);
        sbTotalRooms->setMaximum(100);

        gridLayout->addWidget(sbTotalRooms, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 2, 1, 1);

        sbAvailableRooms = new QSpinBox(groupBox);
        sbAvailableRooms->setObjectName(QString::fromUtf8("sbAvailableRooms"));
        sbAvailableRooms->setMinimum(0);
        sbAvailableRooms->setMaximum(100);

        gridLayout->addWidget(sbAvailableRooms, 3, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnAdd = new QPushButton(verticalLayoutWidget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        horizontalLayout_2->addWidget(btnAdd);

        btnEdit = new QPushButton(verticalLayoutWidget);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));

        horizontalLayout_2->addWidget(btnEdit);

        btnDelete = new QPushButton(verticalLayoutWidget);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout_2->addWidget(btnDelete);

        btnRefresh = new QPushButton(verticalLayoutWidget);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));

        horizontalLayout_2->addWidget(btnRefresh);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(verticalLayoutWidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout_2);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);

        verticalLayout->addWidget(tableView);


        retranslateUi(RoomTypeManager);

        QMetaObject::connectSlotsByName(RoomTypeManager);
    } // setupUi

    void retranslateUi(QDialog *RoomTypeManager)
    {
        RoomTypeManager->setWindowTitle(QCoreApplication::translate("RoomTypeManager", "\346\210\277\345\236\213\347\256\241\347\220\206", nullptr));
        leSearch->setPlaceholderText(QCoreApplication::translate("RoomTypeManager", "\350\276\223\345\205\245\346\210\277\345\236\213\345\220\215\347\247\260\346\220\234\347\264\242...", nullptr));
        btnSearch->setText(QCoreApplication::translate("RoomTypeManager", "\346\220\234\347\264\242", nullptr));
        groupBox->setTitle(QCoreApplication::translate("RoomTypeManager", "\346\210\277\345\236\213\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("RoomTypeManager", "\346\210\277\345\236\213\345\220\215\347\247\260:", nullptr));
        label_2->setText(QCoreApplication::translate("RoomTypeManager", "\351\235\242\347\247\257(m\302\262):", nullptr));
        label_3->setText(QCoreApplication::translate("RoomTypeManager", "\345\272\212\345\236\213:", nullptr));
        label_4->setText(QCoreApplication::translate("RoomTypeManager", "\345\215\225\346\227\245\345\256\232\344\273\267(\345\205\203):", nullptr));
        label_5->setText(QCoreApplication::translate("RoomTypeManager", "\351\205\215\345\245\227\350\256\276\346\226\275:", nullptr));
        label_6->setText(QCoreApplication::translate("RoomTypeManager", "\346\210\277\351\227\264\346\200\273\346\225\260:", nullptr));
        label_7->setText(QCoreApplication::translate("RoomTypeManager", "\345\211\251\344\275\231\345\217\257\350\256\242\346\225\260:", nullptr));
        btnAdd->setText(QCoreApplication::translate("RoomTypeManager", "\346\267\273\345\212\240", nullptr));
        btnEdit->setText(QCoreApplication::translate("RoomTypeManager", "\347\274\226\350\276\221", nullptr));
        btnDelete->setText(QCoreApplication::translate("RoomTypeManager", "\345\210\240\351\231\244", nullptr));
        btnRefresh->setText(QCoreApplication::translate("RoomTypeManager", "\345\210\267\346\226\260", nullptr));
        btnClose->setText(QCoreApplication::translate("RoomTypeManager", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoomTypeManager: public Ui_RoomTypeManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMTYPEMANAGER_H
