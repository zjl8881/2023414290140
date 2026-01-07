#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QWidget>

namespace Ui {
class DoctorEditView;
}

class DoctorEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditView(int rowNo, QWidget *parent = nullptr);
    ~DoctorEditView();

private slots:
    // 更新槽函数名称
    void on_pushButton_clicked();   // 保存按钮
    void on_pushButton_2_clicked(); // 取消按钮

private:
    Ui::DoctorEditView *ui;
    int m_rowNo;
};

#endif // DOCTOREDITVIEW_H
