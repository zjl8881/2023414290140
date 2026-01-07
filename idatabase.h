#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

class IDatabase
{
public:
    static IDatabase& getInstance();

    // 数据库操作
    bool openDatabase();
    QSqlDatabase& getDatabase();
    void initDatabase();

    // 表模型获取
    QSqlTableModel* getDepartmentModel();
    QSqlTableModel* getDoctorModel();
    QSqlTableModel* getPatientModel();
    QSqlTableModel* getMedicinesModel();

    // 登录验证
    bool userLogin(const QString& username, const QString& password);

    // 编辑操作
    bool submitDepartmentEdit();
    bool revertDepartmentEdit();
    bool submitDoctorEdit();
    bool revertDoctorEdit();
    bool submitPatientEdit();
    bool revertPatientEdit();
    bool submitMedicinesEdit();
    bool revertMedicinesEdit();

private:
    IDatabase();
    ~IDatabase();
    IDatabase(const IDatabase&) = delete;
    IDatabase& operator=(const IDatabase&) = delete;

    QSqlDatabase m_db;

    // 表模型
    QSqlTableModel* m_departmentModel = nullptr;
    QSqlTableModel* m_doctorModel = nullptr;
    QSqlTableModel* m_patientModel = nullptr;
    QSqlTableModel* m_medicinesModel = nullptr;

    // 初始化表模型
    void initDepartmentModel();
    void initDoctorModel();
    void initPatientModel();
    void initMedicinesModel();
};

#endif // IDATABASE_H
