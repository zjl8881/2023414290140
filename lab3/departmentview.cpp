#include "departmentview.h"
#include "ui_departmentview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "loghelper.h"

DepartmentView::DepartmentView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DepartmentView)
    , m_db(IDatabase::getInstance())
{
    ui->setupUi(this);

    // 表格配置（不变）
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 绑定科室表模型（不变）
    if(m_db.initDepartmentModel()){
        ui->tableView->setModel(m_db.departmentTabModel);
        ui->tableView->setSelectionModel(m_db.theDepartmentSelection);
        m_originalFilter = m_db.departmentTabModel->filter();
    }

    ui->txtSearch->setPlaceholderText("请输入科室名称进行查找");
}

DepartmentView::~DepartmentView()
{
    delete ui;
}

void DepartmentView::on_btAdd_clicked()
{
    // 1. 初始化科室模型（兜底）
    if (!m_db.departmentTabModel) {
        QMessageBox::critical(this, "错误", "科室数据模型初始化失败！");
        LogHelper::getInstance().writeLog("科室添加失败：数据模型未初始化", "ERROR"); // 错误日志
        return;
    }
    // 2. 添加新行（ID置空）
    int currow = IDatabase::getInstance().addNewDepartment();
    // 3. 提交新行到模型（确保映射器能读取到空数据）
    IDatabase::getInstance().departmentTabModel->submitAll();

    // 记录添加日志
    LogHelper::getInstance().writeLog(QString("新增科室：行索引=%1").arg(currow), "INFO");

    // 4. 跳转编辑页（传 -1 标识新增）
    emit goDepartmentEditView(-1);
}

// 编辑按钮（对齐PatientView的edit逻辑：发信号跳转，不弹窗）
void DepartmentView::on_btEdit_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选中要修改的科室！");
        return;
    }
    int selectedRow = selectedIndexes.first().row();
    // 编辑模式：传选中行索引
    emit goDepartmentEditView(selectedRow);
}

// 删除按钮（逻辑不变）
void DepartmentView::on_btDelete_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选中要删除的科室！");
        return;
    }
    int selectedRow = selectedIndexes.first().row();

    // 获取要删除的科室名称（用于日志）
    QString deptName = m_db.departmentTabModel->index(selectedRow, m_db.departmentTabModel->fieldIndex("NAME")).data().toString();

    int ret = QMessageBox::question(this, "确认", "是否确定删除选中的科室？", QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        LogHelper::getInstance().writeLog(QString("科室删除取消：科室名称=%1").arg(deptName), "INFO");
        return;
    }

    m_db.departmentTabModel->removeRow(selectedRow);
    if (m_db.departmentTabModel->submitAll()) {
        QMessageBox::information(this, "提示", "科室删除成功！");
        LogHelper::getInstance().writeLog(QString("科室删除成功：科室名称=%1").arg(deptName), "INFO");
        m_db.departmentTabModel->select();
    } else {
        QString errMsg = m_db.departmentTabModel->lastError().text();
        QMessageBox::critical(this, "错误", "科室删除失败：" + errMsg);
        LogHelper::getInstance().writeLog(QString("科室删除失败：科室名称=%1，错误信息=%2").arg(deptName, errMsg), "ERROR");
        m_db.departmentTabModel->revertAll();
    }
}

// 查找按钮（逻辑不变）
void DepartmentView::on_btSearch_clicked()
{
    if (!m_db.departmentTabModel) {
        QMessageBox::warning(this, "警告", "科室数据模型未初始化！");
        LogHelper::getInstance().writeLog("科室搜索失败：数据模型未初始化", "ERROR");
        return;
    }

    QString searchText = ui->txtSearch->text().trimmed();
    LogHelper::getInstance().writeLog(QString("科室搜索：关键词=%1").arg(searchText), "INFO");

    if (searchText.isEmpty()) {
        m_db.departmentTabModel->setFilter(m_originalFilter);
        m_db.departmentTabModel->select();
        QMessageBox::information(this, "提示", "已清空搜索，显示所有科室数据！");
        return;
    }

    QString filter = QString("NAME LIKE '%%1%'").arg(searchText);
    m_db.departmentTabModel->setFilter(filter);
    if (m_db.departmentTabModel->select()) {
        int rowCount = m_db.departmentTabModel->rowCount();
        LogHelper::getInstance().writeLog(QString("科室搜索结果：关键词=%1，匹配数量=%2").arg(searchText).arg(rowCount), "INFO");
        if (rowCount == 0) {
            QMessageBox::information(this, "提示", "未找到包含【" + searchText + "】的科室！");
        } else {
            QMessageBox::information(this, "提示", "找到 " + QString::number(rowCount) + " 条匹配的科室数据！");
        }
    } else {
        QString errMsg = m_db.departmentTabModel->lastError().text();
        m_db.departmentTabModel->setFilter(m_originalFilter);
        m_db.departmentTabModel->select();
        QMessageBox::critical(this, "错误", "搜索失败：" + errMsg);
        LogHelper::getInstance().writeLog(QString("科室搜索失败：关键词=%1，错误信息=%2").arg(searchText, errMsg), "ERROR");
    }
}
