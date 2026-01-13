#include "roomtypemanager.h"
#include "ui_roomtypemanager.h"
#include <QMessageBox>
#include <QSqlRecord>

RoomTypeManager::RoomTypeManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomTypeManager),
    model(nullptr),
    refreshTimer(nullptr)
{
    ui->setupUi(this);
    initUI();
    initModel();
    initConnections();
    
    // 初始化并启动定时器（每10秒刷新一次）
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, [=]() {
        model->select();
        ui->tableView->resizeColumnsToContents();
    });
    refreshTimer->start(10000);
}

RoomTypeManager::~RoomTypeManager()
{
    delete ui;
    if (model) {
        delete model;
    }
    if (refreshTimer) {
        delete refreshTimer;
    }
}

void RoomTypeManager::initUI()
{
    // 设置窗口标题
    setWindowTitle("房型管理");
    
    // 设置窗口大小
    resize(800, 600);
    
    // 初始化搜索框
    ui->leSearch->setPlaceholderText("输入房型名称搜索...");
}

void RoomTypeManager::initModel()
{
    // 创建数据模型
    model = new QSqlTableModel(this, DBHelper::getInstance()->getDatabase());
    model->setTable("room_type");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    // 设置字段显示名称
    model->setHeaderData(model->fieldIndex("type_id"), Qt::Horizontal, "房型ID");
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "房型名称");
    model->setHeaderData(model->fieldIndex("area"), Qt::Horizontal, "面积(m²)");
    model->setHeaderData(model->fieldIndex("bed_type"), Qt::Horizontal, "床型");
    model->setHeaderData(model->fieldIndex("price_per_day"), Qt::Horizontal, "单日定价(元)");
    model->setHeaderData(model->fieldIndex("facilities"), Qt::Horizontal, "配套设施");
    model->setHeaderData(model->fieldIndex("total_rooms"), Qt::Horizontal, "房间总数");
    model->setHeaderData(model->fieldIndex("available_rooms"), Qt::Horizontal, "剩余可订数");
    
    // 加载数据
    model->select();
    
    // 设置模型到表格视图
    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void RoomTypeManager::initConnections()
{
    // 这里可以添加额外的信号与槽连接
}

void RoomTypeManager::clearForm()
{
    ui->leName->clear();
    ui->dsbArea->setValue(0.0);
    ui->leBedType->clear();
    ui->dsbPricePerDay->setValue(0.0);
    ui->teFacilities->clear();
    ui->sbTotalRooms->setValue(0);
    ui->sbAvailableRooms->setValue(0);
}

void RoomTypeManager::showDataToForm(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    
    int row = index.row();
    QSqlRecord record = model->record(row);
    
    ui->leName->setText(record.value("name").toString());
    ui->dsbArea->setValue(record.value("area").toDouble());
    ui->leBedType->setText(record.value("bed_type").toString());
    ui->dsbPricePerDay->setValue(record.value("price_per_day").toDouble());
    ui->teFacilities->setPlainText(record.value("facilities").toString());
    ui->sbTotalRooms->setValue(record.value("total_rooms").toInt());
    ui->sbAvailableRooms->setValue(record.value("available_rooms").toInt());
}

// 按钮槽函数实现
void RoomTypeManager::on_btnAdd_clicked()
{
    // 检查表单数据
    QString name = ui->leName->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入房型名称");
        return;
    }
    
    // 检查房型名称是否已存在
    QSqlQuery checkQuery(DBHelper::getInstance()->getDatabase());
    checkQuery.prepare("SELECT COUNT(*) FROM room_type WHERE name = :name");
    checkQuery.bindValue(":name", name);
    
    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, "警告", "该房型名称已存在，请勿重复添加");
            return;
        }
    }
    
    // 开始事务
    if (!DBHelper::getInstance()->beginTransaction()) {
        QMessageBox::critical(this, "错误", "无法开始事务");
        return;
    }
    
    // 插入新记录
    int row = model->rowCount();
    if (!model->insertRow(row)) {
        QMessageBox::critical(this, "错误", "无法插入新记录: " + model->lastError().text());
        DBHelper::getInstance()->rollbackTransaction();
        return;
    }
    
    // 设置字段值
    int totalRooms = ui->sbTotalRooms->value();
    model->setData(model->index(row, model->fieldIndex("name")), name);
    model->setData(model->index(row, model->fieldIndex("area")), ui->dsbArea->value());
    model->setData(model->index(row, model->fieldIndex("bed_type")), ui->leBedType->text().trimmed());
    model->setData(model->index(row, model->fieldIndex("price_per_day")), ui->dsbPricePerDay->value());
    model->setData(model->index(row, model->fieldIndex("facilities")), ui->teFacilities->toPlainText().trimmed());
    model->setData(model->index(row, model->fieldIndex("total_rooms")), totalRooms);
    // 可用房间数默认等于总房间数
    model->setData(model->index(row, model->fieldIndex("available_rooms")), totalRooms);
    
    // 提交修改
    if (!model->submitAll()) {
        QMessageBox::critical(this, "错误", "无法提交修改: " + model->lastError().text());
        model->revertAll();
        DBHelper::getInstance()->rollbackTransaction();
        return;
    }
    
    // 提交事务
    if (!DBHelper::getInstance()->commitTransaction()) {
        QMessageBox::critical(this, "错误", "无法提交事务");
        model->revertAll();
        return;
    }
    
    // 获取新添加的房型ID
    int newTypeId = -1;
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    query.prepare("SELECT MAX(type_id) FROM room_type");
    if (query.exec() && query.next()) {
        newTypeId = query.value(0).toInt();
    }
    
    // 如果获取到了新房型ID，自动生成房间号并添加到room表
    if (newTypeId > 0) {
        int totalRooms = ui->sbTotalRooms->value();
        if (totalRooms > 0) {
            // 开始事务
            if (!DBHelper::getInstance()->beginTransaction()) {
                QMessageBox::critical(this, "错误", "无法开始事务");
                return;
            }
            
            // 生成房间号并添加到room表
            for (int i = 1; i <= totalRooms; i++) {
                // 生成房间号，格式：楼层号+房间序号（例如：101, 102, 201等）
                int floor = (i - 1) / 10 + 1;
                int roomNo = (i - 1) % 10 + 1;
                QString roomNumber = QString("%1%2").arg(floor, 2, 10, QChar('0')).arg(roomNo, 2, 10, QChar('0'));
                
                query.prepare("INSERT INTO room (room_number, type_id, floor, status) VALUES (:room_number, :type_id, :floor, '空闲')");
                query.bindValue(":room_number", roomNumber);
                query.bindValue(":type_id", newTypeId);
                query.bindValue(":floor", floor);
                
                if (!query.exec()) {
                    DBHelper::getInstance()->rollbackTransaction();
                    QMessageBox::critical(this, "错误", "无法添加房间记录: " + query.lastError().text());
                    return;
                }
            }
            
            // 提交事务
            if (!DBHelper::getInstance()->commitTransaction()) {
                QMessageBox::critical(this, "错误", "无法提交房间事务");
                return;
            }
        }
    }
    
    QMessageBox::information(this, "成功", "房型添加成功，已自动生成房间记录");
    clearForm();
    model->select();
}

void RoomTypeManager::on_btnEdit_clicked()
{
    // 获取选中行
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的房型");
        return;
    }
    
    // 获取当前编辑的房型ID
    int currentTypeId = model->record(selected.first().row()).value("type_id").toInt();
    
    // 检查房型名称是否已存在（排除当前编辑的房型）
    QString name = ui->leName->text().trimmed();
    QSqlQuery checkQuery(DBHelper::getInstance()->getDatabase());
    checkQuery.prepare("SELECT COUNT(*) FROM room_type WHERE name = :name AND type_id != :type_id");
    checkQuery.bindValue(":name", name);
    checkQuery.bindValue(":type_id", currentTypeId);
    
    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, "警告", "该房型名称已存在，请勿重复添加");
            return;
        }
    }
    
    // 开始事务
    if (!DBHelper::getInstance()->beginTransaction()) {
        QMessageBox::critical(this, "错误", "无法开始事务");
        return;
    }
    
    // 更新选中行数据
    int row = selected.first().row();
    model->setData(model->index(row, model->fieldIndex("name")), ui->leName->text().trimmed());
    model->setData(model->index(row, model->fieldIndex("area")), ui->dsbArea->value());
    model->setData(model->index(row, model->fieldIndex("bed_type")), ui->leBedType->text().trimmed());
    model->setData(model->index(row, model->fieldIndex("price_per_day")), ui->dsbPricePerDay->value());
    model->setData(model->index(row, model->fieldIndex("facilities")), ui->teFacilities->toPlainText().trimmed());
    model->setData(model->index(row, model->fieldIndex("total_rooms")), ui->sbTotalRooms->value());
    model->setData(model->index(row, model->fieldIndex("available_rooms")), ui->sbAvailableRooms->value());
    
    // 提交修改
    if (!model->submitAll()) {
        QMessageBox::critical(this, "错误", "无法提交修改: " + model->lastError().text());
        model->revertAll();
        DBHelper::getInstance()->rollbackTransaction();
        return;
    }
    
    // 提交事务
    if (!DBHelper::getInstance()->commitTransaction()) {
        QMessageBox::critical(this, "错误", "无法提交事务");
        model->revertAll();
        return;
    }
    
    // 获取修改后的房型ID和总房间数
    int typeId = selected.first().row();
    typeId = model->record(typeId).value("type_id").toInt();
    int newTotalRooms = ui->sbTotalRooms->value();
    
    // 查询当前房间数量
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    query.prepare("SELECT COUNT(*) FROM room WHERE type_id = :type_id");
    query.bindValue(":type_id", typeId);
    
    int currentRoomCount = 0;
    if (query.exec() && query.next()) {
        currentRoomCount = query.value(0).toInt();
    }
    
    // 如果总房间数发生变化，更新房间记录
    if (newTotalRooms != currentRoomCount) {
        // 开始事务
        if (!DBHelper::getInstance()->beginTransaction()) {
            QMessageBox::critical(this, "错误", "无法开始事务");
            return;
        }
        
        if (newTotalRooms > currentRoomCount) {
            // 增加房间数
            int roomsToAdd = newTotalRooms - currentRoomCount;
            
            // 获取当前最大房间号
            int maxRoomNo = 0;
            query.prepare("SELECT MAX(CAST(room_number AS INTEGER)) FROM room WHERE type_id = :type_id");
            query.bindValue(":type_id", typeId);
            if (query.exec() && query.next() && !query.value(0).isNull()) {
                maxRoomNo = query.value(0).toInt();
            }
            
            // 添加新房间
            for (int i = 1; i <= roomsToAdd; i++) {
                maxRoomNo++;
                QString roomNumber = QString::number(maxRoomNo);
                int floor = (maxRoomNo / 100) + ((maxRoomNo % 100 > 0) ? 1 : 0);
                
                query.prepare("INSERT INTO room (room_number, type_id, floor, status) VALUES (:room_number, :type_id, :floor, '空闲')");
                query.bindValue(":room_number", roomNumber);
                query.bindValue(":type_id", typeId);
                query.bindValue(":floor", floor);
                
                if (!query.exec()) {
                    DBHelper::getInstance()->rollbackTransaction();
                    QMessageBox::critical(this, "错误", "无法添加房间记录: " + query.lastError().text());
                    return;
                }
            }
        } else {
            // 减少房间数
            int roomsToRemove = currentRoomCount - newTotalRooms;
            
            // 获取要删除的房间ID列表（按房间号降序排列，删除最大的房间）
            query.prepare("SELECT room_id FROM room WHERE type_id = :type_id ORDER BY CAST(room_number AS INTEGER) DESC LIMIT :limit");
            query.bindValue(":type_id", typeId);
            query.bindValue(":limit", roomsToRemove);
            
            if (query.exec()) {
                while (query.next()) {
                    int roomId = query.value(0).toInt();
                    
                    // 删除房间
                    QSqlQuery deleteQuery(DBHelper::getInstance()->getDatabase());
                    deleteQuery.prepare("DELETE FROM room WHERE room_id = :room_id");
                    deleteQuery.bindValue(":room_id", roomId);
                    
                    if (!deleteQuery.exec()) {
                        DBHelper::getInstance()->rollbackTransaction();
                        QMessageBox::critical(this, "错误", "无法删除房间记录: " + deleteQuery.lastError().text());
                        return;
                    }
                }
            }
        }
        
        // 更新available_rooms字段
        query.prepare("UPDATE room_type SET available_rooms = total_rooms WHERE type_id = :type_id");
        query.bindValue(":type_id", typeId);
        
        if (!query.exec()) {
            DBHelper::getInstance()->rollbackTransaction();
            QMessageBox::critical(this, "错误", "无法更新可用房间数: " + query.lastError().text());
            return;
        }
        
        // 提交事务
        if (!DBHelper::getInstance()->commitTransaction()) {
            QMessageBox::critical(this, "错误", "无法提交房间事务");
            return;
        }
    }
    
    QMessageBox::information(this, "成功", "房型修改成功");
    clearForm();
    model->select();
}

void RoomTypeManager::on_btnDelete_clicked()
{
    // 获取选中行
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的房型");
        return;
    }
    
    // 确认删除
    if (QMessageBox::question(this, "确认删除", "确定要删除选中的房型吗？", 
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }
    
    // 开始事务
    if (!DBHelper::getInstance()->beginTransaction()) {
        QMessageBox::critical(this, "错误", "无法开始事务");
        return;
    }
    
    try {
        QSqlQuery query(DBHelper::getInstance()->getDatabase());
        
        // 先删除相关的房间记录
        for (const QModelIndex &index : selected) {
            int typeId = model->record(index.row()).value("type_id").toInt();
            
            // 删除该房型下的所有房间
            query.prepare("DELETE FROM room WHERE type_id = :type_id");
            query.bindValue(":type_id", typeId);
            
            if (!query.exec()) {
                throw QString("无法删除房间记录: " + query.lastError().text());
            }
        }
        
        // 删除选中的房型记录
        for (const QModelIndex &index : selected) {
            if (!model->removeRow(index.row())) {
                throw QString("无法删除房型记录: " + model->lastError().text());
            }
        }
        
        // 提交修改
        if (!model->submitAll()) {
            throw QString("无法提交修改: " + model->lastError().text());
        }
        
        // 提交事务
        if (!DBHelper::getInstance()->commitTransaction()) {
            throw QString("无法提交事务");
        }
        
        QMessageBox::information(this, "成功", "房型删除成功，相关房间记录已删除");
        clearForm();
        model->select();
        
    } catch (const QString &error) {
        // 回滚事务
        DBHelper::getInstance()->rollbackTransaction();
        model->revertAll();
        QMessageBox::critical(this, "错误", error);
    }
}

void RoomTypeManager::on_btnRefresh_clicked()
{
    model->select();
    ui->tableView->resizeColumnsToContents();
    QMessageBox::information(this, "成功", "数据刷新成功");
}

void RoomTypeManager::on_btnClose_clicked()
{
    close();
}

// 表格双击事件
void RoomTypeManager::on_tableView_doubleClicked(const QModelIndex &index)
{
    showDataToForm(index);
}

// 搜索功能实现
void RoomTypeManager::on_btnSearch_clicked()
{
    QString searchText = ui->leSearch->text().trimmed();
    if (searchText.isEmpty()) {
        model->setFilter("");
    } else {
        model->setFilter(QString("name LIKE '%%1%'").arg(searchText));
    }
    model->select();
}

void RoomTypeManager::on_leSearch_textChanged(const QString &arg1)
{
    QString searchText = arg1.trimmed();
    if (searchText.isEmpty()) {
        model->setFilter("");
        model->select();
    }
    // 实时搜索可以在这里实现，或者保留为点击搜索按钮触发
}
