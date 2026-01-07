#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"
#include "loghelper.h"

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);

    // 设置密码输入框为密码模式
    ui->inputUserPassword->setEchoMode(QLineEdit::Password);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignIn_clicked()
{
    QString userName = ui->inputUserName->text().trimmed();
    QString password = ui->inputUserPassword->text().trimmed();

    // 记录登录尝试日志
    LogHelper::getInstance().writeLog(QString("用户登录尝试：用户名=%1").arg(userName), "INFO");

    QString status = IDatabase::getInstance().userLogin(userName, password);

    if(status == "loginOk"){
        // 登录成功日志
        LogHelper::getInstance().writeLog(QString("用户登录成功：用户名=%1").arg(userName), "INFO");
        emit loginSuccess();
    } else {
        // 登录失败日志
        QString errMsg = status == "wrongPassword" ? "密码错误" : "用户名不存在";
        LogHelper::getInstance().writeLog(QString("用户登录失败：用户名=%1，原因=%2").arg(userName, errMsg), "ERROR");
        emit loginFailed();
    }
}

void LoginView::on_btSignUp_clicked()
{
    LogHelper::getInstance().writeLog("跳转到用户注册页面", "INFO");
    emit goSignUpView();  // 发射跳转到注册页面的信号
}
