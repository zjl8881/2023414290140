#include "medicinesview.h"
#include "ui_medicinesview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "loghelper.h"
#include <QThread>
#include "reportworker.h"

MedicinesView::MedicinesView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicinesView)
    , m_db(IDatabase::getInstance())
{
    ui->setupUi(this);

    // 表格配置
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 绑定药品表模型
    if(m_db.initMedicinesModel()){
        ui->tableView->setModel(m_db.medicinesTabModel);
        ui->tableView->setSelectionModel(m_db.theMedicinesSelection);
        m_originalFilter = m_db.medicinesTabModel->filter();
    } else {
        // 即使initMedicinesModel返回false，也尝试绑定现有模型
        if (m_db.medicinesTabModel) {
            ui->tableView->setModel(m_db.medicinesTabModel);
            ui->tableView->setSelectionModel(m_db.theMedicinesSelection);
            m_originalFilter = m_db.medicinesTabModel->filter();

            // 强制刷新数据
            m_db.medicinesTabModel->select();
        }
    }

    ui->txtSearch->setPlaceholderText("请输入药品名称进行查找");
}

MedicinesView::~MedicinesView()
{
    delete ui;
}

void MedicinesView::on_btAdd_clicked()
{
    // 1. 初始化药品模型
    if (!m_db.medicinesTabModel) {
        QMessageBox::critical(this, "错误", "药品数据模型未初始化！");
        LogHelper::getInstance().writeLog("药品添加失败：数据模型未初始化", "ERROR");
        return;
    }

    // 2. 添加新行
    int currow = IDatabase::getInstance().addNewMedicines();
    // 3. 提交新行到模型
    IDatabase::getInstance().medicinesTabModel->submitAll();

    LogHelper::getInstance().writeLog(QString("新增药品：行索引=%1").arg(currow), "INFO");

    // 4. 跳转编辑页（传 -1 标识新增）
    emit goMedicinesEditView(-1);
}

void MedicinesView::on_btEdit_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选中要修改的药品！");
        return;
    }
    int selectedRow = selectedIndexes.first().row();
    // 编辑模式：传选中行索引
    emit goMedicinesEditView(selectedRow);
}

void MedicinesView::on_btDelete_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选中要删除的药品！");
        return;
    }
    int selectedRow = selectedIndexes.first().row();

    // 获取要删除的药品名称（用于日志）
    QString medicineName = m_db.medicinesTabModel->index(selectedRow, m_db.medicinesTabModel->fieldIndex("medicine_name")).data().toString();

    int ret = QMessageBox::question(this, "确认", "是否确定删除选中的药品？", QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        LogHelper::getInstance().writeLog(QString("药品删除取消：药品名称=%1").arg(medicineName), "INFO");
        return;
    }

    m_db.medicinesTabModel->removeRow(selectedRow);
    if (m_db.medicinesTabModel->submitAll()) {
        QMessageBox::information(this, "提示", "药品删除成功！");
        LogHelper::getInstance().writeLog(QString("药品删除成功：药品名称=%1").arg(medicineName), "INFO");
        m_db.medicinesTabModel->select();
    } else {
        QString errMsg = m_db.medicinesTabModel->lastError().text();
        QMessageBox::critical(this, "错误", "药品删除失败：" + errMsg);
        LogHelper::getInstance().writeLog(QString("药品删除失败：药品名称=%1，错误信息=%2").arg(medicineName, errMsg), "ERROR");
        m_db.medicinesTabModel->revertAll();
    }
}

void MedicinesView::on_btSearch_clicked()
{
    if (!m_db.medicinesTabModel) {
        QMessageBox::warning(this, "警告", "药品数据模型未初始化！");
        LogHelper::getInstance().writeLog("药品搜索失败：数据模型未初始化", "ERROR");
        return;
    }

    QString searchText = ui->txtSearch->text().trimmed();
    LogHelper::getInstance().writeLog(QString("药品搜索：关键词=%1").arg(searchText), "INFO");

    if (searchText.isEmpty()) {
        m_db.medicinesTabModel->setFilter(m_originalFilter);
        m_db.medicinesTabModel->select();
        QMessageBox::information(this, "提示", "已清空搜索，显示所有药品数据！");
        return;
    }

    QString filter = QString("medicine_name LIKE '%%1%'").arg(searchText);
    m_db.medicinesTabModel->setFilter(filter);
    if (m_db.medicinesTabModel->select()) {
        int rowCount = m_db.medicinesTabModel->rowCount();
        LogHelper::getInstance().writeLog(QString("药品搜索结果：关键词=%1，匹配数量=%2").arg(searchText).arg(rowCount), "INFO");
        if (rowCount == 0) {
            QMessageBox::information(this, "提示", "未找到包含【" + searchText + "】的药品！");
        } else {
            QMessageBox::information(this, "提示", "找到 " + QString::number(rowCount) + " 条匹配的药品数据！");
        }
    } else {
        QString errMsg = m_db.medicinesTabModel->lastError().text();
        m_db.medicinesTabModel->setFilter(m_originalFilter);
        m_db.medicinesTabModel->select();
        QMessageBox::critical(this, "错误", "搜索失败：" + errMsg);
        LogHelper::getInstance().writeLog(QString("药品搜索失败：关键词=%1，错误信息=%2").arg(searchText, errMsg), "ERROR");
    }
}

void MedicinesView::on_btReport_clicked()
{
    ui->btReport->setEnabled(false);
    ui->progressBar->setValue(0);

    QThread *thread = new QThread;
    ReportWorker *worker = new ReportWorker("medicine");
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ReportWorker::process);
    connect(worker, &ReportWorker::progressUpdated, ui->progressBar, &QProgressBar::setValue);
    connect(worker, &ReportWorker::finished, this, &MedicinesView::handleReportFinished);

    connect(worker, &ReportWorker::finished, thread, &QThread::quit);
    connect(worker, &ReportWorker::finished, worker, &ReportWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void MedicinesView::handleReportFinished(bool success, QString message)
{
    if (success) QMessageBox::information(this, "报表生成", message);
    else QMessageBox::critical(this, "生成失败", message);

    ui->btReport->setEnabled(true);
    ui->progressBar->setValue(0);
}
