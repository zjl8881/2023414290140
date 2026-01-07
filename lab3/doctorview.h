#ifndef DOCTORVIEW_H
#define DOCTORVIEW_H

#include <QWidget>
#include "idatabase.h"
#include "doctoreditview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DoctorView; }
QT_END_NAMESPACE

class DoctorView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorView(QWidget *parent = nullptr);
    ~DoctorView();

private slots:
    void on_btAdd_clicked();      // 添加按钮
    void on_btEdit_clicked();     // 修改按钮
    void on_btDelete_clicked();   // 删除按钮
    void on_btSearch_clicked();   // 查找按钮
    void on_btReport_clicked();

signals:
    void goDoctorEditView(int idx);  // 跳转到医生编辑页面的信号（和患者管理一致）

private:
    Ui::DoctorView *ui;
    IDatabase &m_db;
    QString m_originalFilter;  // 原始过滤器（用于清空搜索）
};

#endif // DOCTORVIEW_H
