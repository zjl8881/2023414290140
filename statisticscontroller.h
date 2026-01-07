// statisticscontroller.h
#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include <QObject>
#include <QThread>
#include "reportworker.h"
#include "statisticstypes.h"

class QProgressDialog;

class StatisticsController : public QObject
{
    Q_OBJECT

public:
    explicit StatisticsController(QObject *parent = nullptr);
    ~StatisticsController();

    void generateReport(QWidget *parent, const QString &reportType,
                        const QDate &startDate = QDate(), const QDate &endDate = QDate(),
                        const QString &title = "");

signals:
    void reportReady(const StatisticsReport &report);

private slots:
    void onReportGenerated(const StatisticsReport &report);
    void onReportGenerationFailed(const QString &error);
    void onProgressUpdated(int progress, const QString &message);

private:
    QThread *m_workerThread;
    ReportWorker *m_worker;
    QProgressDialog *m_progressDialog;
};

#endif // STATISTICSCONTROLLER_H
