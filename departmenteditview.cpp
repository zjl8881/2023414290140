#include "departmenteditview.h"
#include "ui_departmenteditview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QDataWidgetMapper>

DepartmentEditView::DepartmentEditView(int rowNo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DepartmentEditView)
    , m_rowNo(rowNo)
{
    ui->setupUi(this);

    QSqlTableModel *model = IDatabase::getInstance().getDepartmentModel();
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(ui->dbEditName_Department, 1);  // NAME
    mapper->addMapping(ui->dbEditManager_ID, 2);       // MANAGER_ID
    mapper->addMapping(ui->dbComboStatus, 3);         // STATUS
    mapper->addMapping(ui->dbEditID_Department, 0);    // ID (主键)

    if (m_rowNo >= 0) {
        mapper->setCurrentIndex(m_rowNo);
        // 模仿 PatientEditView：使用窗口标题而不是标签
        this->setWindowTitle("编辑科室");
    } else {
        int newRow = model->rowCount();
        model->insertRow(newRow);
        mapper->setCurrentIndex(newRow);
        this->setWindowTitle("新增科室");
    }
}

// 删除或注释掉所有使用 labelTitle 的代码
DepartmentEditView::~DepartmentEditView()
{
    delete ui;
}


// 修改保存按钮的槽函数名称
void DepartmentEditView::on_pushButton_3_clicked()
{
    if (ui->dbEditName_Department->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "科室名称不能为空！");
        return;
    }

    if (IDatabase::getInstance().submitDepartmentEdit()) {
        QMessageBox::information(this, "成功", "保存成功！");
        emit parentWidget()->close();
    } else {
        QMessageBox::critical(this, "错误", "保存失败！");
    }
}

void DepartmentEditView::on_pushButton_4_clicked()
{
    IDatabase::getInstance().revertDepartmentEdit();
    emit parentWidget()->close();
}
