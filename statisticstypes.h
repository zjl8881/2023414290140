// statisticstypes.h
#ifndef STATISTICSTYPES_H
#define STATISTICSTYPES_H

#include <QString>
#include <QDate>
#include <QVector>

// 科室统计数据结构
struct DepartmentStats {
    QString departmentId;
    QString departmentName;
    int doctorCount;
    int patientCount;
    int activeDoctors;
    double avgPatientsPerDoctor;
};

// 医生统计数据结构
struct DoctorStats {
    QString doctorId;
    QString doctorName;
    QString departmentName;
    QString title;
    int patientCount;
    QString status;
};

// 患者统计数据结构
struct PatientStats {
    QString patientId;
    QString patientName;
    QString sex;
    int age;
    double height;
    double weight;
    QDate createDate;
};

// 药品统计数据结构
struct MedicinesStats {
    QString medicineId;
    QString medicineName;
    QString manufacturer;
    double price;
    int stockQuantity;
    double totalValue;
};

// 综合统计报告
struct StatisticsReport {
    QDate reportDate;
    QString reportTitle;

    // 基础统计
    int totalDepartments;
    int totalDoctors;
    int totalPatients;
    int totalMedicines;

    // 详细统计
    QVector<DepartmentStats> departmentStats;
    QVector<DoctorStats> doctorStats;
    QVector<PatientStats> patientStats;
    QVector<MedicinesStats> medicinesStats;

    // 汇总信息
    QString generationTime;
    QString generatedBy;
};

#endif // STATISTICSTYPES_H
