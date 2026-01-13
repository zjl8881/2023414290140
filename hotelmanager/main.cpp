#include "mainwindow.h"
#include <QApplication>
#include "dbhelper.h"
#include <QSqlQuery>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 初始化数据库
    DBHelper* dbHelper = DBHelper::getInstance();
    
    // 检查数据库文件是否存在，如果不存在则创建并初始化
    QString dbPath = "C:/Users/86176/Desktop/hotel.db";
    if (!QFile::exists(dbPath)) {
        QMessageBox::information(nullptr, "数据库初始化", "首次运行，正在初始化数据库...");
        
        // 读取SQL脚本文件
        QFile sqlFile("hotel_db.sql");
        if (!sqlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "错误", "无法打开数据库初始化脚本文件");
            return -1;
        }
        
        QString sqlScript = sqlFile.readAll();
        sqlFile.close();
        
        // 执行SQL脚本
        if (!dbHelper->beginTransaction()) {
            QMessageBox::critical(nullptr, "错误", "无法开始事务");
            return -1;
        }
        
        QSqlQuery query(dbHelper->getDatabase());
        QStringList sqlCommands = sqlScript.split(";", QString::SkipEmptyParts);
        bool success = true;
        
        for (const QString &sql : sqlCommands) {
            if (!sql.trimmed().isEmpty() && !query.exec(sql)) {
                QMessageBox::critical(nullptr, "错误", "执行SQL脚本失败: " + query.lastError().text());
                success = false;
                break;
            }
        }
        
        if (success) {
            dbHelper->commitTransaction();
            QMessageBox::information(nullptr, "成功", "数据库初始化完成");
        } else {
            dbHelper->rollbackTransaction();
            QMessageBox::critical(nullptr, "错误", "数据库初始化失败");
            return -1;
        }
    }
    
    // 创建并显示主窗口
    MainWindow w;
    w.show();
    
    return a.exec();
}
