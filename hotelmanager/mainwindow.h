#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "roomtypemanager.h"
#include "checkinmanager.h"
#include "checkoutmanager.h"
#include "ordermanager.h"
#include "roomstatusmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 导航菜单槽函数
    void on_actionRoomTypeManager_triggered();
    void on_actionCheckIn_triggered();
    void on_actionCheckOut_triggered();
    void on_actionOrderManager_triggered();
    void on_actionRoomStatus_triggered();
    void on_actionExit_triggered();

    // 工具栏按钮槽函数
    void on_btnRoomType_clicked();
    void on_btnCheckIn_clicked();
    void on_btnCheckOut_clicked();
    void on_btnOrder_clicked();
    void on_btnRoomStatus_clicked();

private:
    Ui::MainWindow *ui;
    
    // 功能模块窗口指针
    RoomTypeManager *roomTypeManager;
    CheckInManager *checkInManager;
    CheckOutManager *checkOutManager;
    OrderManager *orderManager;
    RoomStatusManager *roomStatusManager;
    
    // 初始化UI
    void initUI();
    
    // 初始化信号与槽连接
    void initConnections();
};

#endif // MAINWINDOW_H
