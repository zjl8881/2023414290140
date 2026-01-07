#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_pushButton_clicked();  // 创建按钮
    void on_pushButton_2_clicked(); // 取消按钮

private:
    Ui::SignUp *ui;

signals:
    void goBackToLogin();  // 返回登录界面信号
};

#endif // SIGNUP_H
