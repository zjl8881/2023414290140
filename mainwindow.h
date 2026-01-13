#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include "stats_worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnReserve_clicked();      // 预约按钮
    void on_btnStats_clicked();        // 统计按钮
    void on_btnReportFault_clicked();  // 报修按钮
    void on_btnAddDevice_clicked();    // 新增设备按钮
    void on_btnReturn_clicked();       // 新增归还槽函数

    void on_btnRefresh_clicked();

private:
    Ui::MainWindow *ui;
    void updateTable();
};
#endif
