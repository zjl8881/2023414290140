#include "doctorview.h"
#include "ui_doctorview.h"
#include "idatabase.h"
#include "doctoreditview.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "loghelper.h"

DoctorView::DoctorView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorView)
    , m_db(IDatabase::getInstance())
{
    ui->setupUi(this);

    // 表格配置（不变）
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 【新增】强制初始化医生模型（对齐PatientView的逻辑）
    if (!m_db.doctorTabModel) {
        if (!m_db.initDoctorModel()) {
            QMessageBox::critical(this, "错误", "医生数据模型初始化失败！");
            return;
        }
    }

    // 绑定模型（不变）
    ui->tableView->setModel(m_db.doctorTabModel);
    ui->tableView->setSelectionModel(m_db.theDoctorSelection);
    m_originalFilter = m_db.doctorTabModel->filter();

    ui->txtSearch->setPlaceholderText("请输入姓名进行查找");
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewDoctor();
    // 新增：提交新行到模型（确保映射器能读取到空数据）
    IDatabase::getInstance().doctorTabModel->submitAll();

    LogHelper::getInstance().writeLog(QString("新增医生：行索引=%1").arg(currow), "INFO");

    emit goDoctorEditView(currow);
}

// 修改按钮
void DoctorView::on_btEdit_clicked()
{
    // 1. 获取选中行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选中要修改的医生！");
        return;
    }
    int selectedRow = selectedIndexes.first().row();

    // 2. 跳转到编辑页面
    emit goDoctorEditView(selectedRow);
}

// 删除按钮
void DoctorView::on_btDelete_clicked()
{
    // 1. 获取选中行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选中要删除的医生！");
        return;
    }
    int selectedRow = selectedIndexes.first().row();

    // 获取医生姓名（用于日志）
    QString doctorName = m_db.doctorTabModel->index(selectedRow, m_db.doctorTabModel->fieldIndex("NAME")).data().toString();

    // 2. 确认删除
    int ret = QMessageBox::question(this, "确认", "是否确定删除选中的医生？", QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        LogHelper::getInstance().writeLog(QString("医生删除取消：医生姓名=%1").arg(doctorName), "INFO");
        return;
    }

    // 3. 执行删除
    m_db.doctorTabModel->removeRow(selectedRow);
    if (m_db.doctorTabModel->submitAll()) {
        QMessageBox::information(this, "提示", "医生删除成功！");
        LogHelper::getInstance().writeLog(QString("医生删除成功：医生姓名=%1").arg(doctorName), "INFO");
        m_db.doctorTabModel->select();  // 刷新列表
    } else {
        QString errMsg = m_db.doctorTabModel->lastError().text();
        QMessageBox::critical(this, "错误", "医生删除失败：" + errMsg);
        LogHelper::getInstance().writeLog(QString("医生删除失败：医生姓名=%1，错误信息=%2").arg(doctorName, errMsg), "ERROR");
        m_db.doctorTabModel->revertAll();  // 回滚
    }
}

// 查找按钮（模糊搜索姓名）
void DoctorView::on_btSearch_clicked()
{
    if (!m_db.doctorTabModel) {
        QMessageBox::warning(this, "警告", "医生数据模型未初始化！");
        LogHelper::getInstance().writeLog("医生搜索失败：数据模型未初始化", "ERROR");
        return;
    }

    // 1. 获取搜索关键词
    QString searchText = ui->txtSearch->text().trimmed();
    LogHelper::getInstance().writeLog(QString("医生搜索：关键词=%1").arg(searchText), "INFO");

    if (searchText.isEmpty()) {
        // 2. 清空搜索：恢复原始过滤器
        m_db.doctorTabModel->setFilter(m_originalFilter);
        m_db.doctorTabModel->select();
        QMessageBox::information(this, "提示", "已清空搜索，显示所有医生数据！");
        return;
    }

    // 3. 构建模糊搜索条件（NAME为医生表姓名字段，需和数据库一致）
    QString filter = QString("NAME LIKE '%%1%'").arg(searchText);
    m_db.doctorTabModel->setFilter(filter);

    // 4. 执行搜索并提示结果
    if (m_db.doctorTabModel->select()) {
        int rowCount = m_db.doctorTabModel->rowCount();
        LogHelper::getInstance().writeLog(QString("医生搜索结果：关键词=%1，匹配数量=%2").arg(searchText).arg(rowCount), "INFO");
        if (rowCount == 0) {
            QMessageBox::information(this, "提示", "未找到包含【" + searchText + "】的医生！");
        } else {
            QMessageBox::information(this, "提示", "找到 " + QString::number(rowCount) + " 条匹配的医生数据！");
        }
    } else {
        // 搜索失败：恢复原始数据
        QString errMsg = m_db.doctorTabModel->lastError().text();
        m_db.doctorTabModel->setFilter(m_originalFilter);
        m_db.doctorTabModel->select();
        QMessageBox::critical(this, "错误", "搜索失败：" + errMsg);
        LogHelper::getInstance().writeLog(QString("医生搜索失败：关键词=%1，错误信息=%2").arg(searchText, errMsg), "ERROR");
    }
}
