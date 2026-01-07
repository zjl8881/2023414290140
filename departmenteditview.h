#ifndef DEPARTMENTEDITVIEW_H
#define DEPARTMENTEDITVIEW_H

#include <QWidget>

namespace Ui {
class DepartmentEditView;
}

class DepartmentEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentEditView(int rowNo, QWidget *parent = nullptr);
    ~DepartmentEditView();

private slots:
    // 更新槽函数名称
    void on_pushButton_3_clicked();  // 保存按钮
    void on_pushButton_4_clicked();  // 取消按钮

private:
    Ui::DepartmentEditView *ui;
    int m_rowNo;
};

#endif // DEPARTMENTEDITVIEW_H
