#ifndef ROOMTYPEMANAGER_H
#define ROOMTYPEMANAGER_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTimer>
#include "dbhelper.h"

namespace Ui {
class RoomTypeManager;
}

class RoomTypeManager : public QDialog
{
    Q_OBJECT

public:
    explicit RoomTypeManager(QWidget *parent = nullptr);
    ~RoomTypeManager();

private slots:
    // 按钮槽函数
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_btnRefresh_clicked();
    void on_btnClose_clicked();
    
    // 表格双击事件
    void on_tableView_doubleClicked(const QModelIndex &index);
    
    // 搜索功能
    void on_btnSearch_clicked();
    void on_leSearch_textChanged(const QString &arg1);

private:
    Ui::RoomTypeManager *ui;
    
    // 数据模型
    QSqlTableModel *model;
    
    // 定时器，用于实时刷新数据
    QTimer *refreshTimer;
    
    // 初始化UI
    void initUI();
    
    // 初始化数据模型
    void initModel();
    
    // 初始化信号与槽连接
    void initConnections();
    
    // 清空表单
    void clearForm();
    
    // 显示选中行的数据到表单
    void showDataToForm(const QModelIndex &index);
};

#endif // ROOMTYPEMANAGER_H
