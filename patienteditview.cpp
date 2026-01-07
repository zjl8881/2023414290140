#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QSqlError>

PatientEditView::PatientEditView(int rowNo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
    , m_rowNo(rowNo)
{
    ui->setupUi(this);

    QSqlTableModel *model = IDatabase::getInstance().getPatientModel();
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    // 根据UI文件更新映射关系
    mapper->addMapping(ui->dbEditID, 0);              // ID (主键)
    mapper->addMapping(ui->dbEditIDCard, 1);         // ID_CARD
    mapper->addMapping(ui->dbEditName, 2);           // NAME
    mapper->addMapping(ui->dbComboSex, 3);            // SEX
    mapper->addMapping(ui->dbDataEditDOB, 4);         // DOB
    mapper->addMapping(ui->dbSpinHeight, 5);          // HEIGHT
    mapper->addMapping(ui->dbSpinWeight, 6);          // WEIGHT
    mapper->addMapping(ui->dbEditMobile, 7);         // MOBILEPHONE
    mapper->addMapping(ui->dbCreatedTimeStamp, 8);    // CREATEDTIMESTAMP

    if (m_rowNo >= 0) {
        mapper->setCurrentIndex(m_rowNo);
        this->setWindowTitle("编辑患者");  // 使用窗口标题
    } else {
        int newRow = model->rowCount();
        model->insertRow(newRow);
        mapper->setCurrentIndex(newRow);
        this->setWindowTitle("新增患者");  // 使用窗口标题
    }
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()  // UI中的"保存"按钮
{
    if (ui->dbEditName->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "患者姓名不能为空！");
        return;
    }

    if (IDatabase::getInstance().submitPatientEdit()) {
        QMessageBox::information(this, "成功", "保存成功！");
        emit parentWidget()->close();
    } else {
        QMessageBox::critical(this, "错误", "保存失败！");
    }
}

void PatientEditView::on_pushButton_2_clicked()  // UI中的"取消"按钮
{
    IDatabase::getInstance().revertPatientEdit();
    emit parentWidget()->close();
}
