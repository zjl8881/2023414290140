#ifndef CHECKINMANAGER_H
#define CHECKINMANAGER_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QRegExpValidator>
#include "dbhelper.h"

namespace Ui {
class CheckInManager;
}

class CheckInManager : public QDialog
{
    Q_OBJECT

public:
    explicit CheckInManager(QWidget *parent = nullptr);q委屈委屈我
    ~CheckInManager();

private slots:
    // 按钮槽函数
    void on_btnCheckIn_clicked();
    void on_btnCancel_clicked();
    void on_btnRefresh_clicked();
    
    // 房型选择变化
    void on_cmbRoomType_currentIndexChanged(int index);

    // 房间选择变化
    void on_cmbRoom_currentIndexChanged(int index);
    
    // 日期变化
    void on_deCheckIn_dateChanged(const QDate &date);
    void on_deCheckOut_dateChanged(const QDate &date);
    
    // 搜索客户
    void on_btnSearchCustomer_clicked();

private:
    Ui::CheckInManager *ui;
    
    // 数据模型
    QSqlQueryModel *roomTypeModel;
    QSqlQueryModel *roomModel;
    QSqlQueryModel *customerModel;
    
    // 验证器
    QRegExpValidator *idCardValidator;
    QRegExpValidator *phoneValidator;
    
    // 初始化UI
    void initUI();
    
    // 初始化数据模型
    void initModels();
    
    // 初始化验证器
    void initValidators();
    
    // 初始化信号与槽连接
    void initConnections();
    
    // 清空表单
    void clearForm();
    
    // 加载房型数据
    void loadRoomTypes();
    
    // 根据房型加载可用房间
    void loadRoomsByType(int typeId);
    
    // 计算预计金额
    void calculateExpectedAmount();
    
    // 验证表单数据
    bool validateForm();
    
    // 处理入住登记
    bool processCheckIn();
};

#endif // CHECKINMANAGER_H
