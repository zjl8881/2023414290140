#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"
#include <QMessageBox>
#include "loghelper.h"
#include <QThread>
#include "reportworker.h"
#include <QThread>
#include "reportworker.h"

PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
    , m_db(IDatabase::getInstance())  // 初始化数据库单例引用
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    if(m_db.initPatientModel()){
        ui->tableView->setModel(m_db.patientTabModel);
        ui->tableView->setSelectionModel(m_db.thePatientSelection);
        m_originalFilter = m_db.patientTabModel->filter();  // 保存原始过滤器
    }
}
PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewPatient();
    LogHelper::getInstance().writeLog(QString("新增患者：行索引=%1").arg(currow), "INFO");
    emit goPatientEditView(currow);
}


void PatientView::on_btSearch_clicked()
{
    if (!m_db.patientTabModel) {
        QMessageBox::warning(this, "警告", "患者数据模型未初始化！");
        LogHelper::getInstance().writeLog("患者搜索失败：数据模型未初始化", "ERROR");
        return;
    }

    QString searchText = ui->txtSearch->text().trimmed();
    LogHelper::getInstance().writeLog(QString("患者搜索：关键词=%1").arg(searchText), "INFO");

    if (searchText.isEmpty()) {
        m_db.patientTabModel->setFilter(m_originalFilter);
        m_db.patientTabModel->select();
        QMessageBox::information(this, "提示", "已清空搜索，显示所有患者数据！");
        return;
    }

    QString filter = QString("NAME LIKE '%%1%'").arg(searchText);
    m_db.patientTabModel->setFilter(filter);
    if (m_db.patientTabModel->select()) {
        int rowCount = m_db.patientTabModel->rowCount();
        LogHelper::getInstance().writeLog(QString("患者搜索结果：关键词=%1，匹配数量=%2").arg(searchText).arg(rowCount), "INFO");
        if (rowCount == 0) {
            QMessageBox::information(this, "提示", "未找到包含【" + searchText + "】的患者！");
        } else {
            QMessageBox::information(this, "提示", "找到 " + QString::number(rowCount) + " 条匹配的患者数据！");
        }
    } else {
        QString errMsg = m_db.patientTabModel->lastError().text();
        m_db.patientTabModel->setFilter(m_originalFilter);
        m_db.patientTabModel->select();
        QMessageBox::critical(this, "错误", "搜索失败：" + errMsg);
        LogHelper::getInstance().writeLog(QString("患者搜索失败：关键词=%1，错误信息=%2").arg(searchText, errMsg), "ERROR");
    }
}


void PatientView::on_btDelete_clicked()
{
    // 获取选中患者姓名（用于日志）
    QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex();
    QString patientName = IDatabase::getInstance().patientTabModel->index(curIndex.row(), IDatabase::getInstance().patientTabModel->fieldIndex("NAME")).data().toString();

    LogHelper::getInstance().writeLog(QString("删除患者：患者姓名=%1").arg(patientName), "INFO");
    IDatabase::getInstance().deleteCurrentPatient();

    // 验证删除结果
    if (IDatabase::getInstance().patientTabModel->lastError().isValid()) {
        LogHelper::getInstance().writeLog(QString("患者删除失败：患者姓名=%1，错误信息=%2").arg(patientName, IDatabase::getInstance().patientTabModel->lastError().text()), "ERROR");
    } else {
        LogHelper::getInstance().writeLog(QString("患者删除成功：患者姓名=%1").arg(patientName), "INFO");
    }
}


void PatientView::on_btEdit_clicked()
{
    QModelIndex curIndex =
        IDatabase::getInstance().thePatientSelection->currentIndex();

    emit goPatientEditView(curIndex.row());
}

void PatientView::on_btReport_clicked()
{
    ui->btReport->setEnabled(false);
    ui->progressBar->setValue(0);

    QThread *thread = new QThread;
    ReportWorker *worker = new ReportWorker("patient");
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ReportWorker::process);
    connect(worker, &ReportWorker::progressUpdated, ui->progressBar, &QProgressBar::setValue);
    connect(worker, &ReportWorker::finished, this, &PatientView::handleReportFinished);

    connect(worker, &ReportWorker::finished, thread, &QThread::quit);
    connect(worker, &ReportWorker::finished, worker, &ReportWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void PatientView::handleReportFinished(bool success, QString message)
{
    QMessageBox::information(this, success ? "提示" : "错误", message);
    ui->btReport->setEnabled(true);
    ui->progressBar->setValue(0);
}


