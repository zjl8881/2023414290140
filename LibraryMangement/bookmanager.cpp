// bookmanager.cpp
#include "bookmanager.h"

BookManager::BookManager()
{}

bool BookManager::addBook(const Book& book)
{
    // 避免重复编号
    for (const Book& b : m_books) {
        if (b.id() == book.id()) {
            return false;
        }
    }
    m_books.append(book);
    return true;
}

bool BookManager::removeBook(const QString& bookId)
{
    for (int i = 0; i < m_books.size(); ++i) {
        if (m_books[i].id() == bookId) {
            m_books.removeAt(i);
            return true;
        }
    }
    return false;
}

Book BookManager::findBook(const QString& bookId) const
{
    for (const Book& b : m_books) {
        if (b.id() == bookId) {
            return b;
        }
    }
    return Book();  // 返回空图书
}

QList<Book> BookManager::allBooks() const
{
    return m_books;
}
