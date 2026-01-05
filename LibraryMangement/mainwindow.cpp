#include "mainwindow.h"
// 必须显式包含自动生成的UI头文件（关键修复点）
#include "ui_mainwindow.h"
// 包含BookManager头文件（因为要使用其具体实现）
#include "bookmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) { // 初始化UI对象
    ui->setupUi(this); // 加载UI界面
    this->setWindowTitle("图书管理系统");

    // 初始化数据库管理器
    bookMgr = new BookManager(this);

    // 测试：添加一本图书到数据库
    Book testBook("B001", "Qt从入门到精通", "张三", "机械工业出版社", 89.9, 100);
    bookMgr->addBook(testBook);

    // 测试：查询刚才添加的图书
    Book queryBook = bookMgr->queryBookById("B001");
    qDebug() << "查询结果 - 图书名称：" << queryBook.getName() << " 库存：" << queryBook.getStock();
}

MainWindow::~MainWindow() {
    delete bookMgr; // 释放数据库管理器
    delete ui; // 释放UI对象（现在能正确解析）
}
