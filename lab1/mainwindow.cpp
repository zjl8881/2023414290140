#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->display->setText("0");
    ui->display->setReadOnly(true);
    // 新增：初始化时更新标签，显示默认的“当前结果:0”和“当前操作符:无”
    updateStatusLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 新增：核心函数——更新labCurrentNum和labCurrentOp的显示内容
void MainWindow::updateStatusLabels()
{
    // 处理“当前结果”显示：整数无小数时显示为整数（如5而非5.0），小数正常显示
    if (currentNum == floor(currentNum)) {
        ui->labCurrentNum->setText(QString("当前结果:%1").arg((int)currentNum));
    } else {
        ui->labCurrentNum->setText(QString("当前结果:%1").arg(currentNum));
    }

    // 处理“当前操作符”显示：无操作符时显示“无”，有操作符时显示对应符号
    if (op.isEmpty()) {
        ui->labCurrentOp->setText("当前操作符:无");
    } else {
        ui->labCurrentOp->setText(QString("当前操作符:%1").arg(op));
    }
}

// -------------------------- 数字按键实现（0-9）--------------------------
void MainWindow::on_btnNum0_clicked()
{
    if (isNewOp) {
        ui->display->setText("0");
        isNewOp = false;
        hasDot = false;
    } else if (ui->display->text() != "0") {
        ui->display->setText(ui->display->text() + "0");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum1_clicked()
{
    if (isNewOp) {
        ui->display->setText("1");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "1");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum2_clicked()
{
    if (isNewOp) {
        ui->display->setText("2");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "2");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum3_clicked()
{
    if (isNewOp) {
        ui->display->setText("3");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "3");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum4_clicked()
{
    if (isNewOp) {
        ui->display->setText("4");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "4");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum5_clicked()
{
    if (isNewOp) {
        ui->display->setText("5");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "5");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum6_clicked()
{
    if (isNewOp) {
        ui->display->setText("6");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "6");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum7_clicked()
{
    if (isNewOp) {
        ui->display->setText("7");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "7");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum8_clicked()
{
    if (isNewOp) {
        ui->display->setText("8");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "8");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnNum9_clicked()
{
    if (isNewOp) {
        ui->display->setText("9");
        isNewOp = false;
        hasDot = false;
    } else {
        ui->display->setText(ui->display->text() + "9");
    }
    currentNum = ui->display->text().toDouble();
    // 新增：数字变化后更新标签
    updateStatusLabels();
}

// -------------------------- 运算符按键实现（+、-、×、/）--------------------------
void MainWindow::on_btnAdd_clicked()
{
    if (!op.isEmpty() && !isNewOp) {
        on_btnEq_clicked();
    }
    lastNum = currentNum;
    op = "+";
    isNewOp = true;
    hasDot = false;
    // 新增：操作符变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnSub_clicked()
{
    if (!op.isEmpty() && !isNewOp) {
        on_btnEq_clicked();
    }
    lastNum = currentNum;
    op = "-";
    isNewOp = true;
    hasDot = false;
    // 新增：操作符变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnMul_clicked()
{
    if (!op.isEmpty() && !isNewOp) {
        on_btnEq_clicked();
    }
    lastNum = currentNum;
    op = "×";
    isNewOp = true;
    hasDot = false;
    // 新增：操作符变化后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnDiv_clicked()
{
    if (!op.isEmpty() && !isNewOp) {
        on_btnEq_clicked();
    }
    lastNum = currentNum;
    op = "/";
    isNewOp = true;
    hasDot = false;
    // 新增：操作符变化后更新标签
    updateStatusLabels();
}

// -------------------------- 小数点按键实现 --------------------------
void MainWindow::on_btnDot_clicked()
{
    if (isNewOp) {
        ui->display->setText("0.");
        isNewOp = false;
        hasDot = true;
        currentNum = 0.0;
    } else if (!hasDot) {
        ui->display->setText(ui->display->text() + ".");
        hasDot = true;
    }
    // 新增：小数点操作后更新标签（即使数值未变，显示需同步）
    updateStatusLabels();
}

// -------------------------- 功能按键实现 --------------------------
void MainWindow::on_btnSquare_clicked()
{
    currentNum = pow(currentNum, 2);
    if (currentNum == floor(currentNum)) {
        ui->display->setText(QString::number((int)currentNum));
    } else {
        ui->display->setText(QString::number(currentNum));
    }
    isNewOp = true;
    // 新增：平方运算后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnSqrt_clicked()
{
    if (currentNum < 0) {
        ui->display->setText("Error");
        currentNum = 0;
    } else {
        currentNum = sqrt(currentNum);
        if (currentNum == floor(currentNum)) {
            ui->display->setText(QString::number((int)currentNum));
        } else {
            ui->display->setText(QString::number(currentNum));
        }
    }
    isNewOp = true;
    // 新增：根号运算后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnSign_clicked()
{
    currentNum = -currentNum;
    if (currentNum == floor(currentNum)) {
        ui->display->setText(QString::number((int)currentNum));
    } else {
        ui->display->setText(QString::number(currentNum));
    }
    // 新增：正负号切换后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnEq_clicked()
{
    double result = 0.0;
    if (op == "+") {
        result = lastNum + currentNum;
    } else if (op == "-") {
        result = lastNum - currentNum;
    } else if (op == "×") {
        result = lastNum * currentNum;
    } else if (op == "/") {
        if (currentNum == 0) {
            ui->display->setText("除数不能为零");
            currentNum = 0;
            op = "";
            // 新增：报错后更新标签（重置为0和无操作符）
            updateStatusLabels();
            return;
        }
        result = lastNum / currentNum;
    } else {
        return;
    }

    currentNum = result;
    lastNum = result;
    op = "";
    isNewOp = true;
    hasDot = false;

    // 显示计算结果
    if (result == floor(result)) {
        ui->display->setText(QString::number((int)result));
    } else {
        ui->display->setText(QString::number(result));
    }
    // 新增：等于运算后更新标签（操作符清空，结果同步）
    updateStatusLabels();
}

void MainWindow::on_btnClear_clicked()
{
    currentNum = 0;
    lastNum = 0;
    op = "";
    isNewOp = true;
    hasDot = false;
    expression.clear();
    ui->display->setText("0");
    // 新增：清除后更新标签（重置为初始状态）
    updateStatusLabels();
}

void MainWindow::on_btnReciprocal_clicked()
{
    if (currentNum == 0) {
        ui->display->setText("除数不能为零");
        return;
    }
    currentNum = 1 / currentNum;
    if (currentNum == floor(currentNum)) {
        ui->display->setText(QString::number((int)currentNum));
    } else {
        ui->display->setText(QString::number(currentNum));
    }
    isNewOp = true;
    // 新增：倒数运算后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnPercent_clicked()
{
    currentNum = currentNum / 100;
    if (currentNum == floor(currentNum)) {
        ui->display->setText(QString::number((int)currentNum));
    } else {
        ui->display->setText(QString::number(currentNum));
    }
    isNewOp = true;
    // 新增：百分比运算后更新标签
    updateStatusLabels();
}

void MainWindow::on_btnDel_clicked()
{
    QString text = ui->display->text();
    if (text.length() <= 1) {
        ui->display->setText("0");
        currentNum = 0.0;
        hasDot = false;
    } else {
        text.chop(1);
        ui->display->setText(text);
        currentNum = ui->display->text().toDouble();
        hasDot = ui->display->text().contains(".");
    }
    isNewOp = false;
    // 新增：删除操作后更新标签
    updateStatusLabels();
}

// -------------------------- 键盘事件处理 --------------------------
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    // 数字键
    case Qt::Key_0: on_btnNum0_clicked(); break;
    case Qt::Key_1: on_btnNum1_clicked(); break;
    case Qt::Key_2: on_btnNum2_clicked(); break;
    case Qt::Key_3: on_btnNum3_clicked(); break;
    case Qt::Key_4: on_btnNum4_clicked(); break;
    case Qt::Key_5: on_btnNum5_clicked(); break;
    case Qt::Key_6: on_btnNum6_clicked(); break;
    case Qt::Key_7: on_btnNum7_clicked(); break;
    case Qt::Key_8: on_btnNum8_clicked(); break;
    case Qt::Key_9: on_btnNum9_clicked(); break;

    // 运算符键
    case Qt::Key_Plus: on_btnAdd_clicked(); break;
    case Qt::Key_Minus: on_btnSub_clicked(); break;
    case Qt::Key_Asterisk: on_btnMul_clicked(); break;
    case Qt::Key_Slash: on_btnDiv_clicked(); break;

    // 功能键
    case Qt::Key_Period: on_btnDot_clicked(); break;
    case Qt::Key_Enter:
    case Qt::Key_Return: on_btnEq_clicked(); break;
    case Qt::Key_Delete: on_btnDel_clicked(); break;
    case Qt::Key_Escape: on_btnClear_clicked(); break;
    case Qt::Key_Percent: on_btnPercent_clicked(); break;
    case Qt::Key_S: if (event->modifiers() == Qt::NoModifier) on_btnSquare_clicked(); break;
    case Qt::Key_R: if (event->modifiers() == Qt::NoModifier) on_btnReciprocal_clicked(); break;
    case Qt::Key_Q: if (event->modifiers() == Qt::NoModifier) on_btnSqrt_clicked(); break;
    case Qt::Key_N: if (event->modifiers() == Qt::NoModifier) on_btnSign_clicked(); break;

    default: break;
    }
}
