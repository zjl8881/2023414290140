#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <cmath>
#include <QKeyEvent> // 确保包含键盘事件头文件

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 数字按键槽函数（0-9）
    void on_btnNum0_clicked();
    void on_btnNum1_clicked();
    void on_btnNum2_clicked();
    void on_btnNum3_clicked();
    void on_btnNum4_clicked();
    void on_btnNum5_clicked();
    void on_btnNum6_clicked();
    void on_btnNum7_clicked();
    void on_btnNum8_clicked();
    void on_btnNum9_clicked();

    // 运算符按键槽函数（+、-、×、/、.）
    void on_btnAdd_clicked();
    void on_btnSub_clicked();
    void on_btnMul_clicked();
    void on_btnDiv_clicked();
    void on_btnDot_clicked();

    // 功能按键槽函数
    void on_btnSquare_clicked();
    void on_btnSqrt_clicked();
    void on_btnSign_clicked();
    void on_btnClear_clicked();
    void on_btnEq_clicked();
    void on_btnReciprocal_clicked();
    void on_btnPercent_clicked();
    void on_btnDel_clicked();

    // 键盘事件处理函数
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    double currentNum = 0.0;   // 当前输入数字
    double lastNum = 0.0;      // 上一次输入数字（用于运算）
    QString op = "";           // 当前操作符（+、-、×、/）
    bool isNewOp = true;       // 是否开启新运算（点击运算符后触发）
    bool hasDot = false;       // 当前数字是否包含小数点
    QString expression;        // 存储完整表达式（预留）

    // 新增：声明标签更新函数，用于同步显示当前结果和操作符
    void updateStatusLabels();
};

#endif // MAINWINDOW_H
