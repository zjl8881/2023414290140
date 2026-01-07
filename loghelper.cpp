#include "loghelper.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>

LogHelper& LogHelper::getInstance()
{
    static LogHelper instance;
    return instance;
}

LogHelper::LogHelper()
{
    QString appDir = QCoreApplication::applicationDirPath();
    m_logFilePath = appDir + "/hospital_system.log";
}

LogHelper::~LogHelper()
{
}

void LogHelper::writeLog(const QString& message, const QString& level)
{
    QFile file(m_logFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString logEntry = QString("[%1] [%2] %3\n")
                               .arg(timestamp)
                               .arg(level)
                               .arg(message);

        stream << logEntry;
        file.close();
    }
}
