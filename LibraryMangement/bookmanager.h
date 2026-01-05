// bookmanager.h
#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H
#include <QList>
#include "book.h"

class BookManager
{
public:
    BookManager();

    // 添加图书
    bool addBook(const Book& book);
    // 删除图书（按编号）
    bool removeBook(const QString& bookId);
    // 查询图书（按编号）
    Book findBook(const QString& bookId) const;
    // 获取所有图书
    QList<Book> allBooks() const;

private:
    QList<Book> m_books;  // 存储图书列表
};

#endif // BOOKMANAGER_H
