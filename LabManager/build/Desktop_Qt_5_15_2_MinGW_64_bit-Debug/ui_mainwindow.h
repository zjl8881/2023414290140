/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnReserve;
    QPushButton *btnAddDevice;
    QPushButton *btnReturn;
    QPushButton *btnReportFault;
    QPushButton *btnStats;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnRefresh = new QPushButton(centralwidget);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));

        horizontalLayout->addWidget(btnRefresh);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnReserve = new QPushButton(centralwidget);
        btnReserve->setObjectName(QString::fromUtf8("btnReserve"));

        horizontalLayout->addWidget(btnReserve);

        btnAddDevice = new QPushButton(centralwidget);
        btnAddDevice->setObjectName(QString::fromUtf8("btnAddDevice"));

        horizontalLayout->addWidget(btnAddDevice);

        btnReturn = new QPushButton(centralwidget);
        btnReturn->setObjectName(QString::fromUtf8("btnReturn"));

        horizontalLayout->addWidget(btnReturn);

        btnReportFault = new QPushButton(centralwidget);
        btnReportFault->setObjectName(QString::fromUtf8("btnReportFault"));

        horizontalLayout->addWidget(btnReportFault);

        btnStats = new QPushButton(centralwidget);
        btnStats->setObjectName(QString::fromUtf8("btnStats"));

        horizontalLayout->addWidget(btnStats);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\256\236\351\252\214\345\256\244\350\256\276\345\244\207\344\270\216\351\242\204\347\272\246\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\346\211\213\345\212\250\345\210\267\346\226\260", nullptr));
        btnReserve->setText(QCoreApplication::translate("MainWindow", "\347\224\263\350\257\267\351\242\204\347\272\246", nullptr));
        btnAddDevice->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\350\256\276\345\244\207", nullptr));
        btnReturn->setText(QCoreApplication::translate("MainWindow", "\345\275\222\350\277\230\350\256\276\345\244\207", nullptr));
        btnReportFault->setText(QCoreApplication::translate("MainWindow", "\346\212\245\344\277\256", nullptr));
        btnStats->setText(QCoreApplication::translate("MainWindow", "\345\220\216\345\217\260\345\272\223\345\255\230\347\273\237\350\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
