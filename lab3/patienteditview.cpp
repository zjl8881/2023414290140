#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include "loghelper.h"
#include <QThread>
#include "reportworker.h"
#include <QMessageBox>

PatientEditView::PatientEditView(QWidget *parent,int index):
    QWidget(parent),
    ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel;
    dataMapper->setModel(IDatabase::getInstance().patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard, tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight, tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight, tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditMobile, tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDataEditDOB, tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);

    //ui->dbEditID->setEnabled(false);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()  // 保存按钮
{
    // 获取患者信息用于日志
    QString patientName = ui->dbEditName->text();
    QString patientId = ui->dbEditID->text();

    IDatabase::getInstance().submitPatientEdit();

    if (m_editIndex >= 0) {
        LogHelper::getInstance().writeLog(
            QString("患者信息修改成功：患者ID=%1，患者姓名=%2").arg(patientId).arg(patientName),
            "INFO");
    } else {
        LogHelper::getInstance().writeLog(
            QString("患者信息新增成功：患者ID=%1，患者姓名=%2").arg(patientId).arg(patientName),
            "INFO");
    }

    emit goPreviousView();
}


void PatientEditView::on_pushButton_2_clicked()  // 取消按钮
{
    LogHelper::getInstance().writeLog("取消患者信息编辑", "INFO");

    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();
}


void PatientEditView::on_btReport_clicked()
{
    ui->btReport->setEnabled(false);
    ui->progressBar->setValue(0);

    QThread *thread = new QThread;
    ReportWorker *worker = new ReportWorker("patient");
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ReportWorker::process);
    connect(worker, &ReportWorker::progressUpdated, ui->progressBar, &QProgressBar::setValue);
    connect(worker, &ReportWorker::finished, this, &PatientEditView::handleReportFinished);

    connect(worker, &ReportWorker::finished, thread, &QThread::quit);
    connect(worker, &ReportWorker::finished, worker, &ReportWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void PatientEditView::handleReportFinished(bool success, QString message)
{
    if (success) {
        QMessageBox::information(this, "成功", message);
    } else {
        QMessageBox::critical(this, "错误", message);
    }
    ui->btReport->setEnabled(true);
    ui->progressBar->setValue(0);
}
