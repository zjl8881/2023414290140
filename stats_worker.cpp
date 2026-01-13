#include "stats_worker.h"
#include <QSqlQuery>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlError>

StatsWorker::StatsWorker(QObject *parent) : QObject(parent) {}

void StatsWorker::doWork() {
    QString connName = QString("Conn_%1").arg(quintptr(QThread::currentThreadId()));
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connName);
        db.setDatabaseName("C:/Users/86176/Desktop/lab_management1.db");

        if (!db.open()) {
            emit resultReady("无法连接数据库");
            return;
        }

        QSqlQuery query(db);
        QString report = "库存实时统计:\n";
        if (query.exec("SELECT name, current_qty FROM devices")) {
            while (query.next()) {
                report += QString("%1: %2 台\n").arg(query.value(0).toString(), query.value(1).toString());
            }
        }
        emit resultReady(report);
        db.close();
    }
    QSqlDatabase::removeDatabase(connName);
}
