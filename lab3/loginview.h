#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

private slots:
    void on_btSignIn_clicked();

private:
    Ui::LoginView *ui;

private slots:
    void on_btSignUp_clicked();  // 添加注册按钮点击事件

signals:
    void loginSuccess();
    void loginFailed();
    void goSignUpView();  // 新增：跳转到注册页面信号
};

#endif // LOGINVIEW_H
