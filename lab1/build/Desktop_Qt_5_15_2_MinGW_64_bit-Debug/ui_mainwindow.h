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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *btnDel;
    QPushButton *btnReciprocal;
    QPushButton *btnNum7;
    QPushButton *btnPercent;
    QPushButton *btnClear;
    QPushButton *btnNum8;
    QPushButton *btnSquare;
    QPushButton *btnDiv;
    QPushButton *btnMul;
    QPushButton *btnNum9;
    QPushButton *btnCE;
    QPushButton *btnNum4;
    QPushButton *btnNum6;
    QPushButton *btnSub;
    QPushButton *btnSqrt;
    QLineEdit *display;
    QPushButton *btnDot;
    QPushButton *btnAdd;
    QPushButton *btnSign;
    QPushButton *btnNum3;
    QPushButton *btnNum0;
    QPushButton *btnNum2;
    QPushButton *btnNum1;
    QPushButton *btnNum5;
    QPushButton *btnEq;
    QWidget *widget;
    QLabel *labCurrentNum;
    QLabel *labCurrentOp;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(732, 610);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setToolTipDuration(0);
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:rgb(0, 0, 0);\n"
"font-size:36pt;\n"
"color:white;\n"
"border-radius:2px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color:lightgreen;\n"
"color:balck;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"background-color:red;\n"
"color:balck;\n"
"} \n"
"\n"
"QLineEdit{\n"
"font-size:48pt;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setFocusPolicy(Qt::NoFocus);
        centralwidget->setToolTipDuration(0);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        btnDel = new QPushButton(centralwidget);
        btnDel->setObjectName(QString::fromUtf8("btnDel"));
        sizePolicy.setHeightForWidth(btnDel->sizePolicy().hasHeightForWidth());
        btnDel->setSizePolicy(sizePolicy);
        btnDel->setToolTipDuration(0);
        btnDel->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnDel, 2, 3, 1, 1);

        btnReciprocal = new QPushButton(centralwidget);
        btnReciprocal->setObjectName(QString::fromUtf8("btnReciprocal"));
        sizePolicy.setHeightForWidth(btnReciprocal->sizePolicy().hasHeightForWidth());
        btnReciprocal->setSizePolicy(sizePolicy);
        btnReciprocal->setToolTipDuration(0);
        btnReciprocal->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnReciprocal, 4, 0, 1, 1);

        btnNum7 = new QPushButton(centralwidget);
        btnNum7->setObjectName(QString::fromUtf8("btnNum7"));
        sizePolicy.setHeightForWidth(btnNum7->sizePolicy().hasHeightForWidth());
        btnNum7->setSizePolicy(sizePolicy);
        btnNum7->setToolTipDuration(0);
        btnNum7->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum7, 5, 0, 1, 1);

        btnPercent = new QPushButton(centralwidget);
        btnPercent->setObjectName(QString::fromUtf8("btnPercent"));
        sizePolicy.setHeightForWidth(btnPercent->sizePolicy().hasHeightForWidth());
        btnPercent->setSizePolicy(sizePolicy);
        btnPercent->setToolTipDuration(0);
        btnPercent->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnPercent, 2, 0, 1, 1);

        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));
        sizePolicy.setHeightForWidth(btnClear->sizePolicy().hasHeightForWidth());
        btnClear->setSizePolicy(sizePolicy);
        btnClear->setToolTipDuration(0);
        btnClear->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnClear, 2, 2, 1, 1);

        btnNum8 = new QPushButton(centralwidget);
        btnNum8->setObjectName(QString::fromUtf8("btnNum8"));
        sizePolicy.setHeightForWidth(btnNum8->sizePolicy().hasHeightForWidth());
        btnNum8->setSizePolicy(sizePolicy);
        btnNum8->setToolTipDuration(0);
        btnNum8->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum8, 5, 1, 1, 1);

        btnSquare = new QPushButton(centralwidget);
        btnSquare->setObjectName(QString::fromUtf8("btnSquare"));
        sizePolicy.setHeightForWidth(btnSquare->sizePolicy().hasHeightForWidth());
        btnSquare->setSizePolicy(sizePolicy);
        btnSquare->setToolTipDuration(0);
        btnSquare->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnSquare, 4, 1, 1, 1);

        btnDiv = new QPushButton(centralwidget);
        btnDiv->setObjectName(QString::fromUtf8("btnDiv"));
        sizePolicy.setHeightForWidth(btnDiv->sizePolicy().hasHeightForWidth());
        btnDiv->setSizePolicy(sizePolicy);
        btnDiv->setToolTipDuration(0);
        btnDiv->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnDiv, 4, 3, 1, 1);

        btnMul = new QPushButton(centralwidget);
        btnMul->setObjectName(QString::fromUtf8("btnMul"));
        sizePolicy.setHeightForWidth(btnMul->sizePolicy().hasHeightForWidth());
        btnMul->setSizePolicy(sizePolicy);
        btnMul->setToolTipDuration(0);
        btnMul->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnMul, 5, 3, 1, 1);

        btnNum9 = new QPushButton(centralwidget);
        btnNum9->setObjectName(QString::fromUtf8("btnNum9"));
        sizePolicy.setHeightForWidth(btnNum9->sizePolicy().hasHeightForWidth());
        btnNum9->setSizePolicy(sizePolicy);
        btnNum9->setToolTipDuration(0);
        btnNum9->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum9, 5, 2, 1, 1);

        btnCE = new QPushButton(centralwidget);
        btnCE->setObjectName(QString::fromUtf8("btnCE"));
        sizePolicy.setHeightForWidth(btnCE->sizePolicy().hasHeightForWidth());
        btnCE->setSizePolicy(sizePolicy);
        btnCE->setToolTipDuration(0);
        btnCE->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnCE, 2, 1, 1, 1);

        btnNum4 = new QPushButton(centralwidget);
        btnNum4->setObjectName(QString::fromUtf8("btnNum4"));
        sizePolicy.setHeightForWidth(btnNum4->sizePolicy().hasHeightForWidth());
        btnNum4->setSizePolicy(sizePolicy);
        btnNum4->setToolTipDuration(0);
        btnNum4->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum4, 6, 0, 1, 1);

        btnNum6 = new QPushButton(centralwidget);
        btnNum6->setObjectName(QString::fromUtf8("btnNum6"));
        sizePolicy.setHeightForWidth(btnNum6->sizePolicy().hasHeightForWidth());
        btnNum6->setSizePolicy(sizePolicy);
        btnNum6->setToolTipDuration(0);
        btnNum6->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum6, 6, 2, 1, 1);

        btnSub = new QPushButton(centralwidget);
        btnSub->setObjectName(QString::fromUtf8("btnSub"));
        sizePolicy.setHeightForWidth(btnSub->sizePolicy().hasHeightForWidth());
        btnSub->setSizePolicy(sizePolicy);
        btnSub->setToolTipDuration(0);
        btnSub->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnSub, 6, 3, 1, 1);

        btnSqrt = new QPushButton(centralwidget);
        btnSqrt->setObjectName(QString::fromUtf8("btnSqrt"));
        sizePolicy.setHeightForWidth(btnSqrt->sizePolicy().hasHeightForWidth());
        btnSqrt->setSizePolicy(sizePolicy);
        btnSqrt->setToolTipDuration(0);
        btnSqrt->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnSqrt, 4, 2, 1, 1);

        display = new QLineEdit(centralwidget);
        display->setObjectName(QString::fromUtf8("display"));
        sizePolicy.setHeightForWidth(display->sizePolicy().hasHeightForWidth());
        display->setSizePolicy(sizePolicy);
        display->setToolTipDuration(0);
        display->setLayoutDirection(Qt::LeftToRight);
        display->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(display, 1, 0, 1, 4);

        btnDot = new QPushButton(centralwidget);
        btnDot->setObjectName(QString::fromUtf8("btnDot"));
        sizePolicy.setHeightForWidth(btnDot->sizePolicy().hasHeightForWidth());
        btnDot->setSizePolicy(sizePolicy);
        btnDot->setToolTipDuration(0);
        btnDot->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnDot, 9, 2, 1, 1);

        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        sizePolicy.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy);
        btnAdd->setToolTipDuration(0);
        btnAdd->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnAdd, 8, 3, 1, 1);

        btnSign = new QPushButton(centralwidget);
        btnSign->setObjectName(QString::fromUtf8("btnSign"));
        sizePolicy.setHeightForWidth(btnSign->sizePolicy().hasHeightForWidth());
        btnSign->setSizePolicy(sizePolicy);
        btnSign->setToolTipDuration(0);
        btnSign->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnSign, 9, 0, 1, 1);

        btnNum3 = new QPushButton(centralwidget);
        btnNum3->setObjectName(QString::fromUtf8("btnNum3"));
        sizePolicy.setHeightForWidth(btnNum3->sizePolicy().hasHeightForWidth());
        btnNum3->setSizePolicy(sizePolicy);
        btnNum3->setToolTipDuration(0);
        btnNum3->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum3, 8, 2, 1, 1);

        btnNum0 = new QPushButton(centralwidget);
        btnNum0->setObjectName(QString::fromUtf8("btnNum0"));
        sizePolicy.setHeightForWidth(btnNum0->sizePolicy().hasHeightForWidth());
        btnNum0->setSizePolicy(sizePolicy);
        btnNum0->setToolTipDuration(0);
        btnNum0->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum0, 9, 1, 1, 1);

        btnNum2 = new QPushButton(centralwidget);
        btnNum2->setObjectName(QString::fromUtf8("btnNum2"));
        sizePolicy.setHeightForWidth(btnNum2->sizePolicy().hasHeightForWidth());
        btnNum2->setSizePolicy(sizePolicy);
        btnNum2->setToolTipDuration(0);
        btnNum2->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum2, 8, 1, 1, 1);

        btnNum1 = new QPushButton(centralwidget);
        btnNum1->setObjectName(QString::fromUtf8("btnNum1"));
        sizePolicy.setHeightForWidth(btnNum1->sizePolicy().hasHeightForWidth());
        btnNum1->setSizePolicy(sizePolicy);
        btnNum1->setToolTipDuration(0);
        btnNum1->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum1, 8, 0, 1, 1);

        btnNum5 = new QPushButton(centralwidget);
        btnNum5->setObjectName(QString::fromUtf8("btnNum5"));
        sizePolicy.setHeightForWidth(btnNum5->sizePolicy().hasHeightForWidth());
        btnNum5->setSizePolicy(sizePolicy);
        btnNum5->setToolTipDuration(0);
        btnNum5->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnNum5, 6, 1, 1, 1);

        btnEq = new QPushButton(centralwidget);
        btnEq->setObjectName(QString::fromUtf8("btnEq"));
        sizePolicy.setHeightForWidth(btnEq->sizePolicy().hasHeightForWidth());
        btnEq->setSizePolicy(sizePolicy);
        btnEq->setToolTipDuration(0);
        btnEq->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnEq, 9, 3, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        labCurrentNum = new QLabel(widget);
        labCurrentNum->setObjectName(QString::fromUtf8("labCurrentNum"));
        labCurrentNum->setGeometry(QRect(0, 0, 361, 21));
        labCurrentOp = new QLabel(widget);
        labCurrentOp->setObjectName(QString::fromUtf8("labCurrentOp"));
        labCurrentOp->setGeometry(QRect(360, 1, 371, 20));

        gridLayout->addWidget(widget, 10, 0, 1, 4);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 732, 25));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(btnSquare, btnDel);
        QWidget::setTabOrder(btnDel, btnNum4);
        QWidget::setTabOrder(btnNum4, btnNum7);
        QWidget::setTabOrder(btnNum7, btnAdd);
        QWidget::setTabOrder(btnAdd, btnNum3);
        QWidget::setTabOrder(btnNum3, btnNum8);
        QWidget::setTabOrder(btnNum8, btnClear);
        QWidget::setTabOrder(btnClear, btnNum9);
        QWidget::setTabOrder(btnNum9, btnNum2);
        QWidget::setTabOrder(btnNum2, btnNum5);
        QWidget::setTabOrder(btnNum5, btnSub);
        QWidget::setTabOrder(btnSub, btnCE);
        QWidget::setTabOrder(btnCE, btnNum1);
        QWidget::setTabOrder(btnNum1, btnDiv);
        QWidget::setTabOrder(btnDiv, btnPercent);
        QWidget::setTabOrder(btnPercent, btnSqrt);
        QWidget::setTabOrder(btnSqrt, btnMul);
        QWidget::setTabOrder(btnMul, btnReciprocal);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnDel->setText(QCoreApplication::translate("MainWindow", "DEL", nullptr));
        btnReciprocal->setText(QCoreApplication::translate("MainWindow", "1/x", nullptr));
        btnNum7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btnPercent->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        btnNum8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btnSquare->setText(QCoreApplication::translate("MainWindow", "x^2", nullptr));
        btnDiv->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btnMul->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        btnNum9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btnCE->setText(QCoreApplication::translate("MainWindow", "CE", nullptr));
        btnNum4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btnNum6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btnSub->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnSqrt->setText(QCoreApplication::translate("MainWindow", "\342\210\232", nullptr));
        display->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnDot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnSign->setText(QCoreApplication::translate("MainWindow", "+/-", nullptr));
        btnNum3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btnNum0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnNum2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btnNum1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnNum5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btnEq->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        labCurrentNum->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\347\273\223\346\236\234: 0", nullptr));
        labCurrentOp->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\346\223\215\344\275\234\347\254\246: \346\227\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
