#ifndef DEPARTMENTEDITVIEW_H
#define DEPARTMENTEDITVIEW_H

#include <QWidget>  // 替换QDialog为QWidget
#include <QDataWidgetMapper>  // 新增数据映射器（和PatientEditView一致）
#include "idatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DepartmentEditView; }
QT_END_NAMESPACE

// 移除EditType枚举（后续通过行索引区分新增/编辑：-1=新增，>=0=编辑）
class DepartmentEditView : public QWidget  // 继承QWidget而非QDialog
{
    Q_OBJECT

public:
    // 构造函数对齐PatientEditView：parent + 编辑行索引
    explicit DepartmentEditView(QWidget *parent = nullptr, int index = -1);
    ~DepartmentEditView();

private slots:
    void on_pushButton_3_clicked();  // 保存按钮
    void on_pushButton_4_clicked();  // 取消按钮

private:
    Ui::DepartmentEditView *ui;
    IDatabase &m_db;
    int m_editIndex;  // 编辑行索引：-1=新增，>=0=编辑
    QDataWidgetMapper *dataMapper;   // 数据映射器（和PatientEditView一致）

    void loadDepartmentData();  // 加载选中科室数据
    bool validateInput();       // 输入验证

signals:
    void goPreviousView();  // 返回上一页信号（和PatientEditView一致）
};

#endif // DEPARTMENTEDITVIEW_H
