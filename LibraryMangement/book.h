// book.h
#ifndef BOOK_H
#define BOOK_H
#include <QString>

class Book
{
public:
    Book(const QString& id = "", const QString& name = "",
         const QString& author = "", int count = 0);

    // 获取/设置属性
    QString id() const;
    void setId(const QString& id);
    QString name() const;
    void setName(const QString& name);
    QString author() const;
    void setAuthor(const QString& author);
    int count() const;
    void setCount(int count);

private:
    QString m_id;      // 图书编号
    QString m_name;    // 图书名称
    QString m_author;  // 作者
    int m_count;       // 库存数量
};

#endif // BOOK_H
