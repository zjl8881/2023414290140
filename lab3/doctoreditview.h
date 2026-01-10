// doctoreditview.h
#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper> // 必须包含头文件
#include "IDatabase.h"

namespace Ui {
class DoctorEditView;
}

class DoctorEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditView(QWidget *parent = nullptr, int index = 0);awdawdawd
    ~DoctorEditView();

signals:
    void goPreviousView(); // 返回上一页的信号（匹配PatientEditView）

private slots:
    void on_pushButton_clicked(); // 保存按钮点击事件
    void on_pushButton_2_clicked(); // 取消按钮点击事件
    void on_btReport_clicked();

private:
    Ui::DoctorEditView *ui;
    int m_editIndex; // 当前编辑行索引
    QDataWidgetMapper *dataMapper; // 数据映射器（核心：绑定UI和数据库）
      bool validateInput();
};

#endif // DOCTOREDITVIEW_H
