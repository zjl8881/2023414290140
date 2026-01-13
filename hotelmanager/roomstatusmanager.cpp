#include "roomstatusmanager.h"
#include "ui_roomstatusmanager.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTextEdit>
#include <QDebug>

// 自定义代理，用于设置房间状态单元格样式
class RoomStatusDelegate : public QStyledItemDelegate
{
public:
    explicit RoomStatusDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);
        
        // 根据房间状态设置不同背景颜色
        QString status = index.data().toString();
        QColor bgColor;
        
        if (status == "空闲") {
            bgColor = QColor(144, 238, 144); // 浅绿色
        } else if (status == "已入住") {
            bgColor = QColor(255, 182, 193); // 浅红色
        } else {
            bgColor = QColor(255, 255, 255); // 默认白色
        }
        
        // 绘制背景
        painter->fillRect(option.rect, bgColor);
        
        // 绘制文本
        painter->drawText(option.rect, Qt::AlignCenter, opt.text);
    }
};

RoomStatusManager::RoomStatusManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomStatusManager),
    roomModel(nullptr),
    statusUpdateTimer(nullptr)
{
    ui->setupUi(this);
    initUI();
    initModel();
    initConnections();
    
    // 启动房间状态更新定时器（每30秒更新一次）
    statusUpdateTimer = new QTimer(this);
    connect(statusUpdateTimer, &QTimer::timeout, this, &RoomStatusManager::onTimerTimeout);
    statusUpdateTimer->start(30000);
}

RoomStatusManager::~RoomStatusManager()
{
    delete ui;
    if (roomModel) delete roomModel;
    if (statusUpdateTimer) delete statusUpdateTimer;
}

void RoomStatusManager::initUI()
{
    // 设置窗口标题
    setWindowTitle("房间状态管理");
    
    // 设置窗口大小
    resize(800, 600);
    
    // 初始化筛选条件
    loadFilters();
    
    // 设置房间状态代理
    ui->tableView->setItemDelegateForColumn(4, new RoomStatusDelegate(this));
}

void RoomStatusManager::initModel()
{
    // 创建房间数据模型
    roomModel = new QSqlQueryModel(this);
    
    // 使用JOIN查询获取房间数据和房型名称
    QString sql = "SELECT r.room_id, r.room_number, rt.name as room_type, r.floor, r.status "
                 "FROM room r "
                 "LEFT JOIN room_type rt ON r.type_id = rt.type_id "
                 "ORDER BY r.room_id";
    
    roomModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    
    if (roomModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "无法加载房间数据: " + roomModel->lastError().text());
        return;
    }
    
    // 设置字段显示名称
    roomModel->setHeaderData(0, Qt::Horizontal, "房间ID");
    roomModel->setHeaderData(1, Qt::Horizontal, "房间号");
    roomModel->setHeaderData(2, Qt::Horizontal, "房型");
    roomModel->setHeaderData(3, Qt::Horizontal, "楼层");
    roomModel->setHeaderData(4, Qt::Horizontal, "房间状态");
    
    // 设置表格视图
    ui->tableView->setModel(roomModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();
    
    // 设置房间状态代理（状态列索引仍为4）
    ui->tableView->setItemDelegateForColumn(4, new RoomStatusDelegate(this));
}

void RoomStatusManager::initConnections()
{
    // 这里可以添加额外的信号与槽连接
}

void RoomStatusManager::loadRooms()
{
    if (roomModel) {
        // 使用JOIN查询获取房间数据和房型名称
        QString sql = "SELECT r.room_id, r.room_number, rt.name as room_type, r.floor, r.status "
                     "FROM room r "
                     "LEFT JOIN room_type rt ON r.type_id = rt.type_id "
                     "ORDER BY r.room_id";
        
        roomModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
        ui->tableView->resizeColumnsToContents();
    }
}

void RoomStatusManager::loadFilters()
{
    // 房间状态筛选 - 只保留全部、空闲和已入住
    ui->cmbStatus->addItem("全部", "");
    ui->cmbStatus->addItem("空闲", "空闲");
    ui->cmbStatus->addItem("已入住", "已入住");
    
    // 楼层筛选
    ui->cmbFloor->addItem("全部", "");
    for (int i = 1; i <= 10; ++i) {
        ui->cmbFloor->addItem(QString("%1楼").arg(i), i);
    }
    
    // 房型筛选
    ui->cmbRoomType->addItem("全部", "");
    
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    if (query.exec("SELECT type_id, name FROM room_type ORDER BY name")) {
        while (query.next()) {
            ui->cmbRoomType->addItem(query.value("name").toString(), query.value("type_id").toInt());
        }
    } else {
        qDebug() << "获取房型数据失败: " << query.lastError().text();
        QMessageBox::warning(this, "警告", "获取房型数据失败，可能影响筛选功能");
    }
}

void RoomStatusManager::applyFilters()
{
    if (!roomModel) {
        return;
    }
    
    QString whereClause;
    
    // 添加状态筛选
    QString status = ui->cmbStatus->currentData().toString();
    if (!status.isEmpty()) {
        whereClause += QString("r.status = '%1'").arg(status);
    }
    
    // 添加楼层筛选
    int floor = ui->cmbFloor->currentData().toInt();
    if (floor > 0) {
        if (!whereClause.isEmpty()) whereClause += " AND ";
        whereClause += QString("r.floor = %1").arg(floor);
    }
    
    // 添加房型筛选
    int roomTypeId = ui->cmbRoomType->currentData().toInt();
    if (roomTypeId > 0) {
        if (!whereClause.isEmpty()) whereClause += " AND ";
        whereClause += QString("r.type_id = %1").arg(roomTypeId);
    }
    
    // 构建完整的SQL查询
    QString sql = "SELECT r.room_id, r.room_number, rt.name as room_type, r.floor, r.status "
                 "FROM room r "
                 "LEFT JOIN room_type rt ON r.type_id = rt.type_id ";
    
    if (!whereClause.isEmpty()) {
        sql += "WHERE " + whereClause;
    }
    
    sql += " ORDER BY r.room_id";
    
    // 执行查询
    roomModel->setQuery(sql, DBHelper::getInstance()->getDatabase());
    ui->tableView->resizeColumnsToContents();
}

void RoomStatusManager::showRoomDetails(int roomId)
{
    if (roomId <= 0) {
        return;
    }
    
    // 获取房间详情
    QString sql = QString("SELECT r.room_id, r.room_number, r.floor, r.status, "
                         "rt.name as room_type_name, rt.area, rt.bed_type, rt.price_per_day, rt.facilities "
                         "FROM room r "
                         "LEFT JOIN room_type rt ON r.type_id = rt.type_id "
                         "WHERE r.room_id = %1").arg(roomId);
    
    QSqlQuery query(DBHelper::getInstance()->getDatabase());
    if (!query.exec(sql)) {
        QMessageBox::critical(this, "错误", "获取房间详情失败: " + query.lastError().text());
        return;
    }
    
    if (query.next()) {
        // 创建房间详情对话框
        QDialog *detailDialog = new QDialog(this);
        detailDialog->setWindowTitle("房间详情");
        detailDialog->resize(500, 400);
        
        // 创建文本编辑框显示房间详情
        QTextEdit *textEdit = new QTextEdit(detailDialog);
        textEdit->setReadOnly(true);
        
        // 构建房间详情内容
        QString detail = "==================== 房间详情 ====================";
        detail += "\n\n房间ID: " + QString::number(roomId);
        detail += "\n房间号: " + query.value("room_number").toString();
        detail += "\n楼层: " + query.value("floor").toString() + "楼";
        detail += "\n房间状态: " + query.value("status").toString();
        detail += "\n房型: " + query.value("room_type_name").toString();
        detail += "\n面积: " + QString("%1").arg(query.value("area").toDouble(), 0, 'f', 1) + " m²";
        detail += "\n床型: " + query.value("bed_type").toString();
        detail += "\n单日定价: " + QString("%1").arg(query.value("price_per_day").toDouble(), 0, 'f', 2) + " 元";
        detail += "\n配套设施: " + query.value("facilities").toString();
        detail += "\n\n==================== 房间详情结束 ====================";
        
        textEdit->setPlainText(detail);
        
        // 设置布局
        QVBoxLayout *layout = new QVBoxLayout(detailDialog);
        layout->addWidget(textEdit);
        detailDialog->setLayout(layout);
        
        // 显示房间详情
        detailDialog->exec();
        
        delete detailDialog;
    } else {
        QMessageBox::warning(this, "警告", "未找到房间ID为 " + QString::number(roomId) + " 的房间详情");
    }
}

// 按钮槽函数实现
void RoomStatusManager::on_btnRefresh_clicked()
{
    loadRooms();
    QMessageBox::information(this, "成功", "房间状态已刷新");
}

void RoomStatusManager::on_btnClose_clicked()
{
    close();
}

// 房间状态更新定时器
void RoomStatusManager::onTimerTimeout()
{
    loadRooms();
    qDebug() << "房间状态已自动更新";
}

// 房间选择变化
void RoomStatusManager::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid() && roomModel) {
        // 获取房间ID（房间ID在第0列）
        int roomId = roomModel->data(roomModel->index(index.row(), 0)).toInt();
        showRoomDetails(roomId);
    }
}

void RoomStatusManager::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid() && roomModel) {
        // 获取房间ID（房间ID在第0列）
        int roomId = roomModel->data(roomModel->index(index.row(), 0)).toInt();
        showRoomDetails(roomId);
    }
}

// 状态筛选变化
void RoomStatusManager::on_cmbStatus_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    applyFilters();
}

// 楼层筛选变化
void RoomStatusManager::on_cmbFloor_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    applyFilters();
}

// 房型筛选变化
void RoomStatusManager::on_cmbRoomType_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    applyFilters();
}
