#include "LoginView.h"
#include "IDatabase.h"
#include <QMessageBox>
#include <QFont>

LoginView::LoginView(QWidget *parent) : QWidget(parent) {
    // 1. 设置界面基础属性
    setWindowTitle("用户登录");
    setFixedSize(400, 250); // 固定窗口大小

    // 2. 创建控件并设置属性
    QLabel* titleLabel = new QLabel("医院诊疗系统登录", this);
    QFont titleFont;
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    inputUserName = new QLineEdit(this);
    inputUserName->setPlaceholderText("请输入用户名");
    inputUserName->setFixedHeight(35);

    inputUserPassword = new QLineEdit(this);
    inputUserPassword->setPlaceholderText("请输入密码");
    inputUserPassword->setEchoMode(QLineEdit::Password); // 密码隐藏
    inputUserPassword->setFixedHeight(35);

    btSignIn = new QPushButton("登录", this);
    btSignIn->setFixedSize(120, 40);
    btSignIn->setStyleSheet("background-color:#2E86AB; color:white; border-radius:5px;");

    // 3. 创建布局并添加控件
    mainLayout = new QVBoxLayout(this);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(20);

    // 表单布局（用于用户名/密码行）
    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("用户名：", inputUserName);
    formLayout->addRow("密  码：", inputUserPassword);
    formLayout->setContentsMargins(40, 0, 40, 0);
    mainLayout->addLayout(formLayout);

    mainLayout->addSpacing(25);
    mainLayout->addWidget(btSignIn, 0, Qt::AlignCenter); // 按钮居中
    mainLayout->addSpacing(30);

    // 4. 绑定信号槽
    connect(btSignIn, &QPushButton::clicked, this, &LoginView::on_btSignIn_clicked);
}

void LoginView::on_btSignIn_clicked() {
    QString userName = inputUserName->text().trimmed();
    QString password = inputUserPassword->text().trimmed();

    if (userName.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名或密码不能为空！");
        return;
    }

    QString status = IDatabase::getInstance().userLogin(userName, password);
    if (status == "loginOk") emit loginSuccess();
    else if (status == "wrongPassword") QMessageBox::warning(this, "警告", "密码错误！");
    else if (status == "wrongUsername") QMessageBox::warning(this, "警告", "用户名不存在！");
}
