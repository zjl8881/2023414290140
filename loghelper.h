#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QObject>
#include <QString>

class LogHelper
{
public:
    static LogHelper& getInstance();

    void writeLog(const QString& message, const QString& level = "INFO");

private:
    LogHelper();
    ~LogHelper();
    LogHelper(const LogHelper&) = delete;
    LogHelper& operator=(const LogHelper&) = delete;

    QString m_logFilePath;
};

#endif // LOGHELPER_H
