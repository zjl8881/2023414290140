#include "medicinesview.h"
#include "ui_medicinesview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlError>

MedicinesView::MedicinesView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicinesView)
{
    ui->setupUi(this);

    // 设置表格模型
    ui->tableView->setModel(IDatabase::getInstance().getMedicinesModel());
    ui->tableView->resizeColumnsToContents();
}

MedicinesView::~MedicinesView()
{
    delete ui;
}

void MedicinesView::on_btAdd_clicked()
{
    emit goMedicinesEditView(-1);
}

void MedicinesView::on_btEdit_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要编辑的药品！");
        return;
    }

    int row = selected.first().row();
    emit goMedicinesEditView(row);
}

void MedicinesView::on_btDelete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要删除的药品！");
        return;
    }

    int row = selected.first().row();
    QSqlTableModel *model = IDatabase::getInstance().getMedicinesModel();

    int ret = QMessageBox::question(this, "确认删除",
                                    "确定要删除选中的药品吗？此操作不可恢复！");

    if (ret == QMessageBox::Yes) {
        model->removeRow(row);
        if (!model->submitAll()) {
            QMessageBox::critical(this, "错误", "删除失败：" + model->lastError().text());
        }
    }
}

void MedicinesView::on_btRefresh_clicked()
{
    IDatabase::getInstance().getMedicinesModel()->select();
}
