#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// 提前声明UI类（避免循环引用）
namespace Ui {
class MainWindow;
}

class BookManager; // 提前声明BookManager类

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui; // UI对象指针
    BookManager *bookMgr; // 数据库管理器对象
};

#endif // MAINWINDOW_H
