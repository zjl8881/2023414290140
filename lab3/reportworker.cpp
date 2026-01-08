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

    // 1. 为子线程创建唯一的数据库连接名
    QString connName = QString("Thread_Conn_%1").arg(quintptr(QThread::currentThreadId()));

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connName);
        db.setDatabaseName("C:/Users/86176/Desktop/lab3a.db");

        if (!db.open()) {
            emit finished(false, "数据库打开失败: " + db.lastError().text());
            return;
        }

        emit progressUpdated(30);

        QString content;
        QString fileName;
        QSqlQuery query(db);
        bool querySuccess = false;

        // 2. 执行统计逻辑
        if (m_type == "doctor") {
            fileName = "医生统计报表.txt";
            if (query.exec("SELECT COUNT(*) FROM doctor")) {
                if (query.next()) {
                    content = QString("医生总数统计: %1").arg(query.value(0).toInt());
                    querySuccess = true;
                }
            } else {
                QString reason = query.lastError().text();
                emit finished(false, "SQL执行失败，原因: " + reason);
                return;
            }
        } else if (m_type == "patient") {
            fileName = "患者统计报表.txt";
            if (query.exec("SELECT COUNT(*) FROM patient")) {
                if (query.next()) {
                    content = QString("患者总数统计: %1").arg(query.value(0).toInt());
                    querySuccess = true;
                }
            }
        } else if (m_type == "department") {
            fileName = "科室统计报表.txt";
            if (query.exec("SELECT COUNT(*) FROM department")) {
                if (query.next()) {
                    content = QString("科室总数统计: %1").arg(query.value(0).toInt());
                    querySuccess = true;
                }
            }
        }
        // --- 新增逻辑：处理药品统计报表 ---
        else if (m_type == "medicine") {
            fileName = "药品统计报表.txt";
            // 使用 IDatabase 中定义的表名 "medicines"
            if (query.exec("SELECT COUNT(*) FROM medicines")) {
                if (query.next()) {
                    content = QString("药品种类总数: %1").arg(query.value(0).toInt());
                    querySuccess = true;
                }
            } else {
                QString reason = query.lastError().text();
                emit finished(false, "药品统计SQL执行失败: " + reason);
                return;
            }
        }

        emit progressUpdated(70);

        // 3. 处理文件写入结果
        if (querySuccess && !content.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << "--- 医院管理系统统计报表 ---\n";
                out << "生成时间: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n";
                out << content;
                file.close();
                emit progressUpdated(100);
                emit finished(true, "报表已成功保存至项目目录: " + fileName);
            } else {
                emit finished(false, "文件创建失败，请检查磁盘权限。");
            }
        } else {
            if(!querySuccess)
                emit finished(false, "统计数据获取失败: " + query.lastError().text());
            else
                emit finished(false, "未获取到有效数据。");
        }

        db.close();
    }

    QSqlDatabase::removeDatabase(connName);
}
