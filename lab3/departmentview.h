#ifndef DEPARTMENTVIEW_H
#define DEPARTMENTVIEW_H

#include <QWidget>
#include "idatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DepartmentView; }
QT_END_NAMESPACE

class DepartmentView : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentView(QWidget *parent = nullptr);
    ~DepartmentView();

private slots:
    void on_btAdd_clicked();
    void on_btEdit_clicked();
    void on_btDelete_clicked();
    void on_btSearch_clicked();
    void handleReportFinished(bool success, QString message);
    
    void on_btReport_clicked();

signals:
    void goDepartmentEditView(int idx);  // 新增：跳转编辑页信号（对齐PatientView）

private:
    Ui::DepartmentView *ui;
    IDatabase &m_db;
    QString m_originalFilter;
};

#endif // DEPARTMENTVIEW_H
