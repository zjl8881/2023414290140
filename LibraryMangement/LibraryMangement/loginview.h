#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>

class LoginView : public QWidget {
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView() = default;

signals:
    void loginSuccess();

private slots:
    void on_btSignIn_clicked();

private:
    // 纯代码创建控件（替代ui文件）
    QLineEdit* inputUserName;
    QLineEdit* inputUserPassword;
    QPushButton* btSignIn;
    QFormLayout* mainLayout;
};

#endif // LOGINVIEW_H
