// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addbookdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 绑定“添加图书”按钮的点击信号到槽函数
    connect(ui->btnAddBook, &QPushButton::clicked, this, &MainWindow::onAddBookClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddBookClicked()
{
    AddBookDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Book newBook = dialog.getBookInfo();
        if (m_bookManager.addBook(newBook)) {
            QMessageBox::information(this, "成功", "图书添加成功！");
            // 刷新界面（比如更新列表）
        } else {
            QMessageBox::warning(this, "失败", "图书编号已存在！");
        }
    }
}
