#ifndef CHECKOUTMANAGER_H
#define CHECKOUTMANAGER_H

#include <QDialog>
#include <QSqlQueryModel>
#include "dbhelper.h"

namespace Ui {
class CheckOutManager;
}

class CheckOutManager : public QDialog
{
    Q_OBJECT

public:
    explicit CheckOutManager(QWidget *parent = nullptr);
    ~CheckOutManager();

private slots:
    // 按钮槽函数
    void on_btnSearchOrder_clicked();
    void on_btnCheckOut_clicked();
    void on_btnCancel_clicked();
    
    // 订单选择变化
    void on_tableView_clicked(const QModelIndex &index);
    void on_tableView_doubleClicked(const QModelIndex &index);
    
    // 支付方式选择变化
    void on_cmbPaymentMethod_currentIndexChanged(int index);
    
    // 搜索框输入变化
    void on_leOrderSearch_textChanged(const QString &arg1);

private:
    Ui::CheckOutManager *ui;
    
    // 数据模型
    QSqlQueryModel *orderModel;
    QSqlQueryModel *orderDetailModel;
    
    // 当前选中的订单ID
    int currentOrderId;
    
    // 初始化UI
    void initUI();
    
    // 初始化数据模型
    void initModels();
    
    // 初始化信号与槽连接
    void initConnections();
    
    // 清空表单
    void clearForm();
    
    // 加载待结算订单
    void loadPendingOrders();
    
    // 显示订单详情
    void showOrderDetails(int orderId);
    
    // 计算实际消费金额
    void calculateActualAmount();
    
    // 验证表单数据
    bool validateForm();
    
    // 处理退房结算
    bool processCheckOut();
    
    // 生成结算凭证
    void generateSettlementVoucher();
};

#endif // CHECKOUTMANAGER_H
