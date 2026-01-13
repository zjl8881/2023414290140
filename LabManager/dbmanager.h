#ifndef DBMANAGER_H
#define DBMANAGER_H
啊伟大伟大
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlRecord>
#include <QDateTime>
#include <QVariant>
#include <QDebug>

class DbManager {
public:
    static DbManager& getInstance() {
        static DbManager instance;
        return instance;
    }

    QSqlTableModel *deviceTabModel;
    QSqlTableModel *recordsTabModel;
    QItemSelectionModel *theDeviceSelection;

    void initDatabase() {
        database = QSqlDatabase::addDatabase("QSQLITE");
        QString aFile = "C:/Users/86176/Desktop/lab_management1.db";
        database.setDatabaseName(aFile);

        if(!database.open()) {
            qDebug() << "failed to open database";
        } else {
            QSqlQuery q;
            // 确保设备表包含字段
            q.exec("CREATE TABLE IF NOT EXISTS devices ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT, "
                   "model TEXT, "
                   "total_qty INTEGER, "
                   "current_qty INTEGER, "
                   "status TEXT, "
                   "reserved_qty INTEGER DEFAULT 0)");

            // 确保故障表存在，包含报修原因字段
            q.exec("CREATE TABLE IF NOT EXISTS faults ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "device_id INTEGER, "
                   "fault_qty INTEGER, "
                   "reason TEXT, "
                   "report_time DATETIME)");
        }
    }

    bool initDeviceModel() {
        if (!database.isOpen()) return false;
        deviceTabModel = new QSqlTableModel(nullptr, database);
        deviceTabModel->setTable("devices");
        deviceTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        deviceTabModel->select();

        theDeviceSelection = new QItemSelectionModel(deviceTabModel);
        return true;
    }

    // 新增设备逻辑
    bool addDevice(const QVariantMap &data) {
        if (!database.isOpen()) return false;

        int total = data["total_qty"].toInt();
        int current = data["current_qty"].toInt();
        int reserved = 0;

        int normal = current + reserved;
        int fault = total - normal;
        QString statusStr = QString("正常:%1, 故障中:%2").arg(normal).arg(fault);

        QSqlQuery q(database);
        q.prepare("INSERT INTO devices (name, model, total_qty, current_qty, status, reserved_qty) "
                  "VALUES (:name, :model, :total, :current, :status, :res)");
        q.bindValue(":name", data["name"]);
        q.bindValue(":model", data["model"]);
        q.bindValue(":total", total);
        q.bindValue(":current", current);
        q.bindValue(":status", statusStr);
        q.bindValue(":res", reserved);

        if (!q.exec()) return false;
        deviceTabModel->select();
        return true;
    }

    bool reserveDevice(int deviceId, const QString &userName, int count) {
        if (!database.isOpen()) return false;

        database.transaction(); // 开启事务保证数据一致性
        QSqlQuery q(database);

        // --- 步骤 1: 更新 devices 表 (原有逻辑) ---
        q.prepare("UPDATE devices SET current_qty = current_qty - :count, "
                  "reserved_qty = reserved_qty + :count WHERE id = :id AND current_qty >= :count");
        q.bindValue(":count", count);
        q.bindValue(":id", deviceId);

        if (!q.exec() || q.numRowsAffected() == 0) {
            database.rollback();
            return false;
        }

        // --- 步骤 2: 【关键新增】插入到 records 表 ---
        q.prepare("INSERT INTO records (device_id, user_name, apply_time) "
                  "VALUES (:did, :user, :time)");
        q.bindValue(":did", deviceId);
        q.bindValue(":user", userName);
        // 使用当前系统时间作为申请时间
        q.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

        if (!q.exec()) {
            qDebug() << "写入预约流水失败:" << q.lastError().text();
            database.rollback();
            return false;
        }

        // --- 步骤 3: 刷新状态并提交 ---
        updateStatusString(deviceId); // 刷新“正常/故障”字符串
        database.commit();

        if(deviceTabModel) deviceTabModel->select(); // 刷新 UI 表格
        return true;
    }

    // 归还逻辑
    bool returnDevice(int deviceId, int count) {
        if (!database.isOpen()) return false;
        database.transaction();
        QSqlQuery q(database);

        q.prepare("UPDATE devices SET current_qty = current_qty + :count, "
                  "reserved_qty = MAX(0, reserved_qty - :count) WHERE id = :id");
        q.bindValue(":count", count);
        q.bindValue(":id", deviceId);

        if (!q.exec()) {
            database.rollback();
            return false;
        }

        updateStatusString(deviceId);
        database.commit();
        deviceTabModel->select();
        return true;
    }

    // 优化后的报修逻辑：修改库存并插入 faults 表
    bool reportFault(int deviceId, int count, const QString &description) {
        if (!database.isOpen()) return false;

        // 开启事务，确保库存更新和记录插入同时成功
        database.transaction();
        QSqlQuery q(database);

        // 1. 更新 devices 表：减少可用库存 (current_qty)
        // 注意：库存不能减为负数，所以使用 CASE WHEN 或 MAX
        q.prepare("UPDATE devices SET current_qty = CASE WHEN current_qty >= :count "
                  "THEN current_qty - :count ELSE 0 END WHERE id = :id");
        q.bindValue(":count", count);
        q.bindValue(":id", deviceId);

        if (!q.exec()) {
            database.rollback();
            qDebug() << "更新库存失败:" << q.lastError().text();
            return false;
        }

        // 2. 【核心修改】向 faults 表插入报修记录
        // id 自动生成，is_fixed 默认为 0 (未修复)，时间由 QDateTime 生成
        q.prepare("INSERT INTO faults (device_id, description, report_time, is_fixed) "
                  "VALUES (:did, :desc, :time, :fixed)");
        q.bindValue(":did", deviceId);
        q.bindValue(":desc", description);
        q.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        q.bindValue(":fixed", 0); // 0 表示故障中，1 表示已修复

        if (!q.exec()) {
            database.rollback();
            qDebug() << "插入报修记录失败:" << q.lastError().text();
            return false;
        }

        // 3. 刷新状态字符串并提交
        updateStatusString(deviceId); // 重新计算“正常:X, 故障中:Y”并写入 status 字段
        database.commit();

        // 刷新 UI 模型
        if(deviceTabModel) deviceTabModel->select();

        return true;
    }


private:
    DbManager() { initDatabase(); }
    QSqlDatabase database;

    void updateStatusString(int deviceId) {
        QSqlQuery q(database);
        q.prepare("SELECT current_qty, reserved_qty, total_qty FROM devices WHERE id = :id");
        q.bindValue(":id", deviceId);
        if (q.exec() && q.next()) {
            int cur = q.value(0).toInt();
            int res = q.value(1).toInt();
            int tot = q.value(2).toInt();

            int normal = cur + res;
            int fault = tot - normal;

            QString newStatus = QString("正常:%1, 故障中:%2").arg(normal).arg(fault);

            QSqlQuery qUpdate(database);
            qUpdate.prepare("UPDATE devices SET status = :status WHERE id = :id");
            qUpdate.bindValue(":status", newStatus);
            qUpdate.bindValue(":id", deviceId);
            qUpdate.exec();
        }
    }
};

#endif
