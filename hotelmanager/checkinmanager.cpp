#include "checkinmanager.h"
#include "ui_checkinmanager.h"
#include "dbhelper.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <QRegExpValidator>

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
    initConnections();啊吴大维
}

CheckInManager::~CheckInManager()
{
    delete ui;
    if (roomTypeModel) {
        delete roomTypeModel;
    }
    if (roomModel) {
        delete roomModel;
    }
    if (customerModel) {
        delete customerModel;
    }
    if (idCardValidator) {
        delete idCardValidator;
    }
    if (phoneValidator) {
        delete phoneValidator;
    }
}

void CheckInManager::initUI()
{
    // 设置窗口标题
    setWindowTitle("入住登记");
    
    // 设置窗口大小
    resize(700, 500);
    
    // 初始化日期选择器
    ui->deCheckIn->setDate(QDate::currentDate());
    ui->deCheckOut->setDate(QDate::currentDate().addDays(1));
}

void CheckInManager::initModels()
{
    // 初始化房型模型
    roomTypeModel = new QSqlQueryModel(this);
    
    // 初始化房间模型
    roomModel = new QSqlQueryModel(this);
    
    // 初始化客户模型
    customerModel = new QSqlQueryModel(this);
    
    // 加载房型数据
    loadRoomTypes();
}

void CheckInManager::initValidators()
{
    // 设置ID卡验证器
    QRegExp idCardRegex("^[1-9]\\d{5}(18|19|20)\\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$");
    idCardValidator = new QRegExpValidator(idCardRegex, this);
    ui->leIdCard->setValidator(idCardValidator);
    
    // 设置手机号验证器
    QRegExp phoneRegex("^1[3-9]\\d{9}$");
    phoneValidator = new QRegExpValidator(phoneRegex, this);
    ui->lePhone->setValidator(phoneValidator);
}

void CheckInManager::initConnections()
{
    // 连接信号与槽
    connect(ui->cmbRoomType, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &CheckInManager::on_cmbRoomType_currentIndexChanged);
    connect(ui->deCheckIn, &QDateEdit::dateChanged, this, &CheckInManager::on_deCheckIn_dateChanged);
    connect(ui->deCheckOut, &QDateEdit::dateChanged, this, &CheckInManager::on_deCheckOut_dateChanged);
}

void CheckInManager::loadRoomTypes()
{
    // 从数据库获取房型列表，只显示有可用房间的房型
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    query.prepare("SELECT type_id, name FROM room_type WHERE available_rooms > 0");
    
    if (query.exec()) {
        roomTypeModel->setQuery(std::move(query));
        ui->cmbRoomType->setModel(roomTypeModel);
        ui->cmbRoomType->setModelColumn(1);
    }
    
    // 加载房间号
    if (ui->cmbRoomType->currentIndex() >= 0) {
        int typeId = ui->cmbRoomType->model()->index(ui->cmbRoomType->currentIndex(), 0).data().toInt();
        loadRoomsByType(typeId);
    }
}

void CheckInManager::loadRoomsByType(int typeId)
{
    // 从数据库获取该房型下的空闲房间
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    query.prepare("SELECT room_id, room_number FROM room WHERE type_id = :type_id AND status = '空闲'");
    query.bindValue(":type_id", typeId);
    
    if (query.exec()) {
        roomModel->setQuery(std::move(query));
        ui->cmbRoom->setModel(roomModel);
        ui->cmbRoom->setModelColumn(1);
    }
    
    // 计算预计金额
    calculateExpectedAmount();
}

void CheckInManager::calculateExpectedAmount()
{
    // 获取选中的房型ID
    if (ui->cmbRoomType->currentIndex() < 0) {
        ui->leExpectedAmount->setText("0.00");
        return;
    }
    
    int typeId = ui->cmbRoomType->itemData(ui->cmbRoomType->currentIndex()).toInt();
    if (typeId <= 0) {
        ui->leExpectedAmount->setText("0.00");
        return;
    }
    
    // 获取单日房价
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    query.prepare("SELECT price_per_day FROM room_type WHERE type_id = :type_id");
    query.bindValue(":type_id", typeId);
    
    double pricePerDay = 0.0;
    if (query.exec() && query.next()) {
        pricePerDay = query.value(0).toDouble();
    }
    
    // 计算入住天数
    int days = ui->deCheckIn->date().daysTo(ui->deCheckOut->date());
    if (days < 1) {
        days = 1;
    }
    
    // 计算总价
    double totalAmount = pricePerDay * days;
    ui->leExpectedAmount->setText(QString::number(totalAmount, 'f', 2));
}

void CheckInManager::clearForm()
{
    ui->leCustomerName->clear();
    ui->leIdCard->clear();
    ui->lePhone->clear();
    ui->deCheckIn->setDate(QDate::currentDate());
    ui->deCheckOut->setDate(QDate::currentDate().addDays(1));
    ui->cmbRoomType->setCurrentIndex(-1);
    ui->cmbRoom->clear();
    ui->leExpectedAmount->setText("0.00");
}

bool CheckInManager::validateForm()
{
    // 检查表单数据
    QString name = ui->leCustomerName->text().trimmed();
    QString idCard = ui->leIdCard->text().trimmed();
    QString phone = ui->lePhone->text().trimmed();
    
    if (name.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入客户姓名");
        return false;
    }
    
    if (idCard.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入身份证号码");
        return false;
    }
    
    // 验证ID卡格式
    QRegExp idCardRegex("^[1-9]\\d{5}(18|19|20)\\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$");
    if (!idCardRegex.exactMatch(idCard)) {
        QMessageBox::warning(this, "警告", "请输入有效的身份证号码");
        return false;
    }
    
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入手机号码");
        return false;
    }
    
    // 验证手机号格式
    QRegExp phoneRegex("^1[3-9]\\d{9}$");
    if (!phoneRegex.exactMatch(phone)) {
        QMessageBox::warning(this, "警告", "请输入有效的手机号码");
        return false;
    }
    
    if (ui->cmbRoomType->currentIndex() < 0) {
        QMessageBox::warning(this, "警告", "请选择房型");
        return false;
    }
    
    if (ui->cmbRoom->currentIndex() < 0) {
        QMessageBox::warning(this, "警告", "请选择房间");
        return false;
    }
    
    if (ui->deCheckIn->date() > ui->deCheckOut->date()) {
        QMessageBox::warning(this, "警告", "入住日期不能晚于退房日期");
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
        QSqlQuery query(DBHelper::getInstance()->getDatabase());
        
        // 获取表单数据
        QString name = ui->leCustomerName->text().trimmed();
        QString idCard = ui->leIdCard->text().trimmed();
        QString phone = ui->lePhone->text().trimmed();
        int roomId = ui->cmbRoom->itemData(ui->cmbRoom->currentIndex()).toInt();
        QDate checkInDate = ui->deCheckIn->date();
        QDate checkOutDate = ui->deCheckOut->date();
        
        // 检查客户是否已存在
        query.prepare("SELECT customer_id FROM customer WHERE id_card = :id_card");
        query.bindValue(":id_card", idCard);
        
        int customerId = -1;
        if (query.exec() && query.next()) {
            customerId = query.value(0).toInt();
        } else {
            // 插入新客户
            query.prepare("INSERT INTO customer (name, id_card, phone) VALUES (:name, :id_card, :phone)");
            query.bindValue(":name", name);
            query.bindValue(":id_card", idCard);
            query.bindValue(":phone", phone);
            
            if (!query.exec()) {
                throw QString("无法插入客户记录: " + query.lastError().text());
            }
            
            customerId = query.lastInsertId().toInt();
        }
        
        // 获取房间信息和房价
        query.prepare("SELECT type_id FROM room WHERE room_id = :room_id");
        query.bindValue(":room_id", roomId);
        
        int typeId = -1;
        if (!query.exec() || !query.next()) {
            throw QString("无法获取房间信息");
        }
        typeId = query.value(0).toInt();
        
        // 获取房价
        double pricePerDay = 0.0;
        query.prepare("SELECT price_per_day FROM room_type WHERE type_id = :type_id");
        query.bindValue(":type_id", typeId);
        if (query.exec() && query.next()) {
            pricePerDay = query.value(0).toDouble();
        }
        
        // 计算入住天数和总价
        int days = checkInDate.daysTo(checkOutDate);
        if (days < 1) {
            days = 1;
        }
        double totalAmount = pricePerDay * days;
        
        // 插入订单
        query.prepare("INSERT INTO order_info (customer_id, room_id, check_in_date, check_out_date, status, total_amount) VALUES (:customer_id, :room_id, :check_in_date, :check_out_date, '已入住', :total_amount)");
        query.bindValue(":customer_id", customerId);
        query.bindValue(":room_id", roomId);
        query.bindValue(":check_in_date", checkInDate.toString("yyyy-MM-dd"));
        query.bindValue(":check_out_date", checkOutDate.toString("yyyy-MM-dd"));
        query.bindValue(":total_amount", totalAmount);
        
        if (!query.exec()) {
            throw QString("无法插入订单记录: " + query.lastError().text());
        }
        
        // 更新房间状态
        query.prepare("UPDATE room SET status = '已入住' WHERE room_id = :room_id");
        query.bindValue(":room_id", roomId);
        
        if (!query.exec()) {
            throw QString("无法更新房间状态: " + query.lastError().text());
        }
        
        // 更新房型的可用房间数
        query.prepare("UPDATE room_type SET available_rooms = available_rooms - 1 WHERE type_id = :type_id");
        query.bindValue(":type_id", typeId);
        
        if (!query.exec()) {
            throw QString("无法更新可用房间数: " + query.lastError().text());
        }
        
        // 提交事务
        if (!DBHelper::getInstance()->commitTransaction()) {
            throw QString("无法提交事务");
        }
        
        return true;
        
    } catch (const QString &error) {
        // 回滚事务
        DBHelper::getInstance()->rollbackTransaction();
        QMessageBox::critical(this, "错误", error);
        return false;
    }
}

void CheckInManager::on_btnCheckIn_clicked()
{
    if (validateForm()) {
        if (processCheckIn()) {
            QMessageBox::information(this, "成功", "入住登记成功");
            clearForm();
            loadRoomTypes(); // 重新加载房型和房间号
        }
    }
}

void CheckInManager::on_btnCancel_clicked()
{
    close();
}

void CheckInManager::on_btnRefresh_clicked()
{
    loadRoomTypes();
}

void CheckInManager::on_cmbRoomType_currentIndexChanged(int index)
{
    if (index >= 0) {
        int typeId = ui->cmbRoomType->itemData(index).toInt();
        loadRoomsByType(typeId);
    }
}

void CheckInManager::on_cmbRoom_currentIndexChanged(int index)
{
    // 计算预计金额
    calculateExpectedAmount();
}

void CheckInManager::on_deCheckIn_dateChanged(const QDate &date)
{
    // 确保退房日期不早于入住日期
    if (ui->deCheckOut->date() < date) {
        ui->deCheckOut->setDate(date.addDays(1));
    }
    // 计算预计金额
    calculateExpectedAmount();
}

void CheckInManager::on_deCheckOut_dateChanged(const QDate &date)
{
    // 计算预计金额
    calculateExpectedAmount();
}

void CheckInManager::on_btnSearchCustomer_clicked()
{
    // 这里可以实现客户搜索功能
    QMessageBox::information(this, "提示", "客户搜索功能待实现");
}
