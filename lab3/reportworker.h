#ifndef REPORTWORKER_H
#define REPORTWORKER_H

#include <QObject>

class ReportWorker : public QObject
{
    Q_OBJECT
public:
    explicit ReportWorker(QString type, QObject *parent = nullptr);

public slots:
    void process(); // 耗时任务入口

signals:
    void progressUpdated(int value); // 进度信号
    void finished(bool success, QString message); // 完成信号

private:
    QString m_type; // 区分是 "doctor" 还是 "department"
};

#endif
