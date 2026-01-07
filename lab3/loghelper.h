#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QObject>
#include <QString>

// 日志工具类（单例模式）
class LogHelper : public QObject
{
    Q_OBJECT  // Qt元对象系统必需
public:
    // 获取全局唯一实例
    static LogHelper& getInstance();

    // 声明日志写入接口
    // content：日志内容；type：日志类型（INFO/ERROR/WARN）
    void writeLog(const QString& content, const QString& type = "INFO");

private:
    // 私有构造函数（禁止外部实例化）
    explicit LogHelper(QObject *parent = nullptr);

    // 禁止拷贝和赋值（单例核心）
    LogHelper(const LogHelper&) = delete;
    LogHelper& operator=(const LogHelper&) = delete;
};

#endif // LOGHELPER_H
