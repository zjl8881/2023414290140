#include "signup.h"
#include "ui_signup.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);

    // 设置密码字段为密码模式
    ui->dbEditPassWord->setEchoMode(QLineEdit::Password);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()  // UI中的"创建"按钮
{
    QString fullname = ui->dbEditFullName->text();
    QString username = ui->dbEditUserName->text();
    QString password = ui->dbEditPassWord->text();

    if (fullname.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "请填写所有必填项！");
        return;
    }

    if (!IDatabase::getInstance().openDatabase()) {
        QMessageBox::critical(this, "错误", "数据库连接失败！");
        return;
    }

    QSqlDatabase db = IDatabase::getInstance().getDatabase();
    QSqlQuery query(db);

    query.prepare("INSERT INTO user (FULLNAME, USERNAME, PASSWORD) "
                  "VALUES (:fullname, :username, :password)");
    query.bindValue(":fullname", fullname);
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        QMessageBox::information(this, "成功", "注册成功！");
        emit goLoginView();
    } else {
        if (query.lastError().text().contains("UNIQUE constraint failed")) {
            QMessageBox::warning(this, "注册失败", "用户名已存在！");
        } else {
            QMessageBox::critical(this, "注册失败", "注册失败：" + query.lastError().text());
        }
    }
}

void SignUp::on_pushButton_2_clicked()  // UI中的"取消"按钮
{
    emit goLoginView();
}
