#include "idatabase.h"
#include <QDebug>
#include <QUuid>

void IDatabase::ininDatabase()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="C:/Users/86176/Desktop/lab3a.db";
    database.setDatabaseName(aFile);

    if(!database.open())
    {
        qDebug() <<  "failed to open database";
    }else
        qDebug() <<  "open database is ok" << database.connectionName()  ;
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this, database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 新增：设置患者表中文字段表头
    int idIndex = patientTabModel->fieldIndex("ID");
    int nameIndex = patientTabModel->fieldIndex("NAME");
    int idCardIndex = patientTabModel->fieldIndex("ID_CARD");
    int heightIndex = patientTabModel->fieldIndex("HEIGHT");
    int weightIndex = patientTabModel->fieldIndex("WEIGHT");
    int mobileIndex = patientTabModel->fieldIndex("MOBILEPHONE");
    int dobIndex = patientTabModel->fieldIndex("DOB");
    int sexIndex = patientTabModel->fieldIndex("SEX");
    int createTimeIndex = patientTabModel->fieldIndex("CREATEDTIMESTAMP");

    patientTabModel->setHeaderData(idIndex, Qt::Horizontal, "患者ID");
    patientTabModel->setHeaderData(nameIndex, Qt::Horizontal, "患者姓名");
    patientTabModel->setHeaderData(idCardIndex, Qt::Horizontal, "身份证号");
    patientTabModel->setHeaderData(heightIndex, Qt::Horizontal, "身高(dm)");
    patientTabModel->setHeaderData(weightIndex, Qt::Horizontal, "体重(kg)");
    patientTabModel->setHeaderData(mobileIndex, Qt::Horizontal, "手机号");
    patientTabModel->setHeaderData(dobIndex, Qt::Horizontal, "出生日期");
    patientTabModel->setHeaderData(sexIndex, Qt::Horizontal, "性别");
    patientTabModel->setHeaderData(createTimeIndex, Qt::Horizontal, "创建时间");

    // 原有排序逻辑
    patientTabModel->setSort(nameIndex,Qt::AscendingOrder);
    if(!(patientTabModel->select()))
        return false;

    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;
}

bool IDatabase::initDoctorModel()
{
    // 1. 创建医生表模型
    doctorTabModel = new QSqlTableModel(this, database);
    doctorTabModel->setTable("doctor");
    doctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 2. 设置中文字段表头
    int idIndex = doctorTabModel->fieldIndex("ID");
    int nameIndex = doctorTabModel->fieldIndex("NAME");
    int employeeOnIndex = doctorTabModel->fieldIndex("EMPLOYEEON");
    int deptIdIndex = doctorTabModel->fieldIndex("DEPARTMENT_ID");
    int titleIndex = doctorTabModel->fieldIndex("TITLE");
    int statusIndex = doctorTabModel->fieldIndex("STATUS");

    doctorTabModel->setHeaderData(idIndex, Qt::Horizontal, "医生ID");
    doctorTabModel->setHeaderData(nameIndex, Qt::Horizontal, "医生姓名");
    doctorTabModel->setHeaderData(employeeOnIndex, Qt::Horizontal, "工号");
    doctorTabModel->setHeaderData(deptIdIndex, Qt::Horizontal, "所属科室ID");
    doctorTabModel->setHeaderData(titleIndex, Qt::Horizontal, "职称");
    doctorTabModel->setHeaderData(statusIndex, Qt::Horizontal, "状态");

    // 3. 排序 + 加载数据
    doctorTabModel->setSort(nameIndex, Qt::AscendingOrder);
    if(!(doctorTabModel->select())){
        return false;
    }

    // 4. 创建选择模型
    theDoctorSelection = new QItemSelectionModel(doctorTabModel);
    return true;
}

bool IDatabase::initDepartmentModel()
{
    if(departmentTabModel != nullptr){
        return true;
    }

    departmentTabModel = new QSqlTableModel(this, database);
    departmentTabModel->setTable("department");
    departmentTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    int idIndex = departmentTabModel->fieldIndex("ID");
    int nameIndex = departmentTabModel->fieldIndex("NAME");
    int managerIdIndex = departmentTabModel->fieldIndex("MANAGER_ID");
    int statusIndex = departmentTabModel->fieldIndex("STATUS");

    departmentTabModel->setHeaderData(idIndex, Qt::Horizontal, "科室ID");
    departmentTabModel->setHeaderData(nameIndex, Qt::Horizontal, "科室名称");
    departmentTabModel->setHeaderData(managerIdIndex, Qt::Horizontal, "科室主任ID");
    departmentTabModel->setHeaderData(statusIndex, Qt::Horizontal, "状态");

    if(!departmentTabModel->select()){
        qDebug() << "科室模型初始化失败：" << departmentTabModel->lastError().text();
        delete departmentTabModel;
        departmentTabModel = nullptr;
        return false;
    }

    theDepartmentSelection = new QItemSelectionModel(departmentTabModel, this);
    return true;
}

bool IDatabase::initMedicinesModel() {
    if (!medicinesTabModel) {
        // 第一次初始化：创建新模型
        medicinesTabModel = new QSqlTableModel(this);
        medicinesTabModel->setTable("medicines");
        medicinesTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

        // 设置表头
        medicinesTabModel->setHeaderData(0, Qt::Horizontal, "药品ID");
        medicinesTabModel->setHeaderData(1, Qt::Horizontal, "药品名称");
        medicinesTabModel->setHeaderData(2, Qt::Horizontal, "规格");
        medicinesTabModel->setHeaderData(3, Qt::Horizontal, "生产厂家");
        medicinesTabModel->setHeaderData(4, Qt::Horizontal, "单价");
        medicinesTabModel->setHeaderData(5, Qt::Horizontal, "库存数量");

        theMedicinesSelection = new QItemSelectionModel(medicinesTabModel);
    }

    // 无论是否第一次初始化，都执行数据刷新
    if (!medicinesTabModel->select()) {
        qDebug() << "药品模型数据加载失败：" << medicinesTabModel->lastError().text();
        return false;
    }

    return true;
}

int IDatabase::addNewMedicines() {
    if (medicinesTabModel) {
        int rowNum = medicinesTabModel->rowCount();
        medicinesTabModel->insertRow(rowNum);
        medicinesTabModel->setData(medicinesTabModel->index(rowNum, 1), "新药品");
        return rowNum;
    }
    return -1;
}
int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());

    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1,1);

    int curRecNo =curIndex.row();
    QSqlRecord curRec= patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));

    patientTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

int IDatabase::addNewDoctor()
{
    // 1. 在医生模型末尾插入新行
    int newRow = doctorTabModel->rowCount();
    doctorTabModel->insertRow(newRow, QModelIndex());
    QModelIndex curIndex = doctorTabModel->index(newRow, 1);

    // 2. 获取空记录（仅初始化空值，不再自动生成ID）
    QSqlRecord curRec = doctorTabModel->record(newRow);
    // 移除ID自动生成逻辑，改为空值
    curRec.setValue("ID", "");          // ID置空，允许手动输入
    curRec.setValue("NAME", "");        // 姓名空
    curRec.setValue("EMPLOYEEON", "");  // 工号空
    curRec.setValue("DEPARTMENT_ID", ""); // 科室ID空
    curRec.setValue("TITLE", "");       // 职称空
    curRec.setValue("STATUS", "");      // 状态空

    // 3. 将空记录写回模型
    doctorTabModel->setRecord(newRow, curRec);

    return curIndex.row();
}

int IDatabase::addNewDepartment()
{
    // 1. 在科室模型末尾插入新行
    int newRow = departmentTabModel->rowCount();
    departmentTabModel->insertRow(newRow, QModelIndex());
    QModelIndex curIndex = departmentTabModel->index(newRow, 1);

    // 2. 获取空记录（ID置空，允许手动输入）
    QSqlRecord curRec = departmentTabModel->record(newRow);
    curRec.setValue("ID", "");          // ID置空，不自动生成
    curRec.setValue("NAME", "");        // 名称空
    curRec.setValue("MANAGER_ID", "");  // 主任ID空
    curRec.setValue("STATUS", "");      // 状态空

    // 3. 将空记录写回模型
    departmentTabModel->setRecord(newRow, curRec);

    return curIndex.row();
}

// 新增：提交医生编辑（模仿submitPatientEdit）
bool IDatabase::submitDoctorEdit()
{
    return doctorTabModel->submitAll();
}

// 新增：回滚医生编辑（模仿revertPatientEdit）
void IDatabase::revertDoctorEdit()
{
    doctorTabModel->revertAll();
}


bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase:: revertPatientEdit()
{
    patientTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{

    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER", userName);
    //query.addBindValue(userName);
    query.exec();
    qDebug() << query.lastQuery() << query.first();

    if (query.first() && query.value("username").isValid()){
        QString passwd = query.value("password").toString();
        qDebug() << "数据库中的密码：" << passwd << "，输入的密码：" << password;
        if(passwd == password){
            qDebug() << "login OK";
            return "loginOk";
        }else{
            qDebug() <<"wrong password";
            return "wrongPassword";
        }
    }else{
        qDebug()<<"no such user";
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
