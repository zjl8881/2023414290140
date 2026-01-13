#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    roomTypeManager(nullptr),
    checkInManager(nullptr),
    checkOutManager(nullptr),
    orderManager(nullptr),
    roomStatusManager(nullptr)
{
    ui->setupUi(this);
    initUI();
    initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    
    // 释放功能模块窗口资源
    if (roomTypeManager) {
        delete roomTypeManager;
    }
    if (checkInManager) {
        delete checkInManager;
    }
    if (checkOutManager) {
        delete checkOutManager;
    }
    if (orderManager) {
        delete orderManager;
    }
    if (roomStatusManager) {
        delete roomStatusManager;
    }
}

void MainWindow::initUI()
{
    // 设置窗口标题
    setWindowTitle("酒店入住与预订管理系统");
    
    // 设置窗口大小
    resize(800, 600);
    
    // 设置状态栏信息
    ui->statusBar->showMessage("欢迎使用酒店入住与预订管理系统");
}

void MainWindow::initConnections()
{
    // 这里可以添加额外的信号与槽连接
}

// 导航菜单槽函数实现
void MainWindow::on_actionRoomTypeManager_triggered()
{
    if (!roomTypeManager) {
        roomTypeManager = new RoomTypeManager(this);
    }
    roomTypeManager->show();
    roomTypeManager->raise();
    roomTypeManager->activateWindow();
}

void MainWindow::on_actionCheckIn_triggered()
{
    if (!checkInManager) {
        checkInManager = new CheckInManager(this);
    }
    checkInManager->show();
    checkInManager->raise();
    checkInManager->activateWindow();
}

void MainWindow::on_actionCheckOut_triggered()
{
    if (!checkOutManager) {
        checkOutManager = new CheckOutManager(this);
    }
    checkOutManager->show();
    checkOutManager->raise();
    checkOutManager->activateWindow();
}

void MainWindow::on_actionOrderManager_triggered()
{
    if (!orderManager) {
        orderManager = new OrderManager(this);
    }
    orderManager->show();
    orderManager->raise();
    orderManager->activateWindow();
}

void MainWindow::on_actionRoomStatus_triggered()
{
    if (!roomStatusManager) {
        roomStatusManager = new RoomStatusManager(this);
    }
    roomStatusManager->show();
    roomStatusManager->raise();
    roomStatusManager->activateWindow();
}

void MainWindow::on_actionExit_triggered()
{
    // 询问用户是否确认退出
    if (QMessageBox::question(this, "退出系统", "确定要退出酒店管理系统吗？", 
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        close();
    }
}

// 工具栏按钮槽函数实现
void MainWindow::on_btnRoomType_clicked()
{
    on_actionRoomTypeManager_triggered();
}

void MainWindow::on_btnCheckIn_clicked()
{
    on_actionCheckIn_triggered();
}

void MainWindow::on_btnCheckOut_clicked()
{
    on_actionCheckOut_triggered();
}

void MainWindow::on_btnOrder_clicked()
{
    on_actionOrderManager_triggered();
}

void MainWindow::on_btnRoomStatus_clicked()
{
    on_actionRoomStatus_triggered();
}
