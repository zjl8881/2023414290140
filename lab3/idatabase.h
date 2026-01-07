#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include <qsqldatabase>
#include <QDebug>
#include <QDataWidgetMapper>
#include <QUuid>  // 新增：用于生成唯一ID

class IDatabase : public QObject
{
    Q_OBJECT
public:
    static IDatabase &getInstance()
    {
        static IDatabase instance;
        return instance;
    }

    QString userLogin(QString userName, QString password);

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &)           = delete;
    void operator=(IDatabase const &)= delete;

    QSqlDatabase database;
    void ininDatabase();

signals:

public:
    // 患者相关（原有）
    bool initPatientModel();
    int addNewPatient();
    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    // 医生相关（补充模仿患者的方法）
    int addNewDoctor();
    bool submitDoctorEdit();
    void revertDoctorEdit();
    int addNewDepartment();

    QSqlTableModel *patientTabModel;
    QItemSelectionModel *thePatientSelection;
    QSqlTableModel *doctorTabModel;
    QItemSelectionModel *theDoctorSelection;
    bool initDoctorModel();

    QSqlTableModel *departmentTabModel;
    QItemSelectionModel *theDepartmentSelection;
    bool initDepartmentModel();

    QSqlTableModel *medicinesTabModel;
    QItemSelectionModel *theMedicinesSelection;
    bool submitMedicinesEdit();
    void revertMedicinesEdit();
    int addNewMedicines();
    bool initMedicinesModel();
};

#endif // IDATABASE_H
