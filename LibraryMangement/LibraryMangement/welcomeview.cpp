#include "WelcomeView.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

WelcomeView::WelcomeView(QWidget *parent) : QWidget(parent) {
    // 1. 基础设置
    setWindowTitle("功能选择");
    setFixedSize(500, 400);

    // 2. 创建控件
    QLabel* titleLabel = new QLabel("欢迎使用医院诊疗系统", this);
    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    // 功能按钮
    QPushButton* btnPatient = new QPushButton("患者管理", this);
    QPushButton* btnDoctor = new QPushButton("医生管理", this);
    QPushButton* btnDept = new QPushButton("科室管理", this);
    QList<QPushButton*> btnList = {btnPatient, btnDoctor, btnDept};

    // 设置按钮样式
    for (auto btn : btnList) {
        btn->setFixedSize(180, 60);
        btn->setFont(QFont("Arial", 14));
        btn->setStyleSheet("QPushButton{background-color:#A23B72; color:white; border-radius:8px;}"
                           "QPushButton:hover{background-color:#C73E1D;}");
    }

    // 3. 布局设置
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(60);

    // 按钮水平布局
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addSpacing(30);
    btnLayout->addWidget(btnPatient);
    btnLayout->addSpacing(40);
    btnLayout->addWidget(btnDoctor);
    btnLayout->addSpacing(40);
    btnLayout->addWidget(btnDept);
    btnLayout->addSpacing(30);
    mainLayout->addLayout(btnLayout);

    // 4. 绑定信号槽
    connect(btnPatient, &QPushButton::clicked, this, &WelcomeView::goPatientView);
    connect(btnDoctor, &QPushButton::clicked, this, &WelcomeView::goDoctorView);
    connect(btnDept, &QPushButton::clicked, this, &WelcomeView::goDepartmentView);
}
