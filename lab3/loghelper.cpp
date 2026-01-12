#include "loghelper.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

// 单例实例实现
LogHelper& LogHelper::getInstance()
{
    static LogHelper instance;
    return instance;
}

// 日志写入逻辑实现
void LogHelper::writeLog(const QString& content, const QString& type)
{
    // 1. 打开日志文件（追加模式，不存在则自动创建）
    QFile file("operation_log.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return;  // 打开失败则直接返回
    }

    // 2. 构造日志内容（时间戳 + 类型 + 内容）
    QTextStream out(&file);
    QString logLine = QString("[%1] [%2] %3\n")
                          .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                          .arg(type)
                          .arg(content);

    // 3. 写入并关闭文件
    out << logLine;
    file.close();
}

// 私有构造函数实现
LogHelper::LogHelper(QObject *parent)
    : QObject(parent)
{
    // 构造函数无需额外逻辑
}
