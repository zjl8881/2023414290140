#include "doctorview.h"
#include "ui_doctorview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlError>

DoctorView::DoctorView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorView)
{
    ui->setupUi(this);

    // 设置表格模型
    ui->tableView->setModel(IDatabase::getInstance().getDoctorModel());
    ui->tableView->resizeColumnsToContents();
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btAdd_clicked()
{
    emit goDoctorEditView(-1);
}

void DoctorView::on_btEdit_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要编辑的医生！");
        return;
    }

    int row = selected.first().row();
    emit goDoctorEditView(row);
}

void DoctorView::on_btDelete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要删除的医生！");
        return;
    }

    int row = selected.first().row();
    QSqlTableModel *model = IDatabase::getInstance().getDoctorModel();

    int ret = QMessageBox::question(this, "确认删除",
                                    "确定要删除选中的医生吗？此操作不可恢复！");

    if (ret == QMessageBox::Yes) {
        model->removeRow(row);
        if (!model->submitAll()) {
            QMessageBox::critical(this, "错误", "删除失败：" + model->lastError().text());
        }
    }
}

void DoctorView::on_btRefresh_clicked()
{
    IDatabase::getInstance().getDoctorModel()->select();
}
