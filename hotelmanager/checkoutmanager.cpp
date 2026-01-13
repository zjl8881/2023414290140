#include "checkoutmanager.h"
#include "ui_checkoutmanager.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QTextEdit>

CheckOutManager::CheckOutManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckOutManager),
    orderModel(nullptr),
    orderDetailModel(nullptr),
    currentOrderId(-1)
{
    ui->setupUi(this);
    initUI();
    initModels();
    initConnections();
}

CheckOutManager::~CheckOutManager()
{
    delete ui;
    if (orderModel) delete orderModel;
    if (orderDetailModel) delete orderDetailModel;
}

void CheckOutManager::initUI()
{
    // 设置窗口标题
    setWindowTitle("客户退房结算");
    
    // 设置窗口大小
    resize(800, 600);
    
    // 初始化搜索框
    ui->leOrderSearch->setPlaceholderText("输入订单号、客户姓名或房间号搜索...");
    
    // 初始化支付方式下拉框
    ui->cmbPaymentMethod->addItem("现金", "现金");
    ui->cmbPaymentMethod->addItem("微信支付", "微信支付");
    ui->cmbPaymentMethod->addItem("支付宝", "支付宝");
    ui->cmbPaymentMethod->addItem("银行卡", "银行卡");
    
    // 初始化日期控件
    ui->deActualCheckOut->setDate(QDate::currentDate());
    
    // 初始化金额显示
    ui->leTotalAmount->setText("0.00");
    ui->lePaymentAmount->setText("0.00");
    ui->leChange->setText("0.00");
    
    // 禁用结算按钮，直到选择订单
    ui->btnCheckOut->setEnabled(false);
}

void CheckOutManager::initModels()
{
    // 创建订单数据模型
    orderModel = new QSqlQueryModel(this);
    ui->tableView->setModel(orderModel);
    
    // 设置订单表格列名
    orderModel->setHeaderData(0, Qt::Horizontal, "订单ID");
    orderModel->setHeaderData(1, Qt::Horizontal, "客户姓名");
    orderModel->setHeaderData(2, Qt::Horizontal, "房间号");
    orderModel->setHeaderData(3, Qt::Horizontal, "入住日期");
    orderModel->setHeaderData(4, Qt::Horizontal, "退房日期");
    orderModel->setHeaderData(5, Qt::Horizontal, "订单状态");
    orderModel->setHeaderData(6, Qt::Horizontal, "总金额");
    
    // 创建订单详情数据模型
    orderDetailModel = new QSqlQueryModel(this);
    ui->tableView_2->setModel(orderDetailModel);
    
    // 设置订单详情表格列名
    orderDetailModel->setHeaderData(0, Qt::Horizontal, "项目");
    orderDetailModel->setHeaderData(1, Qt::Horizontal, "金额(元)");
    
    // 加载待结算订单
    loadPendingOrders();
}

void CheckOutManager::initConnections()
{
    // 这里可以添加额外的信号与槽连接
}

void CheckOutManager::clearForm()
{
    // 清空搜索框
    ui->leOrderSearch->clear();
    
    // 清空订单详情
    ui->leCustomerName->clear();
    ui->leRoomNumber->clear();
    ui->leCheckInDate->clear();
    ui->leCheckOutDate->clear();
    ui->deActualCheckOut->setDate(QDate::currentDate());
    ui->leTotalAmount->setText("0.00");
    ui->lePaymentAmount->setText("0.00");
    ui->leChange->setText("0.00");
    ui->cmbPaymentMethod->setCurrentIndex(0);
    ui->teNotes->clear();
    
    // 清空当前订单ID
    currentOrderId = -1;
    
    // 禁用结算按钮
    ui->btnCheckOut->setEnabled(false);
}

void CheckOutManager::loadPendingOrders()
{
    QString sql = "SELECT o.order_id, c.name, r.room_number, o.check_in_date, o.check_out_date, o.status, o.total_amount "
                 "FROM order_info o "
                 "JOIN customer c ON o.customer_id = c.customer_id "
                 "JOIN room r ON o.room_id = r.room_id "
                 "WHERE o.status IN ('已预订', '已入住') "
                 "ORDER BY o.order_id DESC";
    
    orderModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    
    if (orderModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "加载待结算订单失败: " + orderModel->lastError().text());
        return;
    }
    
    // 调整列宽
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void CheckOutManager::showOrderDetails(int orderId)
{
    if (orderId <= 0) {
        return;
    }
    
    // 获取订单详情
    QString sql = QString("SELECT o.order_id, c.name, c.id_card, c.phone, r.room_number, rt.name as room_type_name, "
                         "o.check_in_date, o.check_out_date, o.total_amount, r.type_id "
                         "FROM order_info o "
                         "JOIN customer c ON o.customer_id = c.customer_id "
                         "JOIN room r ON o.room_id = r.room_id "
                         "JOIN room_type rt ON r.type_id = rt.type_id "
                         "WHERE o.order_id = %1").arg(orderId);
    
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    if (!query.exec(sql)) {
        QMessageBox::critical(this, "错误", "获取订单详情失败: " + query.lastError().text());
        return;
    }
    
    if (query.next()) {
        // 显示基本信息
        ui->leCustomerName->setText(query.value("name").toString());
        ui->leRoomNumber->setText(query.value("room_number").toString());
        ui->leCheckInDate->setText(query.value("check_in_date").toString());
        ui->leCheckOutDate->setText(query.value("check_out_date").toString());
        ui->leTotalAmount->setText(QString("%1").arg(query.value("total_amount").toDouble(), 0, 'f', 2));
        ui->lePaymentAmount->setText(ui->leTotalAmount->text());
        
        // 显示订单详情表格
        sql = QString("SELECT '房费' as item, total_amount as amount FROM order_info WHERE order_id = %1").arg(orderId);
        orderDetailModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
        
        if (orderDetailModel->lastError().isValid()) {
            QMessageBox::critical(this, "错误", "加载订单详情失败: " + orderDetailModel->lastError().text());
            return;
        }
        
        // 调整列宽
        ui->tableView_2->resizeColumnsToContents();
        
        // 启用结算按钮
        ui->btnCheckOut->setEnabled(true);
        
        // 保存当前订单ID
        currentOrderId = orderId;
    }
}

void CheckOutManager::calculateActualAmount()
{
    // 这里可以根据实际入住天数重新计算金额
    // 目前使用订单中的总金额
    double totalAmount = ui->leTotalAmount->text().toDouble();
    double paymentAmount = ui->lePaymentAmount->text().toDouble();
    double change = paymentAmount - totalAmount;
    
    ui->leChange->setText(QString("%1").arg(change, 0, 'f', 2));
}

bool CheckOutManager::validateForm()
{
    // 验证是否选择了订单
    if (currentOrderId <= 0) {
        QMessageBox::warning(this, "警告", "请先选择要结算的订单");
        return false;
    }
    
    // 验证支付金额
    double totalAmount = ui->leTotalAmount->text().toDouble();
    double paymentAmount = ui->lePaymentAmount->text().toDouble();
    
    if (paymentAmount < totalAmount) {
        QMessageBox::warning(this, "警告", "支付金额不能小于总金额");
        ui->lePaymentAmount->setFocus();
        return false;
    }
    
    return true;
}

bool CheckOutManager::processCheckOut()
{
    // 验证表单
    if (!validateForm()) {
        return false;
    }
    
    // 开始事务
    if (!DBHelper::getInstance()->beginTransaction()) {
        QMessageBox::critical(this, "错误", "无法开始事务");
        return false;
    }
    
    try {
        QSqlQuery query(DBHelper::getInstance()->getDatabase());
        
        // 1. 获取订单信息
        int roomId = -1;
        int typeId = -1;
        
        query.prepare("SELECT room_id FROM order_info WHERE order_id = :order_id");
        query.bindValue(":order_id", currentOrderId);
        
        if (!query.exec() || !query.next()) {
            throw QString("获取订单信息失败: " + query.lastError().text());
        }
        
        roomId = query.value(0).toInt();
        
        // 2. 获取房型ID
        query.prepare("SELECT type_id FROM room WHERE room_id = :room_id");
        query.bindValue(":room_id", roomId);
        
        if (!query.exec() || !query.next()) {
            throw QString("获取房型信息失败: " + query.lastError().text());
        }
        
        typeId = query.value(0).toInt();
        
        // 3. 更新订单状态
        query.prepare("UPDATE order_info SET status = '已结算', actual_check_out_date = :actual_check_out_date "
                      "WHERE order_id = :order_id");
        query.bindValue(":actual_check_out_date", ui->deActualCheckOut->date().toString("yyyy-MM-dd"));
        query.bindValue(":order_id", currentOrderId);
        
        if (!query.exec()) {
            throw QString("更新订单状态失败: " + query.lastError().text());
        }
        
        // 4. 更新房间状态为空闲
        query.prepare("UPDATE room SET status = '空闲' WHERE room_id = :room_id");
        query.bindValue(":room_id", roomId);
        
        if (!query.exec()) {
            throw QString("更新房间状态失败: " + query.lastError().text());
        }
        
        // 5. 更新房型可用数量
        query.prepare("UPDATE room_type SET available_rooms = available_rooms + 1 WHERE type_id = :type_id");
        query.bindValue(":type_id", typeId);
        
        if (!query.exec()) {
            throw QString("更新房型可用数量失败: " + query.lastError().text());
        }
        
        // 6. 插入结算记录
        query.prepare("INSERT INTO settlement (order_id, payment_method, payment_amount, settlement_date, notes) "
                      "VALUES (:order_id, :payment_method, :payment_amount, :settlement_date, :notes)");
        query.bindValue(":order_id", currentOrderId);
        query.bindValue(":payment_method", ui->cmbPaymentMethod->currentData().toString());
        query.bindValue(":payment_amount", ui->lePaymentAmount->text().toDouble());
        query.bindValue(":settlement_date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":notes", ui->teNotes->toPlainText().trimmed());
        
        if (!query.exec()) {
            throw QString("插入结算记录失败: " + query.lastError().text());
        }
        
        // 提交事务
        if (!DBHelper::getInstance()->commitTransaction()) {
            throw QString("提交事务失败");
        }
        
        QMessageBox::information(this, "成功", "退房结算成功");
        
        // 生成结算凭证
        generateSettlementVoucher();
        
        return true;
        
    } catch (const QString &error) {
        // 回滚事务
        DBHelper::getInstance()->rollbackTransaction();
        QMessageBox::critical(this, "错误", error);
        return false;
    }
}

void CheckOutManager::generateSettlementVoucher()
{
    // 创建结算凭证对话框
    QDialog *voucherDialog = new QDialog(this);
    voucherDialog->setWindowTitle("结算凭证");
    voucherDialog->resize(500, 400);
    
    // 创建文本编辑框显示结算凭证
    QTextEdit *textEdit = new QTextEdit(voucherDialog);
    textEdit->setReadOnly(true);
    
    // 构建结算凭证内容
    QString voucher = "==================== 酒店结算凭证 ====================";
    voucher += "\n\n订单号: " + QString::number(currentOrderId);
    voucher += "\n客户姓名: " + ui->leCustomerName->text();
    voucher += "\n房间号: " + ui->leRoomNumber->text();
    voucher += "\n入住日期: " + ui->leCheckInDate->text();
    voucher += "\n退房日期: " + ui->leCheckOutDate->text();
    voucher += "\n实际退房日期: " + ui->deActualCheckOut->date().toString("yyyy-MM-dd");
    voucher += "\n总金额: " + ui->leTotalAmount->text() + " 元";
    voucher += "\n支付方式: " + ui->cmbPaymentMethod->currentText();
    voucher += "\n支付金额: " + ui->lePaymentAmount->text() + " 元";
    voucher += "\n找零: " + ui->leChange->text() + " 元";
    voucher += "\n结算日期: " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    
    if (!ui->teNotes->toPlainText().trimmed().isEmpty()) {
        voucher += "\n备注: " + ui->teNotes->toPlainText().trimmed();
    }
    
    voucher += "\n\n==================== 谢谢惠顾 ====================";
    
    textEdit->setPlainText(voucher);
    
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(voucherDialog);
    layout->addWidget(textEdit);
    voucherDialog->setLayout(layout);
    
    // 显示结算凭证
    voucherDialog->exec();
    
    delete voucherDialog;
}

// 按钮槽函数实现
void CheckOutManager::on_btnSearchOrder_clicked()
{
    QString searchText = ui->leOrderSearch->text().trimmed();
    QString sql;
    
    if (searchText.isEmpty()) {
        // 加载所有待结算订单
        loadPendingOrders();
    } else {
        // 根据搜索条件查询订单
        sql = QString("SELECT o.order_id, c.name, r.room_number, o.check_in_date, o.check_out_date, o.status, o.total_amount "
                     "FROM order_info o "
                     "JOIN customer c ON o.customer_id = c.customer_id "
                     "JOIN room r ON o.room_id = r.room_id "
                     "WHERE (o.order_id = %1 OR c.name LIKE '%%1%' OR r.room_number LIKE '%%1%') AND o.status IN ('已预订', '已入住') "
                     "ORDER BY o.order_id DESC").arg(searchText);
        
        orderModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
        
        if (orderModel->lastError().isValid()) {
            QMessageBox::critical(this, "错误", "搜索订单失败: " + orderModel->lastError().text());
            return;
        }
        
        // 调整列宽
        ui->tableView->resizeColumnsToContents();
    }
}

void CheckOutManager::on_btnCheckOut_clicked()
{
    // 处理退房结算
    if (processCheckOut()) {
        // 清空表单
        clearForm();
        
        // 刷新订单列表
        loadPendingOrders();
    }
}

void CheckOutManager::on_btnCancel_clicked()
{
    close();
}

// 订单选择变化
void CheckOutManager::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int orderId = orderModel->record(index.row()).value(0).toInt();
        showOrderDetails(orderId);
    }
}

void CheckOutManager::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int orderId = orderModel->record(index.row()).value(0).toInt();
        showOrderDetails(orderId);
    }
}

// 支付方式选择变化
void CheckOutManager::on_cmbPaymentMethod_currentIndexChanged(int index)
{
    // 支付方式变化时可以添加额外逻辑
    Q_UNUSED(index);
}

// 搜索框输入变化
void CheckOutManager::on_leOrderSearch_textChanged(const QString &arg1)
{
    QString searchText = arg1.trimmed();
    if (searchText.isEmpty()) {
        loadPendingOrders();
    }
    // 实时搜索可以在这里实现，或者保留为点击搜索按钮触发
}
