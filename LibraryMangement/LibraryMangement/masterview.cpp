#include "MasterView.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>

MasterView::MasterView(QWidget *parent) : QMainWindow(parent) {
    // 1. 主窗口设置
    setWindowTitle("医院诊疗系统");
    setMinimumSize(1200, 700);

    // 2. 创建顶部标题栏和返回按钮
    QWidget* topWidget = new QWidget(this);
    topWidget->setFixedHeight(60);
    topWidget->setStyleSheet("background-color:#2E86AB;");

    labelTitle = new QLabel("医院诊疗系统", topWidget);
    labelTitle->setFont(QFont("Arial", 18, QFont::Bold));
    labelTitle->setStyleSheet("color:white;");

    QPushButton* btnBack = new QPushButton("返回", topWidget);
    btnBack->setFixedSize(80, 35);
    btnBack->setStyleSheet("background-color:white; color:#2E86AB; border-radius:5px;");

    // 顶部布局
    QHBoxLayout* topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(30, 0, 30, 0);
    topLayout->addWidget(labelTitle);
    topLayout->addStretch();
    topLayout->addWidget(btnBack);

    // 3. 堆叠窗口（管理所有子界面）
    stackedWidget = new QStackedWidget(this);

    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(stackedWidget);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 4. 状态栏显示开发者信息
    statusBar()->showMessage("开发者：张嘉亮 学号：2023414290140 | 数据库已连接");

    // 绑定返回按钮
    connect(btnBack, &QPushButton::clicked, this, &MasterView::goPreviousView);
}

// 其余界面切换逻辑（goLoginView、goWelcomeView等）与之前一致，直接复用
