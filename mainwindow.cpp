#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "dialog_reserve.h"
#include "stats_worker.h"
#include <QMessageBox>
#include <QThread>
#include <QInputDialog>
#include "dialogadddevice.h"
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)哇哇哇哇哇哇哇
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    if(DbManager::getInstance().initDeviceModel()){
        QSqlTableModel *model = DbManager::getInstance().deviceTabModel;
        model->setHeaderData(0, Qt::Horizontal, "设备ID");
        model->setHeaderData(1, Qt::Horizontal, "设备名称");
        model->setHeaderData(2, Qt::Horizontal, "规格型号");
        model->setHeaderData(3, Qt::Horizontal, "库存总数");
        model->setHeaderData(4, Qt::Horizontal, "可使用数");
        model->setHeaderData(5, Qt::Horizontal, "当前状态");
        model->setHeaderData(6, Qt::Horizontal, "已预约数");

        ui->tableView->setModel(model);
        // 视觉调整：已预约数(6) 移到 当前状态(5) 之前
        ui->tableView->horizontalHeader()->moveSection(6, 5);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnRefresh_clicked() {
    DbManager::getInstance().deviceTabModel->select();
}

void MainWindow::on_btnAddDevice_clicked() {
    DialogAddDevice dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QString errorMsg;
        if (!dlg.validateData(errorMsg)) {
            QMessageBox::warning(this, "输入错误", errorMsg);
            return;
        }

        QVariantMap data = dlg.getDeviceData();
        if (DbManager::getInstance().addDevice(data)) {
            QMessageBox::information(this, "成功", "设备已入库");
            DbManager::getInstance().deviceTabModel->select();
        } else {
            QMessageBox::critical(this, "错误", "数据库写入失败");
        }
    }
}

void MainWindow::on_btnReserve_clicked() {
    DialogReserve dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QString name = dlg.getDevice();
        QString user = dlg.getUser();
        int count = dlg.getCount();

        // 根据名称查ID
        QSqlQuery q;
        q.prepare("SELECT id FROM devices WHERE name = :name");
        q.bindValue(":name", name);
        if (q.exec() && q.next()) {
            int id = q.value(0).toInt();
            if (DbManager::getInstance().reserveDevice(id, user, count)) {
                QMessageBox::information(this, "成功", "预约申请已提交！");
            } else {
                QMessageBox::warning(this, "失败", "库存不足或数据库错误。");
            }
        }
    }
}

// 核心修复部分：报修逻辑
void MainWindow::on_btnReportFault_clicked() {
    QModelIndex curIndex = ui->tableView->currentIndex();
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, "提示", "请先在表格中选择要报修的设备");
        return;
    }

    int row = curIndex.row();
    int deviceId = DbManager::getInstance().deviceTabModel->index(row, 0).data().toInt();
    QString deviceName = DbManager::getInstance().deviceTabModel->index(row, 1).data().toString();

    // 1. 询问报修数量
    bool ok;
    int count = QInputDialog::getInt(this, "设备报修",
                                     QString("设备：%1\n请输入故障设备数量:").arg(deviceName),
                                     1, 1, 999, 1, &ok);
    if (!ok) return;

    // 2. 询问故障描述 (对应数据库字段 description)
    QString description = QInputDialog::getText(this, "故障描述",
                                                "请输入故障具体情况:",
                                                QLineEdit::Normal, "", &ok);
    if (!ok || description.isEmpty()) {
        description = "未填写描述"; // 默认值
    }

    // 3. 调用数据库接口
    if (DbManager::getInstance().reportFault(deviceId, count, description)) {
        QMessageBox::information(this, "成功", "报修记录已提交，系统已更新库存状态");
    } else {
        QMessageBox::critical(this, "错误", "报修失败，请检查可用库存是否足够");
    }
}

void MainWindow::on_btnStats_clicked() {
    QThread *thread = new QThread;
    StatsWorker *worker = new StatsWorker;
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &StatsWorker::doWork);
    connect(worker, &StatsWorker::resultReady, this, [=](const QString &msg){
        QMessageBox::information(this, "统计报表", msg);
        thread->quit();
    });
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}

void MainWindow::on_btnReturn_clicked() {
    QModelIndex curIndex = ui->tableView->currentIndex();
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, "提示", "请选择设备");
        return;
    }

    int row = curIndex.row();
    int deviceId = DbManager::getInstance().deviceTabModel->index(row, 0).data().toInt();
    int reservedQty = DbManager::getInstance().deviceTabModel->index(row, 6).data().toInt();

    if (reservedQty <= 0) {
        QMessageBox::information(this, "提示", "无预约记录");
        return;
    }

    bool ok;
    int count = QInputDialog::getInt(this, "归还", "归还数量:", reservedQty, 1, reservedQty, 1, &ok);
    if (ok) {
        DbManager::getInstance().returnDevice(deviceId, count);
    }
}

