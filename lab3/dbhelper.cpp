#include "dbhelper.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

// 初始化静态成员
DBHelper* DBHelper::instance = nullptr;
QMutex DBHelper::mutex;

DBHelper::DBHelper()
{
    // 设置数据库名称和绝对路径
    dbName = "hotel.db";
    dbPath = "C:/Users/86176/Desktop/hotel.db";
}

DBHelper::~DBHelper()
{
    disconnect();
}

DBHelper* DBHelper::getInstance()
{
    // 双重检查锁定模式，确保线程安全
    if (instance == nullptr) {
        mutex.lock();
        if (instance == nullptr) {
            instance = new DBHelper();
        }
        mutex.unlock();
    }
    return instance;
}

bool DBHelper::connect()
{
    // 检查数据库是否已连接
    if (db.isOpen()) {
        return true;
    }
    
    // 添加SQLite数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    
    // 设置数据库路径
    db.setDatabaseName(dbPath);
    
    // 打开数据库
    if (!db.open()) {
        QMessageBox::critical(nullptr, "数据库连接错误", 
                             "无法连接到数据库: " + db.lastError().text());
        qDebug() << "数据库连接失败: " << db.lastError().text();
        return false;
    }
    
    qDebug() << "数据库连接成功";
    return true;
}

void DBHelper::disconnect()
{
    if (db.isOpen()) {
        db.close();
        QSqlDatabase::removeDatabase(db.connectionName());
        qDebug() << "数据库连接已断开";
    }
}

QSqlQuery DBHelper::executeQuery(const QString &sql)
{
    if (!db.isOpen()) {
        if (!connect()) {
            return QSqlQuery();
        }
    }
    
    QSqlQuery query(db);
    if (!query.exec(sql)) {
        QMessageBox::critical(nullptr, "SQL执行错误", 
                             "查询执行失败: " + query.lastError().text() + "\nSQL: " + sql);
        qDebug() << "查询执行失败: " << query.lastError().text() << "\nSQL: " << sql;
    }
    
    return query;
}

bool DBHelper::executeUpdate(const QString &sql)
{
    if (!db.isOpen()) {
        if (!connect()) {
            return false;
        }
    }
    
    QSqlQuery query(db);
    if (!query.exec(sql)) {
        QMessageBox::critical(nullptr, "SQL执行错误", 
                             "更新执行失败: " + query.lastError().text() + "\nSQL: " + sql);
        qDebug() << "更新执行失败: " << query.lastError().text() << "\nSQL: " << sql;
        return false;
    }
    
    return true;
}

bool DBHelper::beginTransaction()
{
    if (!db.isOpen()) {
        if (!connect()) {
            return false;
        }
    }
    
    return db.transaction();
}

bool DBHelper::commitTransaction()
{
    if (!db.isOpen()) {
        return false;
    }
    
    return db.commit();
}

bool DBHelper::rollbackTransaction()
{
    if (!db.isOpen()) {
        return false;
    }
    
    return db.rollback();
}

QSqlDatabase DBHelper::getDatabase()
{
    if (!db.isOpen()) {
        connect();
    }
    
    return db;
}
