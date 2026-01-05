// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "bookmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  // 若勾选了Add Q_OBJECT，则需添加

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 自定义槽函数（比如“添加图书”按钮点击）
    void onAddBookClicked();

private:
    Ui::MainWindow *ui;
    BookManager m_bookManager;  // 图书管理实例
};

#endif // MAINWINDOW_H
