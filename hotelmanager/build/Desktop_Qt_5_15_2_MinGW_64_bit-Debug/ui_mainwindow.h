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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRoomTypeManager;
    QAction *actionCheckIn;
    QAction *actionCheckOut;
    QAction *actionOrderManager;
    QAction *actionRoomStatus;
    QAction *actionExit;
    QAction *btnRoomType;
    QAction *btnCheckIn;
    QAction *btnCheckOut;
    QAction *btnOrder;
    QAction *btnRoomStatus;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionRoomTypeManager = new QAction(MainWindow);
        actionRoomTypeManager->setObjectName(QString::fromUtf8("actionRoomTypeManager"));
        actionCheckIn = new QAction(MainWindow);
        actionCheckIn->setObjectName(QString::fromUtf8("actionCheckIn"));
        actionCheckOut = new QAction(MainWindow);
        actionCheckOut->setObjectName(QString::fromUtf8("actionCheckOut"));
        actionOrderManager = new QAction(MainWindow);
        actionOrderManager->setObjectName(QString::fromUtf8("actionOrderManager"));
        actionRoomStatus = new QAction(MainWindow);
        actionRoomStatus->setObjectName(QString::fromUtf8("actionRoomStatus"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        btnRoomType = new QAction(MainWindow);
        btnRoomType->setObjectName(QString::fromUtf8("btnRoomType"));
        btnCheckIn = new QAction(MainWindow);
        btnCheckIn->setObjectName(QString::fromUtf8("btnCheckIn"));
        btnCheckOut = new QAction(MainWindow);
        btnCheckOut->setObjectName(QString::fromUtf8("btnCheckOut"));
        btnOrder = new QAction(MainWindow);
        btnOrder->setObjectName(QString::fromUtf8("btnOrder"));
        btnRoomStatus = new QAction(MainWindow);
        btnRoomStatus->setObjectName(QString::fromUtf8("btnRoomStatus"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addAction(actionExit);
        menu_2->addAction(actionRoomTypeManager);
        menu_2->addAction(actionRoomStatus);
        menu_3->addAction(actionCheckIn);
        menu_4->addAction(actionCheckOut);
        menu_5->addAction(actionOrderManager);
        mainToolBar->addAction(btnRoomType);
        mainToolBar->addAction(btnCheckIn);
        mainToolBar->addAction(btnCheckOut);
        mainToolBar->addAction(btnOrder);
        mainToolBar->addAction(btnRoomStatus);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\351\205\222\345\272\227\345\205\245\344\275\217\344\270\216\351\242\204\350\256\242\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        actionRoomTypeManager->setText(QCoreApplication::translate("MainWindow", "\346\210\277\345\236\213\347\256\241\347\220\206", nullptr));
        actionCheckIn->setText(QCoreApplication::translate("MainWindow", "\345\205\245\344\275\217\347\231\273\350\256\260", nullptr));
        actionCheckOut->setText(QCoreApplication::translate("MainWindow", "\351\200\200\346\210\277\347\273\223\347\256\227", nullptr));
        actionOrderManager->setText(QCoreApplication::translate("MainWindow", "\350\256\242\345\215\225\347\256\241\347\220\206", nullptr));
        actionRoomStatus->setText(QCoreApplication::translate("MainWindow", "\346\210\277\351\227\264\347\212\266\346\200\201", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        btnRoomType->setText(QCoreApplication::translate("MainWindow", "\346\210\277\345\236\213\347\256\241\347\220\206", nullptr));
        btnRoomType->setIconText(QCoreApplication::translate("MainWindow", "\346\210\277\345\236\213\347\256\241\347\220\206", nullptr));
        btnCheckIn->setText(QCoreApplication::translate("MainWindow", "\345\205\245\344\275\217\347\231\273\350\256\260", nullptr));
        btnCheckIn->setIconText(QCoreApplication::translate("MainWindow", "\345\205\245\344\275\217\347\231\273\350\256\260", nullptr));
        btnCheckOut->setText(QCoreApplication::translate("MainWindow", "\351\200\200\346\210\277\347\273\223\347\256\227", nullptr));
        btnCheckOut->setIconText(QCoreApplication::translate("MainWindow", "\351\200\200\346\210\277\347\273\223\347\256\227", nullptr));
        btnOrder->setText(QCoreApplication::translate("MainWindow", "\350\256\242\345\215\225\347\256\241\347\220\206", nullptr));
        btnOrder->setIconText(QCoreApplication::translate("MainWindow", "\350\256\242\345\215\225\347\256\241\347\220\206", nullptr));
        btnRoomStatus->setText(QCoreApplication::translate("MainWindow", "\346\210\277\351\227\264\347\212\266\346\200\201", nullptr));
        btnRoomStatus->setIconText(QCoreApplication::translate("MainWindow", "\346\210\277\351\227\264\347\212\266\346\200\201", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\205\222\345\272\227\345\205\245\344\275\217\344\270\216\351\242\204\350\256\242\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\344\275\277\347\224\250\351\205\222\345\272\227\345\205\245\344\275\217\344\270\216\351\242\204\350\256\242\347\256\241\347\220\206\347\263\273\347\273\237\357\274\214\350\257\267\344\273\216\344\270\212\346\226\271\350\217\234\345\215\225\346\210\226\345\267\245\345\205\267\346\240\217\351\200\211\346\213\251\345\212\237\350\203\275", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\347\256\241\347\220\206", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\345\256\242\346\210\277\347\256\241\347\220\206", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\205\245\344\275\217\347\256\241\347\220\206", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\351\200\200\346\210\277\347\256\241\347\220\206", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\350\256\242\345\215\225\347\256\241\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
