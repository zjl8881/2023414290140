#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H
// 关键修改1：将<QWidget>替换为<QDialog>
#include <QDialog>
#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddBookDialog; }
QT_END_NAMESPACE

// 关键修改2：将public QWidget改为public QDialog
class AddBookDialog : public QDialog
{
    Q_OBJECT  // 信号槽机制必须的宏，Qt Creator选QWidget时会自动生成，保留即可

public:
    // 构造函数参数parent默认值保留，符合Qt窗口类规范
    AddBookDialog(QWidget *parent = nullptr);
    ~AddBookDialog();

    // 获取用户输入的图书信息的接口函数
    Book getBookInfo() const;

private slots:
    // 确认按钮点击的槽函数
    void onBtnOkClicked();

private:
    Ui::AddBookDialog *ui;
};

#endif // ADDBOOKDIALOG_H
