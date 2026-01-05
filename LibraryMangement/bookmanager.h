#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "book.h"

class BookManager : public QObject {
    Q_OBJECT
public:
    explicit BookManager(QObject *parent = nullptr);
    ~BookManager();

    // 数据库连接/关闭
    bool connectDatabase();
    void closeDatabase();

    // 图书数据库操作示例（增/查）
    bool addBook(const Book &book);       // 添加图书到数据库
    Book queryBookById(const QString &id);// 根据编号查询图书

private:
    QSqlDatabase db;  // 数据库对象
    // 初始化图书表（首次连接时创建表）
    void initBookTable();
};

#endif // BOOKMANAGER_H
