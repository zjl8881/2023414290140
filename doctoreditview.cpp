#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QDataWidgetMapper>

DoctorEditView::DoctorEditView(int rowNo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorEditView)
    , m_rowNo(rowNo)
{
    ui->setupUi(this);

    QSqlTableModel *model = IDatabase::getInstance().getDoctorModel();
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(ui->dbEditIDCard, 1);        // EMPLOYEEON (工号)
    mapper->addMapping(ui->dbEditName, 2);          // NAME
    mapper->addMapping(ui->dbEditDepartmentNo, 3);  // DEPARTMENT_ID
    mapper->addMapping(ui->dbComboTitle, 4);        // TITLE
    mapper->addMapping(ui->dbComboStatus, 5);       // STATUS
    mapper->addMapping(ui->dbEditID_Doctor, 0);     // ID (主键)

    if (m_rowNo >= 0) {
        mapper->setCurrentIndex(m_rowNo);
        // 模仿 PatientEditView：使用窗口标题而不是标签
        this->setWindowTitle("编辑医生");
    } else {
        int newRow = model->rowCount();
        model->insertRow(newRow);
        mapper->setCurrentIndex(newRow);
        this->setWindowTitle("新增医生");
    }
}

// 删除或注释掉所有使用 labelTitle 的代码
DoctorEditView::~DoctorEditView()
{
    delete ui;
}

void DoctorEditView::on_pushButton_clicked()
{
    if (ui->dbEditName->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "医生姓名不能为空！");
        return;
    }

    if (IDatabase::getInstance().submitDoctorEdit()) {
        QMessageBox::information(this, "成功", "保存成功！");
        emit parentWidget()->close();
    } else {
        QMessageBox::critical(this, "错误", "保存失败！");
    }
}

void DoctorEditView::on_pushButton_2_clicked()
{
    IDatabase::getInstance().revertDoctorEdit();
    emit parentWidget()->close();
}
