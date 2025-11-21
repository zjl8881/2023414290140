/********************************************************************************
** Form generated from reading UI file 'searchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *searchText;
    QGridLayout *gridLayout_2;
    QCheckBox *cbCaseSensetive;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbUp;
    QRadioButton *rbDown;
    QVBoxLayout *verticalLayout;
    QPushButton *btFindNext;
    QSpacerItem *verticalSpacer;
    QPushButton *btCancel;

    void setupUi(QDialog *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName(QString::fromUtf8("SearchDialog"));
        SearchDialog->resize(433, 126);
        horizontalLayout_2 = new QHBoxLayout(SearchDialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(SearchDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        searchText = new QLineEdit(SearchDialog);
        searchText->setObjectName(QString::fromUtf8("searchText"));

        gridLayout->addWidget(searchText, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cbCaseSensetive = new QCheckBox(SearchDialog);
        cbCaseSensetive->setObjectName(QString::fromUtf8("cbCaseSensetive"));

        gridLayout_2->addWidget(cbCaseSensetive, 0, 0, 1, 1);

        groupBox = new QGroupBox(SearchDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rbUp = new QRadioButton(groupBox);
        rbUp->setObjectName(QString::fromUtf8("rbUp"));

        horizontalLayout->addWidget(rbUp);

        rbDown = new QRadioButton(groupBox);
        rbDown->setObjectName(QString::fromUtf8("rbDown"));

        horizontalLayout->addWidget(rbDown);


        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btFindNext = new QPushButton(SearchDialog);
        btFindNext->setObjectName(QString::fromUtf8("btFindNext"));

        verticalLayout->addWidget(btFindNext);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        btCancel = new QPushButton(SearchDialog);
        btCancel->setObjectName(QString::fromUtf8("btCancel"));

        verticalLayout->addWidget(btCancel);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(SearchDialog);

        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
        SearchDialog->setWindowTitle(QCoreApplication::translate("SearchDialog", "\346\237\245\346\211\276", nullptr));
        label->setText(QCoreApplication::translate("SearchDialog", "\346\237\245\346\211\276\347\233\256\346\240\207\357\274\232", nullptr));
        cbCaseSensetive->setText(QCoreApplication::translate("SearchDialog", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SearchDialog", "\346\226\271\345\220\221", nullptr));
        rbUp->setText(QCoreApplication::translate("SearchDialog", "\345\220\221\344\270\212(&U)", nullptr));
        rbDown->setText(QCoreApplication::translate("SearchDialog", "\345\220\221\344\270\213(&D)", nullptr));
        btFindNext->setText(QCoreApplication::translate("SearchDialog", "\346\237\245\346\211\276\344\270\213\344\270\200\344\270\252(&F)", nullptr));
        btCancel->setText(QCoreApplication::translate("SearchDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
