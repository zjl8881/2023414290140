// reportworker.h
#ifndef REPORTWORKER_H
#define REPORTWORKER_H

#include <QObject>
#include <QDate>
#include "statisticstypes.h"

class ReportWorker : public QObject
{
    Q_OBJECT

public:
    explicit ReportWorker(QObject *parent = nullptr);

public slots:
    void generateReport(const QString &reportType, const QDate &startDate = QDate(),
                        const QDate &endDate = QDate(), const QString &title = "");

signals:
    void reportGenerated(const StatisticsReport &report);
    void reportGenerationFailed(const QString &error);
    void progressUpdated(int progress, const QString &message);

private:
    void generateComprehensiveReport(const QDate &startDate, const QDate &endDate, const QString &title);
    void generateDepartmentReport(const QDate &startDate, const QDate &endDate);
    void generateDoctorReport(const QDate &startDate, const QDate &endDate);
    void generatePatientReport(const QDate &startDate, const QDate &endDate);

    QVector<DepartmentStats> getDepartmentStatistics();
    QVector<DoctorStats> getDoctorStatistics(const QDate &startDate, const QDate &endDate);
    QVector<PatientStats> getPatientStatistics(const QDate &startDate, const QDate &endDate);
    QVector<MedicinesStats> getMedicinesStatistics();

    int getTotalCount(const QString &tableName);
};

#endif // REPORTWORKER_H
