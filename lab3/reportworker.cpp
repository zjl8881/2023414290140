#include "reportworker.h"
#include <QThread>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

ReportWorker::ReportWorker(QString type, QObject *parent) : QObject(parent), m_type(type) {}

void ReportWorker::process() {
    emit progressUpdated(10);

    // 1. 定义连接名：使用当前线程的 ID 确保唯一性
    // 这避免了多个后台线程同时生成报表时发生连接冲突
    QString connName = QString("Thread_Conn_%1").arg(quintptr(QThread::currentThreadId()));

    // 2. 模仿 IDatabase 的逻辑配置数据库
    {
        QSqlDatabase db;
        // 如果连接池里已经有这个名字的连接，直接复用；否则新建
        if (QSqlDatabase::contains(connName)) {
            db = QSqlDatabase::database(connName);
        } else {
            // 这里必须指定 "QSQLITE" 驱动和唯一的连接名 connName
            db = QSqlDatabase::addDatabase("QSQLITE", connName);

            // 模仿你的代码：使用相同的文件路径
            QString aFile = "C:/Users/86176/Desktop/lab3a.db";
            db.setDatabaseName(aFile);
        }

        // 3. 尝试打开数据库
        if (!db.open()) {
            qDebug() << "后台线程打开数据库失败:" << db.lastError().text();
            emit finished(false, "后台数据库连接失败");
            return;
        } else {
            qDebug() << "后台线程开启成功，连接名:" << db.connectionName();
        }

        emit progressUpdated(30);

        QString content;
        QString fileName;

        // 4. 执行统计查询 (必须将 db 对象传给 QSqlQuery)
        QSqlQuery query(db);
        if (m_type == "doctor") {
            fileName = "医生统计报表.txt";
            if (query.exec("SELECT COUNT(*) FROM doctor") && query.next()) {
                content = QString("医生总数统计: %1").arg(query.value(0).toInt());
            }
        } else {
            fileName = "科室统计报表.txt";
            if (query.exec("SELECT COUNT(*) FROM department") && query.next()) {
                content = QString("科室总数统计: %1").arg(query.value(0).toInt());
            }
        }

        // 5. 生成报表文件逻辑
        if (!content.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << "--- 统计报表 ---\n";
                out << "生成时间: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n";
                out << content;
                file.close();
                emit progressUpdated(100);
                emit finished(true, "报表已保存至: " + fileName);
            } else {
                emit finished(false, "无法写入文件，请检查权限");
            }
        } else {
            emit finished(false, "数据库查询返回空结果");
        }

        // 6. 操作完成后关闭连接
        db.close();
    }

    // 7. 彻底移除连接名（防止内存中残留过多的临时连接名）
    QSqlDatabase::removeDatabase(connName);
}
