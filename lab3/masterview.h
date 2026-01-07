#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "departmentview.h"
#include "doctorview.h"
#include "patientview.h"
#include "patienteditview.h"
#include "welcomeview.h"
#include "departmenteditview.h"
#include "medicinesview.h"
#include "medicineseditview.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goPreviousView();
    void goDoctorView();
    void goDoctorEditView(int rowNo);
    void goDepartmentView();
    void goDepartmentEditView(int rowNo);
    void goPatientView();
    void goPatientEditView(int rowNo);
    void goMedicinesView();
    void goMedicinesEditView(int rowNo);

private slots:
    void on_btBack_clicked();
    void on_stackedWidget_currentChanged(int arg1);
    void on_btLogout_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterView *ui;

    LoginView *loginView;
    WelcomeView *welcomeView;
    DoctorView *doctorView;
    DoctorEditView *doctorEditView;
    DepartmentView *departmentView;
    DepartmentEditView *departmentEditView;
    PatientView *patientView;
    PatientEditView *patientEditView;
    MedicinesView *medicinesView;
    MedicinesEditView *medicinesEditView;
};
#endif // MASTERVIEW_H
