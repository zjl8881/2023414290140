#include "book.h"

Book::Book(QString id, QString name, QString author, QString press, double price, int stock)
    : bookId(id), bookName(name), bookAuthor(author), bookPress(press), bookPrice(price), bookStock(stock) {}

QString Book::getId() const { return bookId; }
QString Book::getName() const { return bookName; }
QString Book::getAuthor() const { return bookAuthor; }
QString Book::getPress() const { return bookPress; }
double Book::getPrice() const { return bookPrice; }
int Book::getStock() const { return bookStock; }

void Book::setId(QString id) { bookId = id; }
void Book::setName(QString name) { bookName = name; }
void Book::setAuthor(QString author) { bookAuthor = author; }
void Book::setPress(QString press) { bookPress = press; }
void Book::setPrice(double price) { bookPrice = price; }
void Book::setStock(int stock) { bookStock = stock; }
