#include "signup.h"
#include "ui_signup.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QUuid>
#include "loghelper.h"

SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);

    // 设置密码输入框为密码模式
    ui->dbEditPassWord->setEchoMode(QLineEdit::Password);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()  // 创建按钮
{
    // 获取用户输入
    QString fullName = ui->dbEditFullName->text().trimmed();
    QString userName = ui->dbEditUserName->text().trimmed();
    QString password = ui->dbEditPassWord->text().trimmed();WASDAWDAWDAWS

    // 输入验证
    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "警告", "全名不能为空！");
        return;
    }
    if (userName.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名不能为空！");
        return;
    }
    if (password.isEmpty()) {
        QMessageBox::warning(this, "警告", "密码不能为空！");
        return;
    }

    // 记录注册尝试日志
    LogHelper::getInstance().writeLog(QString("用户注册尝试：用户名=%1，全名=%2").arg(userName).arg(fullName), "INFO");

    // 检查用户名是否已存在
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM user WHERE username = :USERNAME");
    checkQuery.bindValue(":USERNAME", userName);

    if (!checkQuery.exec()) {
        QString errorMsg = checkQuery.lastError().text();
        LogHelper::getInstance().writeLog(QString("检查用户名存在失败：%1").arg(errorMsg), "ERROR");
        QMessageBox::critical(this, "错误", "检查用户名失败：" + errorMsg);
        return;
    }

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "警告", "用户名已存在，请选择其他用户名！");
        LogHelper::getInstance().writeLog(QString("用户注册失败：用户名已存在=%1").arg(userName), "WARN");
        return;
    }

    // 生成唯一ID（使用QUuid生成UUID）
    QString userId = QUuid::createUuid().toString(QUuid::WithoutBraces);

    // 插入新用户记录
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO user (ID, FULLNAME, USERNAME, PASSWORD) VALUES (:ID, :FULLNAME, :USERNAME, :PASSWORD)");
    insertQuery.bindValue(":ID", userId);
    insertQuery.bindValue(":FULLNAME", fullName);
    insertQuery.bindValue(":USERNAME", userName);
    insertQuery.bindValue(":PASSWORD", password);

    if (insertQuery.exec()) {
        LogHelper::getInstance().writeLog(QString("用户注册成功：用户ID=%1，用户名=%2，全名=%3").arg(userId).arg(userName).arg(fullName), "INFO");
        QMessageBox::information(this, "成功", "用户创建成功！\n您的用户ID为：" + userId);
        emit goBackToLogin();  // 创建成功后返回登录界面
    } else {
        QString errorMsg = insertQuery.lastError().text();
        LogHelper::getInstance().writeLog(QString("用户注册失败：用户名=%1，错误信息=%2").arg(userName).arg(errorMsg), "ERROR");
        QMessageBox::critical(this, "错误", "用户创建失败：" + errorMsg);
    }
}

void SignUp::on_pushButton_2_clicked()  // 取消按钮
{
    LogHelper::getInstance().writeLog("取消用户注册", "INFO");
    emit goBackToLogin();  // 返回登录界面
}
