#include "departmenteditview.h"
#include "ui_departmenteditview.h"
#include <QMessageBox>
#include <QDateTime>
#include <QUuid>
#include "loghelper.h"
#include <QThread>
#include "reportworker.h"

DepartmentEditView::DepartmentEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::DepartmentEditView)
    , m_db(IDatabase::getInstance())
    , m_editIndex(index)
    , dataMapper(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("编辑科室信息");

    // 1. 判空模型，避免崩溃
    if (!m_db.departmentTabModel) {
        QMessageBox::critical(this, "错误", "科室数据模型未初始化！");
        return;
    }

    // 2. 初始化映射器
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(m_db.departmentTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 3. 绑定UI控件到数据库字段
    dataMapper->addMapping(ui->dbEditID_Department, m_db.departmentTabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName_Department, m_db.departmentTabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditManager_ID, m_db.departmentTabModel->fieldIndex("MANAGER_ID"));
    dataMapper->addMapping(ui->dbComboStatus, m_db.departmentTabModel->fieldIndex("STATUS"));

    // 4. 区分新增/编辑场景（核心修改）
    if (index >= 0) {
        // 编辑场景：加载选中行数据
        dataMapper->setCurrentIndex(index);
        // 加载状态下拉框（兼容原有逻辑）
        loadDepartmentData();
    } else {
        // 新增场景：清空所有UI控件
        ui->dbEditID_Department->clear();
        ui->dbEditName_Department->clear();
        ui->dbEditManager_ID->clear();
        ui->dbComboStatus->setCurrentIndex(-1); // 下拉框置空（默认无选中）
        // 映射器绑定到新行（index=-1 对应新增行）
        int newRow = m_db.departmentTabModel->rowCount() - 1;
        dataMapper->setCurrentIndex(newRow);
    }

    // 5. ID字段可编辑（允许手动输入）
    ui->dbEditID_Department->setReadOnly(false);
}


DepartmentEditView::~DepartmentEditView()
{
    delete ui;
    delete dataMapper;  // 释放映射器
}

// 加载科室数据（映射器已绑定，此方法可选保留）
void DepartmentEditView::loadDepartmentData()
{
    if (m_editIndex < 0 || !m_db.departmentTabModel) {
        return;
    }

    // 兼容原有逻辑（映射器已绑定，可省略）
    QModelIndex index = m_db.departmentTabModel->index(m_editIndex, m_db.departmentTabModel->fieldIndex("STATUS"));
    QString statusText = m_db.departmentTabModel->data(index).toString();
    int statusIndex = ui->dbComboStatus->findText(statusText);
    if (statusIndex != -1) {
        ui->dbComboStatus->setCurrentIndex(statusIndex);
    }
}

// 完善输入验证（ID不能为空）
bool DepartmentEditView::validateInput()
{
    if (ui->dbEditID_Department->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "科室ID不能为空！");
        return false;
    }
    if (ui->dbEditName_Department->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "科室名称不能为空！");
        return false;
    }
    return true;
}

void DepartmentEditView::on_pushButton_3_clicked()  // 保存按钮
{
    // 1. 输入验证（ID不能为空）
    if (!validateInput()) {
        LogHelper::getInstance().writeLog("科室信息保存失败：输入验证未通过", "ERROR");
        return;
    }

    // 2. 提交映射器修改
    dataMapper->submit();

    // 3. 提交到数据库
    if (m_db.departmentTabModel->submitAll()) {
        QString deptName = ui->dbEditName_Department->text();
        QString deptId = ui->dbEditID_Department->text();

        if (m_editIndex >= 0) {
            LogHelper::getInstance().writeLog(
                QString("科室信息修改成功：科室ID=%1，科室名称=%2").arg(deptId).arg(deptName),
                "INFO");
        } else {
            LogHelper::getInstance().writeLog(
                QString("科室信息新增成功：科室ID=%1，科室名称=%2").arg(deptId).arg(deptName),
                "INFO");
        }

        QMessageBox::information(this, "提示", "科室信息保存成功！");
        emit goPreviousView();
    } else {
        QString errorMsg = m_db.departmentTabModel->lastError().text();
        LogHelper::getInstance().writeLog(
            QString("科室信息保存失败：%1").arg(errorMsg),
            "ERROR");
        QMessageBox::critical(this, "错误", "保存失败：" + errorMsg);
        m_db.departmentTabModel->revertAll(); // 回滚
    }
}

void DepartmentEditView::on_pushButton_4_clicked()  // 取消按钮
{
    LogHelper::getInstance().writeLog("取消科室信息编辑", "INFO");

    // 回滚修改
    m_db.departmentTabModel->revertAll();
    dataMapper->revert(); // 同步回滚UI
    emit goPreviousView();
}

void DepartmentEditView::on_btReport_clicked()
{
    ui->btReport->setEnabled(false);
    ui->progressBar->setValue(0);

    QThread *thread = new QThread;
    ReportWorker *worker = new ReportWorker("department");
    worker->moveToThread(thread);

    // 连接信号
    connect(thread, &QThread::started, worker, &ReportWorker::process);
    connect(worker, &ReportWorker::progressUpdated, ui->progressBar, &QProgressBar::setValue);
    connect(worker, &ReportWorker::finished, this, &DepartmentEditView::handleReportFinished);

    // 线程清理
    connect(worker, &ReportWorker::finished, thread, &QThread::quit);
    connect(worker, &ReportWorker::finished, worker, &ReportWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void DepartmentEditView::handleReportFinished(bool success, QString message)
{
    if (success) {
        QMessageBox::information(this, "成功", message);
    } else {
        QMessageBox::critical(this, "错误", message);
    }
    ui->btReport->setEnabled(true);
    ui->progressBar->setValue(0);
}
