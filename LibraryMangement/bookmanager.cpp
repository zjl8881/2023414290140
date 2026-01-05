#include "bookmanager.h"

BookManager::BookManager(QObject *parent) : QObject(parent) {
    // 初始化连接 + 创建图书表
    if (connectDatabase()) {
        initBookTable();
    }
}

BookManager::~BookManager() {
    closeDatabase();
}

bool BookManager::connectDatabase() {
    // 避免重复添加驱动
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL");
        // ========== 请修改为你的Navicat配置 ==========
        db.setHostName("localhost");    // 数据库主机
        db.setDatabaseName("library_db");// 数据库名（需先在Navicat创建）
        db.setUserName("root");         // 数据库用户名
        db.setPassword("123123");       // 数据库密码
        db.setPort(3306);               // 端口
    }

    if (db.open()) {
        qDebug() << "数据库连接成功！";
        return true;
    } else {
        qDebug() << "数据库连接失败：" << db.lastError().text();
        return false;
    }
}

void BookManager::closeDatabase() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "数据库已关闭";
    }
}

void BookManager::initBookTable() {
    // 创建图书表：编号(主键)、名称、作者、出版社、价格、库存
    QSqlQuery query;
    QString createSql = R"(
        CREATE TABLE IF NOT EXISTS book (
            book_id VARCHAR(20) PRIMARY KEY,
            book_name VARCHAR(50) NOT NULL,
            book_author VARCHAR(30) NOT NULL,
            book_press VARCHAR(50) NOT NULL,
            book_price DOUBLE NOT NULL,
            book_stock INT NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
    )";

    if (!query.exec(createSql)) {
        qDebug() << "创建图书表失败：" << query.lastError().text();
    } else {
        qDebug() << "图书表初始化成功（存在则跳过创建）";
    }
}

bool BookManager::addBook(const Book &book) {
    if (!db.isOpen()) {
        qDebug() << "数据库未连接，添加图书失败";
        return false;
    }

    QSqlQuery query;
    // 预处理SQL，避免注入
    query.prepare(R"(
        INSERT INTO book (book_id, book_name, book_author, book_press, book_price, book_stock)
        VALUES (:id, :name, :author, :press, :price, :stock)
    )");
    query.bindValue(":id", book.getId());
    query.bindValue(":name", book.getName());
    query.bindValue(":author", book.getAuthor());
    query.bindValue(":press", book.getPress());
    query.bindValue(":price", book.getPrice());
    query.bindValue(":stock", book.getStock());

    if (query.exec()) {
        qDebug() << "图书添加成功：" << book.getName();
        return true;
    } else {
        qDebug() << "图书添加失败：" << query.lastError().text();
        return false;
    }
}

Book BookManager::queryBookById(const QString &id) {
    Book emptyBook; // 默认返回空图书
    if (!db.isOpen()) {
        qDebug() << "数据库未连接，查询图书失败";
        return emptyBook;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM book WHERE book_id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // 从查询结果构造图书对象
        Book book(
            query.value("book_id").toString(),
            query.value("book_name").toString(),
            query.value("book_author").toString(),
            query.value("book_press").toString(),
            query.value("book_price").toDouble(),
            query.value("book_stock").toInt()
            );
        qDebug() << "查询到图书：" << book.getName();
        return book;
    } else {
        qDebug() << "未查询到编号为" << id << "的图书：" << query.lastError().text();
        return emptyBook;
    }
}
