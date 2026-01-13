#include "ordermanager.h"
#include "ui_ordermanager.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QTextEdit>

OrderManager::OrderManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderManager),
    orderModel(nullptr),
    proxyModel(nullptr),
    refreshTimer(nullptr)
{
    ui->setupUi(this);
    initUI();
    initModels();
    initConnections();
    
    // 初始化并启动定时器（每10秒刷新一次）
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, [=]() {
        // 保存当前筛选条件
        bool hasFilter = !ui->leOrderSearch->text().trimmed().isEmpty() ||
                         ui->cmbOrderStatus->currentIndex() > 0 ||
                         ui->cmbRoomType->currentIndex() > 0;
        
        if (hasFilter) {
            // 应用现有筛选条件
            applyFilters();
        } else {
            // 加载所有订单
            loadOrders();
        }
    });
    refreshTimer->start(10000);
}

OrderManager::~OrderManager()
{
    delete ui;
    if (orderModel) delete orderModel;
    if (proxyModel) delete proxyModel;
    if (refreshTimer) delete refreshTimer;
}

void OrderManager::initUI()
{
    // 设置窗口标题
    setWindowTitle("订单管理");
    
    // 设置窗口大小
    resize(800, 600);
    
    // 初始化搜索框
    ui->leOrderSearch->setPlaceholderText("输入订单号、客户姓名或房间号搜索...");
    
    // 初始化日期范围
    ui->deStartDate->setDate(QDate::currentDate().addMonths(-1));
    ui->deEndDate->setDate(QDate::currentDate());
    
    // 初始化订单状态下拉框
    ui->cmbOrderStatus->addItem("全部", "");
    ui->cmbOrderStatus->addItem("已预订", "已预订");
    ui->cmbOrderStatus->addItem("已入住", "已入住");
    ui->cmbOrderStatus->addItem("已结算", "已结算");
    ui->cmbOrderStatus->addItem("已取消", "已取消");
    
    // 初始化房型下拉框
    loadRoomTypes();
}

void OrderManager::initModels()
{
    // 创建订单数据模型
    orderModel = new QSqlQueryModel(this);
    
    // 创建代理模型用于排序和筛选
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(orderModel);
    proxyModel->setDynamicSortFilter(true);
    
    // 设置表格视图
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // 加载订单数据
    loadOrders();
}

void OrderManager::initConnections()
{
    // 这里可以添加额外的信号与槽连接
}

void OrderManager::loadOrders()
{
    QString sql = "SELECT o.order_id, c.name as customer_name, r.room_number, "
                 "o.check_in_date, o.check_out_date, o.actual_check_out_date, "
                 "o.status, o.total_amount, rt.name as room_type_name "
                 "FROM order_info o "
                 "JOIN customer c ON o.customer_id = c.customer_id "
                 "JOIN room r ON o.room_id = r.room_id "
                 "JOIN room_type rt ON r.type_id = rt.type_id "
                 "ORDER BY o.order_id DESC";
    
    orderModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    
    if (orderModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "加载订单数据失败: " + orderModel->lastError().text());
        return;
    }
    
    // 设置列名
    orderModel->setHeaderData(0, Qt::Horizontal, "订单ID");
    orderModel->setHeaderData(1, Qt::Horizontal, "客户姓名");
    orderModel->setHeaderData(2, Qt::Horizontal, "房间号");
    orderModel->setHeaderData(3, Qt::Horizontal, "入住日期");
    orderModel->setHeaderData(4, Qt::Horizontal, "退房日期");
    orderModel->setHeaderData(5, Qt::Horizontal, "实际退房日期");
    orderModel->setHeaderData(6, Qt::Horizontal, "订单状态");
    orderModel->setHeaderData(7, Qt::Horizontal, "总金额(元)");
    orderModel->setHeaderData(8, Qt::Horizontal, "房型");
    
    // 调整列宽
    ui->tableView->resizeColumnsToContents();
}

void OrderManager::loadRoomTypes()
{
    // 清空房型下拉框
    ui->cmbRoomType->clear();
    ui->cmbRoomType->addItem("全部", "");
    
    // 加载房型数据
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    query.exec("SELECT type_id, name FROM room_type ORDER BY name");
    
    while (query.next()) {
        ui->cmbRoomType->addItem(query.value(1).toString(), query.value(0).toInt());
    }
}

void OrderManager::applyFilters()
{
    // 构建SQL查询
    QString sql = "SELECT o.order_id, c.name as customer_name, r.room_number, "
                 "o.check_in_date, o.check_out_date, o.actual_check_out_date, "
                 "o.status, o.total_amount, rt.name as room_type_name "
                 "FROM order_info o "
                 "JOIN customer c ON o.customer_id = c.customer_id "
                 "JOIN room r ON o.room_id = r.room_id "
                 "JOIN room_type rt ON r.type_id = rt.type_id "
                 "WHERE 1=1 ";
    
    // 添加搜索条件
    QString searchText = ui->leOrderSearch->text().trimmed();
    if (!searchText.isEmpty()) {
        sql += QString(" AND (o.order_id = %1 OR c.name LIKE '%%1%' OR r.room_number LIKE '%%1%')").arg(searchText);
    }
    
    // 添加日期范围条件
    sql += QString(" AND o.check_in_date BETWEEN '%1' AND '%2'").arg(
        ui->deStartDate->date().toString("yyyy-MM-dd"),
        ui->deEndDate->date().toString("yyyy-MM-dd")
    );
    
    // 添加订单状态条件
    QString orderStatus = ui->cmbOrderStatus->currentData().toString();
    if (!orderStatus.isEmpty()) {
        sql += QString(" AND o.status = '%1'").arg(orderStatus);
    }
    
    // 添加房型条件
    int roomTypeId = ui->cmbRoomType->currentData().toInt();
    if (roomTypeId > 0) {
        sql += QString(" AND r.type_id = %1").arg(roomTypeId);
    }
    
    // 添加排序
    sql += " ORDER BY o.order_id DESC";
    
    // 执行查询
    orderModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    
    if (orderModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "筛选订单失败: " + orderModel->lastError().text());
        return;
    }
    
    // 调整列宽
    ui->tableView->resizeColumnsToContents();
    
    QMessageBox::information(this, "成功", QString("找到 %1 条订单记录").arg(orderModel->rowCount()));
}

void OrderManager::showOrderDetails(int orderId)
{
    if (orderId <= 0) {
        return;
    }
    
    // 获取订单详情
    QString sql = QString("SELECT o.order_id, c.name, c.id_card, c.phone, r.room_number, rt.name as room_type, "
                         "o.check_in_date, o.check_out_date, o.actual_check_out_date, o.status, o.total_amount, "
                         "s.payment_method, s.payment_amount, s.settlement_date, s.notes "
                         "FROM order_info o "
                         "JOIN customer c ON o.customer_id = c.customer_id "
                         "JOIN room r ON o.room_id = r.room_id "
                         "JOIN room_type rt ON r.type_id = rt.type_id "
                         "LEFT JOIN settlement s ON o.order_id = s.order_id "
                         "WHERE o.order_id = %1").arg(orderId);
    
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    if (!query.exec(sql)) {
        QMessageBox::critical(this, "错误", "获取订单详情失败: " + query.lastError().text());
        return;
    }
    
    if (query.next()) {
        // 创建订单详情对话框
        QDialog *detailDialog = new QDialog(this);
        detailDialog->setWindowTitle("订单详情");
        detailDialog->resize(500, 400);
        
        // 创建文本编辑框显示订单详情
        QTextEdit *textEdit = new QTextEdit(detailDialog);
        textEdit->setReadOnly(true);
        
        // 构建订单详情内容
        QString detail = "==================== 订单详情 ====================";
        detail += "\n\n订单号: " + QString::number(orderId);
        detail += "\n客户姓名: " + query.value("name").toString();
        detail += "\n身份证号: " + query.value("id_card").toString();
        detail += "\n联系方式: " + query.value("phone").toString();
        detail += "\n房型: " + query.value("room_type").toString();
        detail += "\n房间号: " + query.value("room_number").toString();
        detail += "\n入住日期: " + query.value("check_in_date").toString();
        detail += "\n退房日期: " + query.value("check_out_date").toString();
        
        QString actualCheckOut = query.value("actual_check_out_date").toString();
        if (!actualCheckOut.isEmpty()) {
            detail += "\n实际退房日期: " + actualCheckOut;
        }
        
        detail += "\n订单状态: " + query.value("status").toString();
        detail += "\n总金额: " + QString("%1").arg(query.value("total_amount").toDouble(), 0, 'f', 2) + " 元";
        
        // 结算信息
        if (query.value("payment_method").isValid() && !query.value("payment_method").isNull()) {
            detail += "\n\n==================== 结算信息 ====================";
            detail += "\n支付方式: " + query.value("payment_method").toString();
            detail += "\n支付金额: " + QString("%1").arg(query.value("payment_amount").toDouble(), 0, 'f', 2) + " 元";
            detail += "\n结算日期: " + query.value("settlement_date").toString();
            
            QString notes = query.value("notes").toString();
            if (!notes.isEmpty()) {
                detail += "\n备注: " + notes;
            }
        }
        
        detail += "\n\n==================== 订单详情结束 ====================";
        
        textEdit->setPlainText(detail);
        
        // 设置布局
        QVBoxLayout *layout = new QVBoxLayout(detailDialog);
        layout->addWidget(textEdit);
        detailDialog->setLayout(layout);
        
        // 显示订单详情
        detailDialog->exec();
        
        delete detailDialog;
    }
}

// 按钮槽函数实现
void OrderManager::on_btnSearch_clicked()
{
    applyFilters();
}

void OrderManager::on_btnResetFilter_clicked()
{
    // 重置所有筛选条件
    ui->leOrderSearch->clear();
    ui->deStartDate->setDate(QDate::currentDate().addMonths(-1));
    ui->deEndDate->setDate(QDate::currentDate());
    ui->cmbOrderStatus->setCurrentIndex(0);
    ui->cmbRoomType->setCurrentIndex(0);
    
    // 重新加载所有订单
    loadOrders();
    
    QMessageBox::information(this, "成功", "筛选条件已重置");
}

void OrderManager::on_btnClose_clicked()
{
    close();
}

// 订单选择变化
void OrderManager::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        // 获取原始模型索引
        QModelIndex sourceIndex = proxyModel->mapToSource(index);
        int orderId = orderModel->record(sourceIndex.row()).value(0).toInt();
        showOrderDetails(orderId);
    }
}

void OrderManager::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        // 获取原始模型索引
        QModelIndex sourceIndex = proxyModel->mapToSource(index);
        int orderId = orderModel->record(sourceIndex.row()).value(0).toInt();
        showOrderDetails(orderId);
    }
}

// 日期范围变化
void OrderManager::on_deStartDate_dateChanged(const QDate &date)
{
    ui->deEndDate->setMinimumDate(date);
}

void OrderManager::on_deEndDate_dateChanged(const QDate &date)
{
    ui->deStartDate->setMaximumDate(date);
}

// 搜索框输入变化
void OrderManager::on_leOrderSearch_textChanged(const QString &arg1)
{
    // 实时搜索可以在这里实现，或者保留为点击搜索按钮触发
    QString searchText = arg1.trimmed();
    if (searchText.isEmpty()) {
        loadOrders();
    }
}
