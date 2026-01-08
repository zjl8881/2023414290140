#ifndef REPORTWORKER_H
#define REPORTWORKER_H

#include <QObject>

class ReportWorker : public QObject
{
    Q_OBJECT
public:
    // 构造函数接收业务类型：doctor, department, patient, medicines
    explicit ReportWorker(QString type, QObject *parent = nullptr);

public slots:
    void process(); // 耗时统计任务

signals:
    void progressUpdated(int value);
    void finished(bool success, QString message);

private:
    QString m_type;
};

#endif
