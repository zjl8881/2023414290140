#include "checkinmanager.h"
#include "ui_checkinmanager.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QRegExp>
#include <QDebug>

CheckInManager::CheckInManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckInManager),
    roomTypeModel(nullptr),
    roomModel(nullptr),
    customerModel(nullptr),
    idCardValidator(nullptr),
    phoneValidator(nullptr)
{
    ui->setupUi(this);
    initUI();
    initModels();
    initValidators();
    initConnections();
}

CheckInManager::~CheckInManager()
{
    delete ui;
    
    if (roomTypeModel) delete roomTypeModel;
    if (roomModel) delete roomModel;
    if (customerModel) delete customerModel;
    if (idCardValidator) delete idCardValidator;
    if (phoneValidator) delete phoneValidator;
}

void CheckInManager::initUI()
{
    // 设置窗口标题
    setWindowTitle("客户入住登记");
    
    // 设置窗口大小
    resize(800, 600);
    
    // 初始化日期控件
    ui->deCheckIn->setDate(QDate::currentDate());
    ui->deCheckOut->setDate(QDate::currentDate().addDays(1));
    ui->deCheckIn->setMinimumDate(QDate::currentDate());
    ui->deCheckOut->setMinimumDate(ui->deCheckIn->date().addDays(1));
    
    // 初始化搜索框
    ui->leCustomerSearch->setPlaceholderText("输入客户姓名或身份证号搜索...");
}

void CheckInManager::initModels()
{
    // 创建房型数据模型
    roomTypeModel = new QSqlQueryModel(this);
    ui->cmbRoomType->setModel(roomTypeModel);
    ui->cmbRoomType->setModelColumn(1); // 显示房型名称
    
    // 创建房间数据模型
    roomModel = new QSqlQueryModel(this);
    ui->cmbRoom->setModel(roomModel);
    ui->cmbRoom->setModelColumn(1); // 显示房间号
    
    // 创建客户数据模型
    customerModel = new QSqlQueryModel(this);
    
    // 加载初始数据
    loadRoomTypes();
}

void CheckInManager::initValidators()
{
    // 身份证号验证器（18位）
    // 宽松的正则表达式，允许中间输入过程
    QRegExp idCardRegex("^[1-9]\\d{0,5}(18|19|20)?\\d{0,2}(0[1-9]|1[0-2])?(0[1-9]|[12]\\d|3[01])?\\d{0,3}[\\dXx]?$");
    idCardValidator = new QRegExpValidator(idCardRegex, this);
    ui->leIdCard->setValidator(idCardValidator);
    ui->leIdCard->setMaxLength(18);
    
    // 手机号验证器（11位）
    QRegExp phoneRegex("^1[3-9]\\d{0,9}$");
    phoneValidator = new QRegExpValidator(phoneRegex, this);
    ui->lePhone->setValidator(phoneValidator);
    ui->lePhone->setMaxLength(11);
}

void CheckInManager::initConnections()
{
    // 这里可以添加额外的信号与槽连接
}

void CheckInManager::clearForm()
{
    ui->leCustomerName->clear();
    ui->leIdCard->clear();
    ui->lePhone->clear();
    ui->deCheckIn->setDate(QDate::currentDate());
    ui->deCheckOut->setDate(QDate::currentDate().addDays(1));
    ui->cmbRoomType->setCurrentIndex(0);
    ui->cmbRoom->clear();
    ui->leExpectedAmount->setText("0.00");
}

void CheckInManager::loadRoomTypes()
{
    // 移除available_rooms > 0条件，显示所有房型
    QString sql = "SELECT type_id, name, price_per_day FROM room_type";
    roomTypeModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    
    if (roomTypeModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "加载房型数据失败: " + roomTypeModel->lastError().text());
        return;
    }
    
    // 设置列名（仅内部使用）
    roomTypeModel->setHeaderData(0, Qt::Horizontal, "type_id");
    roomTypeModel->setHeaderData(1, Qt::Horizontal, "name");
    roomTypeModel->setHeaderData(2, Qt::Horizontal, "price_per_day");
    
    // 重新设置模型，确保组合框更新
    ui->cmbRoomType->setModel(nullptr);
    ui->cmbRoomType->setModel(roomTypeModel);
    ui->cmbRoomType->setModelColumn(1); // 显示房型名称
    
    if (roomTypeModel->rowCount() > 0) {
        // 默认选择第一个房型
        ui->cmbRoomType->setCurrentIndex(0);
        on_cmbRoomType_currentIndexChanged(0);
    } else {
        ui->cmbRoom->clear();
        ui->leExpectedAmount->setText("0.00");
    }
}

void CheckInManager::loadRoomsByType(int typeId)
{
    QString sql = QString("SELECT room_id, room_number FROM room WHERE type_id = %1 AND status = '空闲'").arg(typeId);
    roomModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    
    if (roomModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "加载房间数据失败: " + roomModel->lastError().text());
        return;
    }
    
    // 设置列名（仅内部使用）
    roomModel->setHeaderData(0, Qt::Horizontal, "room_id");
    roomModel->setHeaderData(1, Qt::Horizontal, "room_number");
    
    // 重新设置模型，确保组合框更新
    ui->cmbRoom->setModel(nullptr);
    ui->cmbRoom->setModel(roomModel);
    ui->cmbRoom->setModelColumn(1); // 显示房间号
    
    if (roomModel->rowCount() > 0) {
        // 默认选择第一个房间
        ui->cmbRoom->setCurrentIndex(0);
        calculateExpectedAmount();
    } else {
        ui->cmbRoom->setModel(nullptr);
        ui->leExpectedAmount->setText("0.00");
    }
}

void CheckInManager::calculateExpectedAmount()
{
    // 获取选择的房型
    int roomTypeIndex = ui->cmbRoomType->currentIndex();
    if (roomTypeIndex < 0) {
        ui->leExpectedAmount->setText("0.00");
        return;
    }
    
    // 获取房型单价
    double pricePerDay = roomTypeModel->record(roomTypeIndex).value(2).toDouble();
    
    // 计算入住天数
    int days = ui->deCheckIn->date().daysTo(ui->deCheckOut->date());
    if (days <= 0) days = 1;
    
    // 计算预计金额
    double expectedAmount = pricePerDay * days;
    ui->leExpectedAmount->setText(QString("%1").arg(expectedAmount, 0, 'f', 2));
}

bool CheckInManager::validateForm()
{
    // 验证客户姓名
    if (ui->leCustomerName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入客户姓名");
        ui->leCustomerName->setFocus();
        return false;
    }
    
    // 验证身份证号
    QString idCard = ui->leIdCard->text().trimmed();
    if (idCard.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入身份证号");
        ui->leIdCard->setFocus();
        return false;
    }
    
    // 使用严格的正则表达式进行最终验证
    QRegExp strictIdCardRegex("^[1-9]\\d{5}(18|19|20)\\d{2}(0[1-9]|1[0-2])(0[1-9]|[12]\\d|3[01])\\d{3}[\\dXx]$");
    if (!strictIdCardRegex.exactMatch(idCard)) {
        QMessageBox::warning(this, "警告", "身份证号格式不正确");
        ui->leIdCard->setFocus();
        return false;
    }
    
    // 验证手机号
    QString phone = ui->lePhone->text().trimmed();
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入手机号");
        ui->lePhone->setFocus();
        return false;
    }
    
    // 使用严格的正则表达式进行最终验证
    QRegExp strictPhoneRegex("^1[3-9]\\d{9}$");
    if (!strictPhoneRegex.exactMatch(phone)) {
        QMessageBox::warning(this, "警告", "手机号格式不正确");
        ui->lePhone->setFocus();
        return false;
    }
    
    // 验证房型选择
    if (ui->cmbRoomType->currentIndex() < 0) {
        QMessageBox::warning(this, "警告", "请选择房型");
        ui->cmbRoomType->setFocus();
        return false;
    }
    
    // 验证房间选择
    if (ui->cmbRoom->currentIndex() < 0 || ui->cmbRoom->currentText().isEmpty()) {
        QMessageBox::warning(this, "警告", "该房型下没有可用房间，请选择其他房型");
        ui->cmbRoomType->setFocus();
        return false;
    }
    
    // 验证日期
    if (ui->deCheckIn->date() >= ui->deCheckOut->date()) {
        QMessageBox::warning(this, "警告", "退房日期必须晚于入住日期");
        ui->deCheckOut->setFocus();
        return false;
    }
    
    return true;
}

bool CheckInManager::processCheckIn()
{
    // 开始事务
    if (!DBHelper::getInstance()->beginTransaction()) {
        QMessageBox::critical(this, "错误", "无法开始事务");
        return false;
    }
    
    try {
        // 1. 检查客户是否已存在
        QString idCard = ui->leIdCard->text().trimmed();
        int customerId = -1;
        
        QSqlQuery query(DBHelper::getInstance()->getDatabase());
        query.prepare("SELECT customer_id FROM customer WHERE id_card = :id_card");
        query.bindValue(":id_card", idCard);
        
        if (query.exec() && query.next()) {
            // 客户已存在，获取客户ID
            customerId = query.value(0).toInt();
        } else {
            // 客户不存在，插入新客户
            query.prepare("INSERT INTO customer (name, id_card, phone) VALUES (:name, :id_card, :phone)");
            query.bindValue(":name", ui->leCustomerName->text().trimmed());
            query.bindValue(":id_card", idCard);
            query.bindValue(":phone", ui->lePhone->text().trimmed());
            
            if (!query.exec()) {
                throw QString("插入客户信息失败: " + query.lastError().text());
            }
            
            customerId = query.lastInsertId().toInt();
        }
        
        // 2. 获取选择的房间ID
        int roomIndex = ui->cmbRoom->currentIndex();
        int roomId = roomModel->record(roomIndex).value(0).toInt();
        
        // 3. 计算实际金额
        double amount = ui->leExpectedAmount->text().toDouble();
        
        // 4. 插入订单
        query.prepare("INSERT INTO order_info (customer_id, room_id, check_in_date, check_out_date, status, total_amount) "
                      "VALUES (:customer_id, :room_id, :check_in_date, :check_out_date, '已入住', :total_amount)");
        query.bindValue(":customer_id", customerId);
        query.bindValue(":room_id", roomId);
        query.bindValue(":check_in_date", ui->deCheckIn->date().toString("yyyy-MM-dd"));
        query.bindValue(":check_out_date", ui->deCheckOut->date().toString("yyyy-MM-dd"));
        query.bindValue(":total_amount", amount);
        
        if (!query.exec()) {
            throw QString("插入订单失败: " + query.lastError().text());
        }
        
        // 5. 更新房间状态为"已入住"
        query.prepare("UPDATE room SET status = '已入住' WHERE room_id = :room_id");
        query.bindValue(":room_id", roomId);
        
        if (!query.exec()) {
            throw QString("更新房间状态失败: " + query.lastError().text());
        }
        
        // 6. 更新房型可用数量
        int roomTypeIndex = ui->cmbRoomType->currentIndex();
        int typeId = roomTypeModel->record(roomTypeIndex).value(0).toInt();
        
        query.prepare("UPDATE room_type SET available_rooms = available_rooms - 1 WHERE type_id = :type_id");
        query.bindValue(":type_id", typeId);
        
        if (!query.exec()) {
            throw QString("更新房型可用数量失败: " + query.lastError().text());
        }
        
        // 提交事务
        if (!DBHelper::getInstance()->commitTransaction()) {
            throw QString("提交事务失败");
        }
        
        QMessageBox::information(this, "成功", "客户入住登记成功");
        return true;
        
    } catch (const QString &error) {
        // 回滚事务
        DBHelper::getInstance()->rollbackTransaction();
        QMessageBox::critical(this, "错误", error);
        return false;
    }
}

// 按钮槽函数实现
void CheckInManager::on_btnCheckIn_clicked()
{
    // 验证表单
    if (!validateForm()) {
        return;
    }
    
    // 处理入住登记
    if (processCheckIn()) {
        // 清空表单
        clearForm();
        
        // 刷新数据
        loadRoomTypes();
    }
}

void CheckInManager::on_btnCancel_clicked()
{
    close();
}

void CheckInManager::on_btnRefresh_clicked()
{
    loadRoomTypes();
    calculateExpectedAmount();
    QMessageBox::information(this, "成功", "数据刷新成功");
}

// 房型选择变化
void CheckInManager::on_cmbRoomType_currentIndexChanged(int index)
{
    if (index >= 0) {
        int typeId = roomTypeModel->record(index).value(0).toInt();
        loadRoomsByType(typeId);
        calculateExpectedAmount();
    }
}

// 房间选择变化
void CheckInManager::on_cmbRoom_currentIndexChanged(int index)
{
    calculateExpectedAmount();
}

// 日期变化
void CheckInManager::on_deCheckIn_dateChanged(const QDate &date)
{
    ui->deCheckOut->setMinimumDate(date.addDays(1));
    calculateExpectedAmount();
}

void CheckInManager::on_deCheckOut_dateChanged(const QDate &date)
{
    calculateExpectedAmount();
}

// 搜索客户
void CheckInManager::on_btnSearchCustomer_clicked()
{
    QString searchText = ui->leCustomerSearch->text().trimmed();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入搜索条件");
        return;
    }
    
    QString sql = QString("SELECT customer_id, name, id_card, phone FROM customer WHERE name LIKE '%%1%' OR id_card LIKE '%%1%'").arg(searchText);
    
    if (customerModel) {
        delete customerModel;
    }
    
    customerModel = new QSqlQueryModel(this);
    customerModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    
    if (customerModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "搜索客户失败: " + customerModel->lastError().text());
        return;
    }
    
    // 显示搜索结果（这里可以根据需要添加表格显示）
    QMessageBox::information(this, "搜索结果", QString("找到 %1 位客户").arg(customerModel->rowCount()));
}
