// statisticscontroller.cpp
#include "statisticscontroller.h"
#include "reportworker.h"
#include "loghelper.h"
#include <QProgressDialog>
#include <QMessageBox>
#include <QApplication>

StatisticsController::StatisticsController(QObject *parent) : QObject(parent),
    m_workerThread(nullptr), m_worker(nullptr), m_progressDialog(nullptr)
{
}

StatisticsController::~StatisticsController()
{
    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait();
        delete m_workerThread;
    }
}

void StatisticsController::generateReport(QWidget *parent, const QString &reportType,
                                          const QDate &startDate, const QDate &endDate,
                                          const QString &title)
{
    // 创建进度对话框
    m_progressDialog = new QProgressDialog("正在生成报表...", "取消", 0, 100, parent);
    m_progressDialog->setWindowTitle("报表生成");
    m_progressDialog->setWindowModality(Qt::WindowModal);
    m_progressDialog->setMinimumDuration(0);
    m_progressDialog->show();

    QApplication::processEvents(); // 确保界面更新

    // 创建工作线程
    m_workerThread = new QThread(this);
    m_worker = new ReportWorker();
    m_worker->moveToThread(m_workerThread);

    // 连接信号槽
    connect(m_workerThread, &QThread::finished, m_worker, &ReportWorker::deleteLater);
    connect(m_worker, &ReportWorker::reportGenerated, this, &StatisticsController::onReportGenerated);
    connect(m_worker, &ReportWorker::reportGenerationFailed, this, &StatisticsController::onReportGenerationFailed);
    connect(m_worker, &ReportWorker::progressUpdated, this, &StatisticsController::onProgressUpdated);

    connect(m_progressDialog, &QProgressDialog::canceled, this, [this]() {
        if (m_workerThread && m_workerThread->isRunning()) {
            m_workerThread->quit();
            m_workerThread->wait();
        }
        if (m_progressDialog) {
            m_progressDialog->close();
            m_progressDialog->deleteLater();
            m_progressDialog = nullptr;
        }
    });

    // 启动线程
    m_workerThread->start();

    // 开始生成报表
    QMetaObject::invokeMethod(m_worker, "generateReport", Qt::QueuedConnection,
                              Q_ARG(QString, reportType),
                              Q_ARG(QDate, startDate),
                              Q_ARG(QDate, endDate),
                              Q_ARG(QString, title));
}

void StatisticsController::onReportGenerated(const StatisticsReport &report)
{
    if (m_progressDialog) {
        m_progressDialog->close();
        m_progressDialog->deleteLater();
        m_progressDialog = nullptr;
    }

    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait();
        m_workerThread = nullptr;
    }

    emit reportReady(report);

    LogHelper::getInstance().writeLog("报表生成完成并准备就绪", "INFO");
}

void StatisticsController::onReportGenerationFailed(const QString &error)
{
    if (m_progressDialog) {
        m_progressDialog->close();
        m_progressDialog->deleteLater();
        m_progressDialog = nullptr;
    }

    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait();
        m_workerThread = nullptr;
    }

    QMessageBox::critical(nullptr, "报表生成错误", QString("生成报表时发生错误：\n%1").arg(error));
}

void StatisticsController::onProgressUpdated(int progress, const QString &message)
{
    if (m_progressDialog) {
        m_progressDialog->setValue(progress);
        m_progressDialog->setLabelText(message);
        QApplication::processEvents();
    }
}
