#include "departmentview.h"
#include "ui_departmentview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlError>

DepartmentView::DepartmentView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DepartmentView)
{
    ui->setupUi(this);

    // 设置表格模型
    ui->tableView->setModel(IDatabase::getInstance().getDepartmentModel());
    ui->tableView->resizeColumnsToContents();
}

DepartmentView::~DepartmentView()
{
    delete ui;
}

void DepartmentView::on_btAdd_clicked()
{
    emit goDepartmentEditView(-1);
}

void DepartmentView::on_btEdit_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要编辑的科室！");
        return;
    }

    int row = selected.first().row();
    emit goDepartmentEditView(row);
}

void DepartmentView::on_btDelete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要删除的科室！");
        return;
    }

    int row = selected.first().row();
    QSqlTableModel *model = IDatabase::getInstance().getDepartmentModel();

    int ret = QMessageBox::question(this, "确认删除",
                                    "确定要删除选中的科室吗？此操作不可恢复！");

    if (ret == QMessageBox::Yes) {
        model->removeRow(row);
        if (!model->submitAll()) {
            QMessageBox::critical(this, "错误", "删除失败：" + model->lastError().text());
        }
    }
}

void DepartmentView::on_btRefresh_clicked()
{
    IDatabase::getInstance().getDepartmentModel()->select();
}
