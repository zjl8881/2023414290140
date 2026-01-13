#include "dialog_reserve.h"
#include "ui_dialog_reserve.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


DialogReserve::DialogReserve(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReserve)
{
    ui->setupUi(this);
    this->setWindowTitle("申请预约设备");

    // 重点：手动连接按钮盒信号到对话框槽
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    initDeviceList();
}

DialogReserve::~DialogReserve()
{
    delete ui;
}

void DialogReserve::initDeviceList()
{
    ui->comboName->clear();
    QSqlQuery query("SELECT name FROM devices");
    while (query.next()) {
        ui->comboName->addItem(query.value(0).toString());
    }
}

QString DialogReserve::getDevice() const
{
    return ui->comboName->currentText();
}

QString DialogReserve::getUser() const
{
    return ui->editUser->text();
}

void DialogReserve::on_buttonBox_accepted()
{
    // 逻辑已由 accept() 信号处理
}

void DialogReserve::on_buttonBox_rejected()
{
    // 逻辑已由 reject() 信号处理
}

int DialogReserve::getCount() const {
    return ui->editCount->text().toInt();
}
