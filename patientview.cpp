#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlError>

PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
{
    ui->setupUi(this);

    // 设置表格模型
    ui->tableView->setModel(IDatabase::getInstance().getPatientModel());
    ui->tableView->resizeColumnsToContents();
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btAdd_clicked()
{
    emit goPatientEditView(-1);
}

void PatientView::on_btEdit_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要编辑的患者！");
        return;
    }

    int row = selected.first().row();
    emit goPatientEditView(row);
}

void PatientView::on_btDelete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要删除的患者！");
        return;
    }

    int row = selected.first().row();
    QSqlTableModel *model = IDatabase::getInstance().getPatientModel();

    int ret = QMessageBox::question(this, "确认删除",
                                    "确定要删除选中的患者吗？此操作不可恢复！");

    if (ret == QMessageBox::Yes) {
        model->removeRow(row);
        if (!model->submitAll()) {
            QMessageBox::critical(this, "错误", "删除失败：" + model->lastError().text());
        }
    }
}

void PatientView::on_btRefresh_clicked()
{
    IDatabase::getInstance().getPatientModel()->select();
}
