#include "medicineseditview.h"
#include "ui_medicineseditview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QSqlError>

MedicinesEditView::MedicinesEditView(int rowNo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicinesEditView)
    , m_rowNo(rowNo)
{
    ui->setupUi(this);

    QSqlTableModel *model = IDatabase::getInstance().getMedicinesModel();
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    // 根据UI文件更新映射关系
    mapper->addMapping(ui->dbEditID_Medicines, 0);      // medicine_id (主键)
    mapper->addMapping(ui->dbEditName_Medicines, 1);    // medicine_name
    mapper->addMapping(ui->dbEditSpecification, 2);     // specification
    mapper->addMapping(ui->dbEditManufacturer, 3);      // manufacturer
    mapper->addMapping(ui->dbEditPrice, 4);             // price
    mapper->addMapping(ui->dbEditQuantity, 5);          // stock_quantity

    if (m_rowNo >= 0) {
        mapper->setCurrentIndex(m_rowNo);
        this->setWindowTitle("编辑药品");  // 使用窗口标题
    } else {
        int newRow = model->rowCount();
        model->insertRow(newRow);
        mapper->setCurrentIndex(newRow);
        this->setWindowTitle("新增药品");  // 使用窗口标题
    }
}

MedicinesEditView::~MedicinesEditView()
{
    delete ui;
}

void MedicinesEditView::on_pushButton_3_clicked()  // UI中的"保存"按钮
{
    if (ui->dbEditName_Medicines->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "药品名称不能为空！");
        return;
    }

    if (IDatabase::getInstance().submitMedicinesEdit()) {
        QMessageBox::information(this, "成功", "保存成功！");
        emit parentWidget()->close();
    } else {
        QMessageBox::critical(this, "错误", "保存失败！");
    }
}

void MedicinesEditView::on_pushButton_4_clicked()  // UI中的"取消"按钮
{
    IDatabase::getInstance().revertMedicinesEdit();
    emit parentWidget()->close();
}
