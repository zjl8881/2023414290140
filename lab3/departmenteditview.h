#ifndef DEPARTMENTEDITVIEW_H
#define DEPARTMENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "idatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DepartmentEditView;
}
QT_END_NAMESPACE


class DepartmentEditView : public QWidget  // 继承QWidget而非QDialog
{
    Q_OBJECT

public:
    explicit DepartmentEditView(QWidget *parent = nullptr, int index = -1);
    ~DepartmentEditView();

private slots:
    void on_pushButton_3_clicked();  // 保存按钮
    void on_pushButton_4_clicked();  // 取消按钮
    void on_btReport_clicked();
    void handleReportFinished(bool success, QString message);

private:
    Ui::DepartmentEditView *ui;
    IDatabase &m_db;
    int m_editIndex;
    QDataWidgetMapper *dataMapper;   // 数据映射器

    void loadDepartmentData();  // 加载选中科室数据
    bool validateInput();       // 输入验证

signals:
    void goPreviousView();  // 返回上一页信号
};

#endif // DEPARTMENTEDITVIEW_H
