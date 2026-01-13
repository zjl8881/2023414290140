#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QMessageBox>
#include <QMutex>

class DBHelper
{
public:
    // 获取单例实例
    static DBHelper* getInstance();
    
    // 连接数据库
    bool connect();
    
    // 断开数据库连接
    void disconnect();
    
    // 执行SQL语句（查询）
    QSqlQuery executeQuery(const QString &sql);
    
    // 执行SQL语句（非查询，如INSERT、UPDATE、DELETE）
    bool executeUpdate(const QString &sql);
    
    // 开始事务
    bool beginTransaction();
    
    // 提交事务
    bool commitTransaction();
    
    // 回滚事务
    bool rollbackTransaction();
    
    // 获取数据库实例
    QSqlDatabase getDatabase();
    
private:
    // 私有构造函数，防止外部实例化
    DBHelper();
    
    // 私有析构函数
    ~DBHelper();
    
    // 拷贝构造函数和赋值运算符设为私有，防止拷贝
    DBHelper(const DBHelper &);
    DBHelper& operator=(const DBHelper &);
    
    static DBHelper* instance; // 单例实例
    static QMutex mutex; // 互斥锁，用于线程安全
    
    QSqlDatabase db; // 数据库对象
    QString dbName; // 数据库名称
    QString dbPath; // 数据库路径
};

#endif // DBHELPER_H
