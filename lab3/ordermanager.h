#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QTimer>
#include "dbhelper.h"

namespace Ui {
class OrderManager;
}

class OrderManager : public QDialog
{
    Q_OBJECT

public:
    explicit OrderManager(QWidget *parent = nullptr);
    ~OrderManager();

private slots:
    // 按钮槽函数
    void on_btnSearch_clicked();
    void on_btnResetFilter_clicked();
    void on_btnClose_clicked();
    
    // 订单选择变化
    void on_tableView_clicked(const QModelIndex &index);
    void on_tableView_doubleClicked(const QModelIndex &index);
    
    // 日期范围变化
    void on_deStartDate_dateChanged(const QDate &date);
    void on_deEndDate_dateChanged(const QDate &date);
    
    // 搜索框输入变化
    void on_leOrderSearch_textChanged(const QString &arg1);

private:
    Ui::OrderManager *ui;
    
    // 数据模型
    QSqlQueryModel *orderModel;
    QSortFilterProxyModel *proxyModel;
    
    // 定时器，用于实时刷新数据
    QTimer *refreshTimer;
    
    // 初始化UI
    void initUI();
    
    // 初始化数据模型
    void initModels();
    
    // 初始化信号与槽连接
    void initConnections();
    
    // 加载订单数据
    void loadOrders();
    
    // 加载房型数据
    void loadRoomTypes();
    
    // 应用筛选条件
    void applyFilters();
    
    // 显示订单详情
    void showOrderDetails(int orderId);
};

#endif // ORDERMANAGER_H
