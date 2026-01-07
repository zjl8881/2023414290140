#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"
#include <QMessageBox>

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignIn_clicked()  // 按钮名称改为 btSignIn
{
    QString username = ui->inputUserName->text();
    QString password = ui->inputUserPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空！");
        return;
    }

    if (IDatabase::getInstance().userLogin(username, password)) {
        emit goWelcomeView();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
    }
}

void LoginView::on_btSignUp_clicked()  // 按钮名称改为 btSignUp
{
    emit goSignUpView();
}
