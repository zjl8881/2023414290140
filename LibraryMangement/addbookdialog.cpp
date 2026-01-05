#include "addbookdialog.h"
#include "ui_addbookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent)
    // 父类初始化列表仍为QDialog（修改头文件后，这里会自动匹配）
    : QDialog(parent)
    , ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
    // 绑定确认按钮点击信号到自定义槽函数
    connect(ui->btnOk, &QPushButton::clicked, this, &AddBookDialog::onBtnOkClicked);
    // 绑定取消按钮点击信号到QDialog的reject槽（关闭对话框，返回Rejected）
    connect(ui->btnCancel, &QPushButton::clicked, this, &AddBookDialog::reject);
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

// 获取用户输入的图书信息
Book AddBookDialog::getBookInfo() const
{
    return Book(
        ui->editId->text(),     // 图书编号
        ui->editName->text(),   // 图书名称
        ui->editAuthor->text(), // 作者
        ui->spinCount->value()  // 库存数量
        );
}

// 确认按钮点击的槽函数逻辑
void AddBookDialog::onBtnOkClicked()
{
    // 简单校验：图书编号和名称不能为空
    if (ui->editId->text().isEmpty() || ui->editName->text().isEmpty()) {
        return; // 校验不通过则不关闭对话框
    }
    // 校验通过，关闭对话框并返回Accepted
    accept();
}
