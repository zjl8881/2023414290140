// stats_worker.h
#ifndef STATS_WORKER_H
#define STATS_WORKER_H
#include <QObject>

class StatsWorker : public QObject {
    Q_OBJECT
public slots:
    void doWork(); // 统计逻辑
signals:
    void resultReady(const QString &msg);
};
#endif

// stats_worker.cpp
#include "stats_worker.h"
#include <QSqlQuery>
#include <QThread>

void StatsWorker::doWork() {
    QThread::msleep(2000); // 模拟耗时操作
    QSqlQuery query("SELECT name, current_qty FROM devices");
    QString report = "库存简报:\n";
    while (query.next()) {
        report += query.value(0).toString() + ": 剩余 " + query.value(1).toString() + "\n";
    }
    emit resultReady(report);
}
