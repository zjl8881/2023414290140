// reportworker.cpp
#include "reportworker.h"
#include "idatabase.h"
#include "loghelper.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ReportWorker::ReportWorker(QObject *parent) : QObject(parent)
{
}

void ReportWorker::generateReport(const QString &reportType, const QDate &startDate,
                                  const QDate &endDate, const QString &title)
{
    LogHelper::getInstance().writeLog(
        QString("开始生成报表：类型=%1，时间范围=%2~%3")
            .arg(reportType)
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd")),
        "INFO"
        );

    try {
        if (reportType == "comprehensive") {
            generateComprehensiveReport(startDate, endDate, title);
        } else if (reportType == "department") {
            generateDepartmentReport(startDate, endDate);
        } else if (reportType == "doctor") {
            generateDoctorReport(startDate, endDate);
        } else if (reportType == "patient") {
            generatePatientReport(startDate, endDate);
        } else {
            throw QString("未知的报表类型: %1").arg(reportType);
        }
    } catch (const QString &error) {
        LogHelper::getInstance().writeLog(
            QString("报表生成失败：%1").arg(error),
            "ERROR"
            );
        emit reportGenerationFailed(error);
    }
}

void ReportWorker::generateComprehensiveReport(const QDate &startDate, const QDate &endDate, const QString &title)
{
    StatisticsReport report;
    report.reportDate = QDate::currentDate();
    report.reportTitle = title.isEmpty() ? "医院综合统计报告" : title;
    report.generationTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    report.generatedBy = "系统自动生成";

    emit progressUpdated(10, "开始生成综合统计报告...");

    // 获取基础统计
    report.totalDepartments = getTotalCount("department");
    emit progressUpdated(20, "获取科室统计信息...");

    report.totalDoctors = getTotalCount("doctor");
    emit progressUpdated(30, "获取医生统计信息...");

    report.totalPatients = getTotalCount("patient");
    emit progressUpdated(40, "获取患者统计信息...");

    report.totalMedicines = getTotalCount("medicines");
    emit progressUpdated(50, "获取药品统计信息...");

    // 获取详细统计
    report.departmentStats = getDepartmentStatistics();
    emit progressUpdated(60, "分析科室数据...");

    report.doctorStats = getDoctorStatistics(startDate, endDate);
    emit progressUpdated(70, "分析医生数据...");

    report.patientStats = getPatientStatistics(startDate, endDate);
    emit progressUpdated(80, "分析患者数据...");

    report.medicinesStats = getMedicinesStatistics();
    emit progressUpdated(90, "分析药品数据...");

    emit progressUpdated(100, "报告生成完成");
    emit reportGenerated(report);

    LogHelper::getInstance().writeLog("综合统计报告生成成功", "INFO");
}

QVector<DepartmentStats> ReportWorker::getDepartmentStatistics()
{
    QVector<DepartmentStats> stats;

    QSqlQuery query;
    query.prepare(
        "SELECT d.ID, d.NAME, d.STATUS, "
        "COUNT(DISTINCT doc.ID) as doctor_count "
        "FROM department d "
        "LEFT JOIN doctor doc ON doc.DEPARTMENT_ID = d.ID "
        "GROUP BY d.ID, d.NAME, d.STATUS"
        );

    if (!query.exec()) {
        throw QString("查询科室统计失败: %1").arg(query.lastError().text());
    }

    while (query.next()) {
        DepartmentStats deptStats;
        deptStats.departmentId = query.value("ID").toString();
        deptStats.departmentName = query.value("NAME").toString();
        deptStats.doctorCount = query.value("doctor_count").toInt();
        deptStats.activeDoctors = query.value("STATUS").toString() == "active" ? deptStats.doctorCount : 0;

        stats.append(deptStats);
    }

    return stats;
}

// 其他统计方法实现类似...
int ReportWorker::getTotalCount(const QString &tableName)
{
    QSqlQuery query;
    query.prepare(QString("SELECT COUNT(*) as total_count FROM %1").arg(tableName));

    if (!query.exec() || !query.next()) {
        return 0;
    }

    return query.value("total_count").toInt();
}

void ReportWorker::generateDepartmentReport(const QDate &startDate, const QDate &endDate)
{
    LogHelper::getInstance().writeLog(
        QString("开始生成科室报表：时间范围=%1~%2")
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd")),
        "INFO"
        );

    StatisticsReport report;
    report.reportDate = QDate::currentDate();
    report.reportTitle = "科室统计报告";
    report.generationTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    report.generatedBy = "系统自动生成";

    emit progressUpdated(50, "获取科室统计信息...");
    report.departmentStats = getDepartmentStatistics();

    emit progressUpdated(100, "科室报告生成完成");
    emit reportGenerated(report);

    LogHelper::getInstance().writeLog("科室统计报告生成成功", "INFO");
}

void ReportWorker::generateDoctorReport(const QDate &startDate, const QDate &endDate)
{
    LogHelper::getInstance().writeLog(
        QString("开始生成医生报表：时间范围=%1~%2")
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd")),
        "INFO"
        );

    StatisticsReport report;
    report.reportDate = QDate::currentDate();
    report.reportTitle = "医生工作统计报告";
    report.generationTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    report.generatedBy = "系统自动生成";

    emit progressUpdated(50, "获取医生统计信息...");
    report.doctorStats = getDoctorStatistics(startDate, endDate);

    emit progressUpdated(100, "医生报告生成完成");
    emit reportGenerated(report);

    LogHelper::getInstance().writeLog("医生统计报告生成成功", "INFO");
}

void ReportWorker::generatePatientReport(const QDate &startDate, const QDate &endDate)
{
    LogHelper::getInstance().writeLog(
        QString("开始生成患者报表：时间范围=%1~%2")
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd")),
        "INFO"
        );

    StatisticsReport report;
    report.reportDate = QDate::currentDate();
    report.reportTitle = "患者统计报告";
    report.generationTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    report.generatedBy = "系统自动生成";

    emit progressUpdated(50, "获取患者统计信息...");
    report.patientStats = getPatientStatistics(startDate, endDate);

    emit progressUpdated(100, "患者报告生成完成");
    emit reportGenerated(report);

    LogHelper::getInstance().writeLog("患者统计报告生成成功", "INFO");
}

QVector<DoctorStats> ReportWorker::getDoctorStatistics(const QDate &startDate, const QDate &endDate)
{
    QVector<DoctorStats> stats;

    QSqlQuery query;
    query.prepare(
        "SELECT d.ID, d.NAME, d.TITLE, d.STATUS, "
        "dep.NAME as department_name, "
        "COUNT(p.ID) as patient_count "
        "FROM doctor d "
        "LEFT JOIN department dep ON d.DEPARTMENT_ID = dep.ID "
        "LEFT JOIN patient p ON p.ID = d.ID "  // 注意：这里需要根据实际的患者-医生关系调整
        "WHERE 1=1 "  // 这里可以根据时间范围添加过滤条件
        "GROUP BY d.ID, d.NAME, d.TITLE, d.STATUS, dep.NAME"
        );

    if (!query.exec()) {
        throw QString("查询医生统计失败: %1").arg(query.lastError().text());
    }

    while (query.next()) {
        DoctorStats doctorStats;
        doctorStats.doctorId = query.value("ID").toString();
        doctorStats.doctorName = query.value("NAME").toString();
        doctorStats.title = query.value("TITLE").toString();
        doctorStats.status = query.value("STATUS").toString();
        doctorStats.departmentName = query.value("department_name").toString();
        doctorStats.patientCount = query.value("patient_count").toInt();

        stats.append(doctorStats);
    }

    return stats;
}

QVector<PatientStats> ReportWorker::getPatientStatistics(const QDate &startDate, const QDate &endDate)
{
    QVector<PatientStats> stats;

    QSqlQuery query;
    query.prepare(
        "SELECT ID, NAME, SEX, DOB, HEIGHT, WEIGHT, CREATEDTIMESTAMP "
        "FROM patient "
        "WHERE DATE(CREATEDTIMESTAMP) BETWEEN :startDate AND :endDate "
        "ORDER BY CREATEDTIMESTAMP DESC"
        );

    query.bindValue(":startDate", startDate.toString("yyyy-MM-dd"));
    query.bindValue(":endDate", endDate.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        throw QString("查询患者统计失败: %1").arg(query.lastError().text());
    }

    while (query.next()) {
        PatientStats patientStats;
        patientStats.patientId = query.value("ID").toString();
        patientStats.patientName = query.value("NAME").toString();
        patientStats.sex = query.value("SEX").toString();

        QDate dob = query.value("DOB").toDate();
        patientStats.age = QDate::currentDate().year() - dob.year();

        patientStats.height = query.value("HEIGHT").toDouble();
        patientStats.weight = query.value("WEIGHT").toDouble();
        patientStats.createDate = query.value("CREATEDTIMESTAMP").toDate();

        stats.append(patientStats);
    }

    return stats;
}

QVector<MedicinesStats> ReportWorker::getMedicinesStatistics()
{
    QVector<MedicinesStats> stats;

    QSqlQuery query;
    query.prepare(
        "SELECT medicine_id, medicine_name, manufacturer, price, stock_quantity, "
        "price * stock_quantity as total_value "
        "FROM medicines "
        "ORDER BY total_value DESC"
        );

    if (!query.exec()) {
        throw QString("查询药品统计失败: %1").arg(query.lastError().text());
    }

    while (query.next()) {
        MedicinesStats medicineStats;
        medicineStats.medicineId = query.value("medicine_id").toString();
        medicineStats.medicineName = query.value("medicine_name").toString();
        medicineStats.manufacturer = query.value("manufacturer").toString();
        medicineStats.price = query.value("price").toDouble();
        medicineStats.stockQuantity = query.value("stock_quantity").toInt();
        medicineStats.totalValue = query.value("total_value").toDouble();

        stats.append(medicineStats);
    }

    return stats;
}
