#include "medicineseditview.h"
#include "ui_medicineseditview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>

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

void MedicinesEditView::on_pushButton_3_clicked()
{
    if (!validateInput()) {
        return;
    }

    if (dataMapper) {
        dataMapper->submit();
    }

    if (m_db && m_db->medicinesTabModel) {
        if (m_db->medicinesTabModel->submitAll()) {
            QMessageBox::information(this, "提示", "保存成功！");
            emit goPreviousView();
        } else {
            QMessageBox::critical(this, "错误", "保存失败：" + m_db->medicinesTabModel->lastError().text());
            m_db->medicinesTabModel->revertAll();
        }
    }
}

void MedicinesEditView::on_pushButton_4_clicked()
{
    if (m_db && m_db->medicinesTabModel) {
        m_db->medicinesTabModel->revertAll();
    }
    if (dataMapper) {
        dataMapper->revert();
    }
    emit goPreviousView();
}
