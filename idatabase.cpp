#include "idatabase.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QFile>
#include <QSqlRecord>

// 单例实例获取
IDatabase& IDatabase::getInstance()
{
    static IDatabase instance;
    return instance;
}

// 构造函数
IDatabase::IDatabase()
    : m_departmentModel(nullptr)
    , m_doctorModel(nullptr)
    , m_patientModel(nullptr)
    , m_medicinesModel(nullptr)
{
}

// 析构函数
IDatabase::~IDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }

    if (m_departmentModel) delete m_departmentModel;
    if (m_doctorModel) delete m_doctorModel;
    if (m_patientModel) delete m_patientModel;
    if (m_medicinesModel) delete m_medicinesModel;
}

// 打开数据库 - 替换为您的连接方式
bool IDatabase::openDatabase()
{
    if (m_db.isOpen()) {
        return true;
    }

    // 使用您指定的连接方式
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "C:/Users/86176/Desktop/lab3a.db";
    m_db.setDatabaseName(aFile);

    if (!m_db.open()) {
        qDebug() << "failed to open database";
        return false;
    } else {
        qDebug() << "open database is ok" << m_db.connectionName();
        return true;
    }
}

// 获取数据库引用
QSqlDatabase& IDatabase::getDatabase()
{
    return m_db;
}

// 初始化数据库表 - 修改为使用新的连接方式
void IDatabase::initDatabase()
{
    if (!m_db.isOpen()) {
        if (!openDatabase()) {
            qDebug() << "数据库连接失败，无法初始化表";
            return;
        }
    }

    QSqlQuery query(m_db);

    // 创建用户表
    query.exec("CREATE TABLE IF NOT EXISTS user ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "FULLNAME VARCHAR(100), "
               "USERNAME VARCHAR(50) UNIQUE, "
               "PASSWORD VARCHAR(100))");

    // 创建科室表
    query.exec("CREATE TABLE IF NOT EXISTS department ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "NAME VARCHAR(100), "
               "MANAGER_ID INTEGER, "
               "STATUS VARCHAR(20) DEFAULT 'active')");

    // 创建医生表
    query.exec("CREATE TABLE IF NOT EXISTS doctor ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "EMPLOYEEON DATE, "
               "NAME VARCHAR(100), "
               "DEPARTMENT_ID INTEGER, "
               "TITLE VARCHAR(50), "
               "STATUS VARCHAR(20) DEFAULT 'active')");

    // 创建患者表
    query.exec("CREATE TABLE IF NOT EXISTS patient ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "ID_CARD VARCHAR(20), "
               "NAME VARCHAR(100), "
               "SEX VARCHAR(10), "
               "DOB DATE, "
               "HEIGHT FLOAT, "
               "WEIGHT FLOAT, "
               "MOBILEPHONE VARCHAR(20), "
               "CREATEDTIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP)");

    // 创建药品表
    query.exec("CREATE TABLE IF NOT EXISTS medicines ("
               "medicine_id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "medicine_name VARCHAR(100), "
               "specification VARCHAR(50), "
               "manufacturer VARCHAR(100), "
               "price DECIMAL(10,2), "
               "stock_quantity INTEGER)");

    // 创建历史记录表
    query.exec("CREATE TABLE IF NOT EXISTS history ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "USER_ID INTEGER, "
               "EVENT TEXT, "
               "TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP)");

    qDebug() << "数据库表初始化完成";
}

// 获取科室表模型
QSqlTableModel* IDatabase::getDepartmentModel()
{
    if (!m_departmentModel) {
        initDepartmentModel();
    }
    return m_departmentModel;
}

// 获取医生表模型
QSqlTableModel* IDatabase::getDoctorModel()
{
    if (!m_doctorModel) {
        initDoctorModel();
    }
    return m_doctorModel;
}

// 获取患者表模型
QSqlTableModel* IDatabase::getPatientModel()
{
    if (!m_patientModel) {
        initPatientModel();
    }
    return m_patientModel;
}

// 获取药品表模型
QSqlTableModel* IDatabase::getMedicinesModel()
{
    if (!m_medicinesModel) {
        initMedicinesModel();
    }
    return m_medicinesModel;
}

// 用户登录验证
bool IDatabase::userLogin(const QString& username, const QString& password)
{
    if (!m_db.isOpen()) {
        if (!openDatabase()) {
            return false;
        }
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM user WHERE USERNAME = :username AND PASSWORD = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "登录查询失败:" << query.lastError().text();
        return false;
    }

    return query.next();
}

// 提交科室编辑
bool IDatabase::submitDepartmentEdit()
{
    if (!m_departmentModel) {
        return false;
    }
    return m_departmentModel->submitAll();
}

// 撤销科室编辑
bool IDatabase::revertDepartmentEdit()
{
    if (!m_departmentModel) {
        return false;
    }
    m_departmentModel->revertAll();
    return true;
}

// 提交医生编辑
bool IDatabase::submitDoctorEdit()
{
    if (!m_doctorModel) {
        return false;
    }
    return m_doctorModel->submitAll();
}

// 撤销医生编辑
bool IDatabase::revertDoctorEdit()
{
    if (!m_doctorModel) {
        return false;
    }
    m_doctorModel->revertAll();
    return true;
}

// 提交患者编辑
bool IDatabase::submitPatientEdit()
{
    if (!m_patientModel) {
        return false;
    }
    return m_patientModel->submitAll();
}

// 撤销患者编辑
bool IDatabase::revertPatientEdit()
{
    if (!m_patientModel) {
        return false;
    }
    m_patientModel->revertAll();
    return true;
}

// 提交药品编辑
bool IDatabase::submitMedicinesEdit()
{
    if (!m_medicinesModel) {
        return false;
    }
    return m_medicinesModel->submitAll();
}

// 撤销药品编辑
bool IDatabase::revertMedicinesEdit()
{
    if (!m_medicinesModel) {
        return false;
    }
    m_medicinesModel->revertAll();
    return true;
}

// 初始化科室表模型
void IDatabase::initDepartmentModel()
{
    if (m_departmentModel) {
        delete m_departmentModel;
    }

    m_departmentModel = new QSqlTableModel(nullptr, m_db);
    m_departmentModel->setTable("department");
    m_departmentModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 设置表头
    m_departmentModel->setHeaderData(0, Qt::Horizontal, "ID");
    m_departmentModel->setHeaderData(1, Qt::Horizontal, "科室名称");
    m_departmentModel->setHeaderData(2, Qt::Horizontal, "负责人ID");
    m_departmentModel->setHeaderData(3, Qt::Horizontal, "状态");

    if (!m_departmentModel->select()) {
        qDebug() << "加载department表失败:" << m_departmentModel->lastError().text();
    }
}

// 初始化医生表模型
void IDatabase::initDoctorModel()
{
    if (m_doctorModel) {
        delete m_doctorModel;
    }

    m_doctorModel = new QSqlTableModel(nullptr, m_db);
    m_doctorModel->setTable("doctor");
    m_doctorModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 设置表头
    m_doctorModel->setHeaderData(0, Qt::Horizontal, "ID");
    m_doctorModel->setHeaderData(1, Qt::Horizontal, "入职日期");
    m_doctorModel->setHeaderData(2, Qt::Horizontal, "姓名");
    m_doctorModel->setHeaderData(3, Qt::Horizontal, "科室ID");
    m_doctorModel->setHeaderData(4, Qt::Horizontal, "职称");
    m_doctorModel->setHeaderData(5, Qt::Horizontal, "状态");

    if (!m_doctorModel->select()) {
        qDebug() << "加载doctor表失败:" << m_doctorModel->lastError().text();
    }
}

// 初始化患者表模型
void IDatabase::initPatientModel()
{
    if (m_patientModel) {
        delete m_patientModel;
    }

    m_patientModel = new QSqlTableModel(nullptr, m_db);
    m_patientModel->setTable("patient");
    m_patientModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 设置表头
    m_patientModel->setHeaderData(0, Qt::Horizontal, "ID");
    m_patientModel->setHeaderData(1, Qt::Horizontal, "身份证号");
    m_patientModel->setHeaderData(2, Qt::Horizontal, "姓名");
    m_patientModel->setHeaderData(3, Qt::Horizontal, "性别");
    m_patientModel->setHeaderData(4, Qt::Horizontal, "出生日期");
    m_patientModel->setHeaderData(5, Qt::Horizontal, "身高");
    m_patientModel->setHeaderData(6, Qt::Horizontal, "体重");
    m_patientModel->setHeaderData(7, Qt::Horizontal, "手机号");
    m_patientModel->setHeaderData(8, Qt::Horizontal, "创建时间");

    if (!m_patientModel->select()) {
        qDebug() << "加载patient表失败:" << m_patientModel->lastError().text();
    }
}

// 初始化药品表模型
void IDatabase::initMedicinesModel()
{
    if (m_medicinesModel) {
        delete m_medicinesModel;
    }

    m_medicinesModel = new QSqlTableModel(nullptr, m_db);
    m_medicinesModel->setTable("medicines");
    m_medicinesModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 设置表头
    m_medicinesModel->setHeaderData(0, Qt::Horizontal, "药品ID");
    m_medicinesModel->setHeaderData(1, Qt::Horizontal, "药品名称");
    m_medicinesModel->setHeaderData(2, Qt::Horizontal, "规格");
    m_medicinesModel->setHeaderData(3, Qt::Horizontal, "生产厂家");
    m_medicinesModel->setHeaderData(4, Qt::Horizontal, "价格");
    m_medicinesModel->setHeaderData(5, Qt::Horizontal, "库存数量");

    if (!m_medicinesModel->select()) {
        qDebug() << "加载medicines表失败:" << m_medicinesModel->lastError().text();
    }
}
