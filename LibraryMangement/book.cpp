// book.cpp
#include "book.h"

Book::Book(const QString& id, const QString& name, const QString& author, int count)
    : m_id(id), m_name(name), m_author(author), m_count(count)
{}

QString Book::id() const { return m_id; }
void Book::setId(const QString& id) { m_id = id; }

QString Book::name() const { return m_name; }
void Book::setName(const QString& name) { m_name = name; }

QString Book::author() const { return m_author; }
void Book::setAuthor(const QString& author) { m_author = author; }

int Book::count() const { return m_count; }
void Book::setCount(int count) { m_count = count; }
