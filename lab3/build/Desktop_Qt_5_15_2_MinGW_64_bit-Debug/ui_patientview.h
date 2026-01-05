/********************************************************************************
** Form generated from reading UI file 'patientview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTVIEW_H
#define UI_PATIENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientView
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtSearch;
    QPushButton *btSearch;
    QPushButton *btAdd;
    QPushButton *btDelete;
    QPushButton *btEdit;
    QTableView *tableView;

    void setupUi(QWidget *PatientView)
    {
        if (PatientView->objectName().isEmpty())
            PatientView->setObjectName(QString::fromUtf8("PatientView"));
        PatientView->resize(689, 556);
        verticalLayout = new QVBoxLayout(PatientView);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtSearch = new QLineEdit(PatientView);
        txtSearch->setObjectName(QString::fromUtf8("txtSearch"));

        horizontalLayout->addWidget(txtSearch);

        btSearch = new QPushButton(PatientView);
        btSearch->setObjectName(QString::fromUtf8("btSearch"));

        horizontalLayout->addWidget(btSearch);

        btAdd = new QPushButton(PatientView);
        btAdd->setObjectName(QString::fromUtf8("btAdd"));

        horizontalLayout->addWidget(btAdd);

        btDelete = new QPushButton(PatientView);
        btDelete->setObjectName(QString::fromUtf8("btDelete"));

        horizontalLayout->addWidget(btDelete);

        btEdit = new QPushButton(PatientView);
        btEdit->setObjectName(QString::fromUtf8("btEdit"));

        horizontalLayout->addWidget(btEdit);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(PatientView);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(PatientView);

        QMetaObject::connectSlotsByName(PatientView);
    } // setupUi

    void retranslateUi(QWidget *PatientView)
    {
        PatientView->setWindowTitle(QCoreApplication::translate("PatientView", "\346\202\243\350\200\205\347\256\241\347\220\206", nullptr));
        txtSearch->setPlaceholderText(QCoreApplication::translate("PatientView", "\350\257\267\350\276\223\345\205\245\345\247\223\345\220\215\350\277\233\350\241\214\346\237\245\346\211\276", nullptr));
        btSearch->setText(QCoreApplication::translate("PatientView", "\346\237\245\346\211\276", nullptr));
        btAdd->setText(QCoreApplication::translate("PatientView", "\346\267\273\345\212\240", nullptr));
        btDelete->setText(QCoreApplication::translate("PatientView", "\345\210\240\351\231\244", nullptr));
        btEdit->setText(QCoreApplication::translate("PatientView", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientView: public Ui_PatientView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTVIEW_H
