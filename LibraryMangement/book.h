#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book {
public:
    // 构造函数
    Book() = default;
    Book(QString id, QString name, QString author, QString press, double price, int stock);

    // 获取属性的接口
    QString getId() const;
    QString getName() const;
    QString getAuthor() const;
    QString getPress() const;
    double getPrice() const;
    int getStock() const;

    // 设置属性的接口
    void setId(QString id);
    void setName(QString name);
    void setAuthor(QString author);
    void setPress(QString press);
    void setPrice(double price);
    void setStock(int stock);

private:
    // 图书属性
    QString bookId;     // 图书编号
    QString bookName;   // 图书名称
    QString bookAuthor; // 作者
    QString bookPress;  // 出版社
    double bookPrice;   // 价格
    int bookStock;      // 库存
};

#endif // BOOK_H
