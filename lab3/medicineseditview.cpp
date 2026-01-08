#include "medicineseditview.h"
#include "ui_medicineseditview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include "loghelper.h"
#include <QThread>
#include "reportworker.h"

MedicinesEditView::MedicinesEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::MedicinesEditView)
    , m_editIndex(index)
    , dataMapper(nullptr)
    , m_db(nullptr)
{
    ui->setupUi(this);

    // 获取IDatabase实例
    m_db = &IDatabase::getInstance();

    if (!m_db->medicinesTabModel) {
        QMessageBox::critical(this, "错误", "药品数据模型未初始化！");
        return;
    }

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(m_db->medicinesTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 绑定字段映射
    int medicineIdIndex = m_db->medicinesTabModel->fieldIndex("medicine_id");
    int nameIndex = m_db->medicinesTabModel->fieldIndex("medicine_name");
    int specIndex = m_db->medicinesTabModel->fieldIndex("specification");
    int manuIndex = m_db->medicinesTabModel->fieldIndex("manufacturer");
    int priceIndex = m_db->medicinesTabModel->fieldIndex("price");
    int stockIndex = m_db->medicinesTabModel->fieldIndex("stock_quantity");

    if (medicineIdIndex >= 0) dataMapper->addMapping(ui->dbEditID_Medicines, medicineIdIndex);
    if (nameIndex >= 0) dataMapper->addMapping(ui->dbEditName_Medicines, nameIndex);
    if (specIndex >= 0) dataMapper->addMapping(ui->dbEditSpecification, specIndex);
    if (manuIndex >= 0) dataMapper->addMapping(ui->dbEditManufacturer, manuIndex);
    if (priceIndex >= 0) dataMapper->addMapping(ui->dbEditPrice, priceIndex);
    if (stockIndex >= 0) dataMapper->addMapping(ui->dbEditQuantity, stockIndex);

    if (index >= 0) {
        dataMapper->setCurrentIndex(index);
    } else {
        // 新增模式
        ui->dbEditID_Medicines->clear();
        ui->dbEditName_Medicines->clear();
        ui->dbEditSpecification->clear();
        ui->dbEditManufacturer->clear();
        ui->dbEditPrice->clear();
        ui->dbEditQuantity->clear();

        if (m_db->medicinesTabModel->rowCount() > 0) {
            dataMapper->setCurrentIndex(m_db->medicinesTabModel->rowCount() - 1);
        }
    }

    ui->dbEditID_Medicines->setReadOnly(false);
}

MedicinesEditView::~MedicinesEditView()
{
    delete dataMapper;
    delete ui;
}

bool MedicinesEditView::validateInput()
{
    if (ui->dbEditID_Medicines->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "药品ID不能为空！");
        return false;
    }
    if (ui->dbEditName_Medicines->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "药品名称不能为空！");
        return false;
    }
    if (ui->dbEditPrice->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "药品单价不能为空！");
        return false;
    }
    return true;
}

void MedicinesEditView::on_pushButton_3_clicked()  // 保存按钮
{
    if (!validateInput()) {
        LogHelper::getInstance().writeLog("药品信息保存失败：输入验证未通过", "ERROR");
        return;
    }

    if (dataMapper) {
        dataMapper->submit();
    }

    if (m_db && m_db->medicinesTabModel) {
        if (m_db->medicinesTabModel->submitAll()) {
            QString medicineName = ui->dbEditName_Medicines->text();
            QString medicineId = ui->dbEditID_Medicines->text();

            if (m_editIndex >= 0) {
                LogHelper::getInstance().writeLog(
                    QString("药品信息修改成功：药品ID=%1，药品名称=%2").arg(medicineId).arg(medicineName),
                    "INFO");
            } else {
                LogHelper::getInstance().writeLog(
                    QString("药品信息新增成功：药品ID=%1，药品名称=%2").arg(medicineId).arg(medicineName),
                    "INFO");
            }

            QMessageBox::information(this, "提示", "保存成功！");
            emit goPreviousView();
        } else {
            QString errorMsg = m_db->medicinesTabModel->lastError().text();
            LogHelper::getInstance().writeLog(
                QString("药品信息保存失败：%1").arg(errorMsg),
                "ERROR");
            QMessageBox::critical(this, "错误", "保存失败：" + errorMsg);
            m_db->medicinesTabModel->revertAll();
        }
    }
}

void MedicinesEditView::on_pushButton_4_clicked()  // 取消按钮
{
    LogHelper::getInstance().writeLog("取消药品信息编辑", "INFO");

    if (m_db && m_db->medicinesTabModel) {
        m_db->medicinesTabModel->revertAll();
    }
    if (dataMapper) {
        dataMapper->revert();
    }
    emit goPreviousView();
}

void MedicinesEditView::on_btReport_clicked()
{
    ui->btReport->setEnabled(false);
    ui->progressBar->setValue(0);

    QThread *thread = new QThread;
    ReportWorker *worker = new ReportWorker("medicine");
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ReportWorker::process);
    connect(worker, &ReportWorker::progressUpdated, ui->progressBar, &QProgressBar::setValue);
    connect(worker, &ReportWorker::finished, this, &MedicinesEditView::handleReportFinished);

    connect(worker, &ReportWorker::finished, thread, &QThread::quit);
    connect(worker, &ReportWorker::finished, worker, &ReportWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void MedicinesEditView::handleReportFinished(bool success, QString message)
{
    if (success) QMessageBox::information(this, "报表生成", message);
    else QMessageBox::critical(this, "生成失败", message);

    ui->btReport->setEnabled(true);
    ui->progressBar->setValue(0);
}
