#ifndef ROOMSTATUSMANAGER_H
#define ROOMSTATUSMANAGER_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTimer>
#include "dbhelper.h"

namespace Ui {
class RoomStatusManager;
}

class RoomStatusManager : public QDialog
{
    Q_OBJECT

public:
    explicit RoomStatusManager(QWidget *parent = nullptr);
    ~RoomStatusManager();

private slots:
    // 按钮槽函数
    void on_btnRefresh_clicked();
    void on_btnClose_clicked();
    
    // 房间状态更新定时器
    void onTimerTimeout();
    
    // 房间选择变化
    void on_tableView_clicked(const QModelIndex &index);
    void on_tableView_doubleClicked(const QModelIndex &index);
    
    // 状态筛选变化
    void on_cmbStatus_currentIndexChanged(int index);
    
    // 楼层筛选变化
    void on_cmbFloor_currentIndexChanged(int index);
    
    // 房型筛选变化
    void on_cmbRoomType_currentIndexChanged(int index);

private:
    Ui::RoomStatusManager *ui;
    
    // 数据模型
    QSqlQueryModel *roomModel;
    
    // 定时器，用于实时更新房间状态
    QTimer *statusUpdateTimer;
    
    // 初始化UI
    void initUI();
    
    // 初始化数据模型
    void initModel();
    
    // 初始化信号与槽连接
    void initConnections();
    
    // 加载房间数据
    void loadRooms();
    
    // 加载筛选条件
    void loadFilters();
    
    // 应用筛选条件
    void applyFilters();
    
    // 显示房间详情
    void showRoomDetails(int roomId);
    
    // 设置房间状态单元格样式
    void setRoomStatusStyle();
};

#endif // ROOMSTATUSMANAGER_H
