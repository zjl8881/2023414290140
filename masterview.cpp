#include "masterview.h"
#include "ui_masterview.h"
#include "loginview.h"
#include "welcomeview.h"
#include "doctorview.h"
#include "doctoreditview.h"
#include "departmentview.h"
#include "departmenteditview.h"
#include "patientview.h"
#include "patienteditview.h"
#include "medicinesview.h"
#include "medicineseditview.h"
#include "signup.h"
#include "statisticsview.h"  // 确保包含这个头文件
#include "idatabase.h"
#include <QDebug>

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
    , loginView(nullptr)
    , welcomeView(nullptr)
    , doctorView(nullptr)
    , doctorEditView(nullptr)
    , departmentView(nullptr)
    , departmentEditView(nullptr)
    , patientView(nullptr)
    , patientEditView(nullptr)
    , medicinesView(nullptr)
    , medicinesEditView(nullptr)
    , signUpView(nullptr)
    , statisticsView(nullptr)  // 在初始化列表中初始化 statisticsView
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    goLoginView();
    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug() << "goLoginView";
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);

    connect(loginView, SIGNAL(goWelcomeView()), this, SLOT(goWelcomeView()));
    connect(loginView, SIGNAL(goSignUpView()), this, SLOT(goSignUpView()));
}

void MasterView::goWelcomeView()
{
    qDebug() << "welcomeView";
    welcomeView = new WelcomeView(this);
    pushWidgetToStackView(welcomeView);

    connect(welcomeView, SIGNAL(goDoctorView()), this, SLOT(goDoctorView()));
    connect(welcomeView, SIGNAL(goPatientView()), this, SLOT(goPatientView()));
    connect(welcomeView, SIGNAL(goDepartmentView()), this, SLOT(goDepartmentView()));
    connect(welcomeView, SIGNAL(goMedicinesView()), this, SLOT(goMedicinesView()));
    connect(welcomeView, SIGNAL(goStatisticsView()), this, SLOT(goStatisticsView()));
}

void MasterView::goPreviousView()
{
    int index = ui->stackedWidget->currentIndex();
    if (index > 0) {
        ui->stackedWidget->setCurrentIndex(index - 1);
    }
}

void MasterView::goDoctorView()
{
    qDebug() << "goDoctorView";
    doctorView = new DoctorView(this);
    pushWidgetToStackView(doctorView);

    connect(doctorView, SIGNAL(goDoctorEditView(int)), this, SLOT(goDoctorEditView(int)));
}

void MasterView::goDoctorEditView(int rowNo)
{
    qDebug() << "goDoctorEditView" << rowNo;
    doctorEditView = new DoctorEditView(rowNo, this);
    pushWidgetToStackView(doctorEditView);
}

void MasterView::goStatisticsView()
{
    qDebug() << "goStatisticsView";
    statisticsView = new StatisticsView(this);  // 现在 statisticsView 已经声明
    pushWidgetToStackView(statisticsView);
}

void MasterView::goDepartmentView()
{
    qDebug() << "goDepartmentView";
    departmentView = new DepartmentView(this);
    pushWidgetToStackView(departmentView);

    connect(departmentView, SIGNAL(goDepartmentEditView(int)), this, SLOT(goDepartmentEditView(int)));
}

void MasterView::goDepartmentEditView(int rowNo)
{
    qDebug() << "goDepartmentEditView" << rowNo;
    departmentEditView = new DepartmentEditView(rowNo, this);
    pushWidgetToStackView(departmentEditView);
}

void MasterView::goPatientView()
{
    qDebug() << "goPatientView";
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);

    connect(patientView, SIGNAL(goPatientEditView(int)), this, SLOT(goPatientEditView(int)));
}

void MasterView::goPatientEditView(int rowNo)
{
    qDebug() << "goPatientEditView" << rowNo;
    patientEditView = new PatientEditView(rowNo, this);
    pushWidgetToStackView(patientEditView);
}

void MasterView::goMedicinesView()
{
    qDebug() << "goMedicinesView";
    medicinesView = new MedicinesView(this);
    pushWidgetToStackView(medicinesView);

    connect(medicinesView, SIGNAL(goMedicinesEditView(int)), this, SLOT(goMedicinesEditView(int)));
}

void MasterView::goMedicinesEditView(int rowNo)
{
    qDebug() << "goMedicinesEditView" << rowNo;
    medicinesEditView = new MedicinesEditView(rowNo, this);
    pushWidgetToStackView(medicinesEditView);
}

void MasterView::goSignUpView()
{
    qDebug() << "goSignUpView";
    signUpView = new SignUp(this);
    pushWidgetToStackView(signUpView);

    connect(signUpView, SIGNAL(goLoginView()), this, SLOT(goLoginView()));
}

void MasterView::on_btBack_clicked()
{
    goPreviousView();
}

void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    if (ui->stackedWidget->currentIndex() > 0) {
        ui->btBack->setVisible(true);
    } else {
        ui->btBack->setVisible(false);
    }
}

void MasterView::on_btLogout_clicked()
{
    goLoginView();
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    int index = ui->stackedWidget->addWidget(widget);
    ui->stackedWidget->setCurrentIndex(index);
}
