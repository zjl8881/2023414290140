#ifndef STATS_WORKER_H
#define STATS_WORKER_H

#include <QObject>
#include <QString>
#include <QVariant> // 必须包含，解决 "incomplete type 'class QVariant'"

class StatsWorker : public QObject {
    Q_OBJECT
public:
    explicit StatsWorker(QObject *parent = nullptr);

signals:
    void resultReady(const QString &msg);

public slots:
    void doWork(); // 统计逻辑
};

#endif
