#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

// 日志写入函数
void logMessage(const QString &content) {
    // 创建logs目录（若不存在）
    QDir logDir("logs");
    if (!logDir.exists()) {
        logDir.mkpath(".");
    }
    
    // 日志文件路径：logs/YYYY-MM-DD.log
    QString logFileName = logDir.filePath(
        QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".log"
    );
    
    // 打开文件并追加日志（带时间戳）
    QFile logFile(logFileName);
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") 
            << " - " << content << "\n";
        logFile.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 记录程序启动日志
    logMessage("程序启动");
    
    MainWindow w;
    w.show();
    
    int exitCode = a.exec();
    
    // 记录程序退出日志
    logMessage("程序退出，退出码：" + QString::number(exitCode));
    
    return exitCode;
}
