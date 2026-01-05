#include "PatientView.h"
#include "IDatabase.h"
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFont>

PatientView::PatientView(QWidget *parent) : QWidget(parent) {
    // 1. 基础设置
    setWindowTitle("患者管理");
    setMinimumSize(1000, 600);

    // 2. 创建顶部控件（搜索+按钮）
    QLabel* titleLabel = new QLabel("患者信息管理", this);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));

    txtSearch = new QLineEdit(this);
    txtSearch->setPlaceholderText("请输入患者姓名搜索");
    txtSearch->setFixedHeight(35);
    txtSearch->setMaximumWidth(300);

    // 功能按钮
    btSearch = new QPushButton("查找", this);
    btAdd = new QPushButton("添加", this);
    btEdit = new QPushButton("修改", this);
    btDelete = new QPushButton("删除", this);
    btBack = new QPushButton("返回", this);
    QList<QPushButton*> btnList = {btSearch, btAdd, btEdit, btDelete, btBack};

    // 按钮样式
    for (auto btn : btnList) {
        btn->setFixedSize(80, 35);
        btn->setStyleSheet("QPushButton{background-color:#2E86AB; color:white; border-radius:5px;}"
                           "QPushButton:hover{background-color:#3F97D6;}");
    }

    // 3. 创建患者列表表格
    tableView = new QTableView(this);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setAlternatingRowColors(true);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 绑定数据库模型
    IDatabase& db = IDatabase::getInstance();
    tableView->setModel(db.patientTabModel);
    tableView->setSelectionModel(db.thePatientSelection);

    // 4. 布局设置
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 顶部布局（标题+搜索+按钮）
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(titleLabel);
    topLayout->addSpacing(40);
    topLayout->addWidget(txtSearch);
    topLayout->addWidget(btSearch);
    topLayout->addSpacing(20);
    topLayout->addWidget(btAdd);
    topLayout->addWidget(btEdit);
    topLayout->addWidget(btDelete);
    topLayout->addSpacing(30);
    topLayout->addStretch();
    topLayout->addWidget(btBack);

    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(tableView);

    // 5. 绑定信号槽
    connect(btSearch, &QPushButton::clicked, this, &PatientView::on_btSearch_clicked);
    connect(btAdd, &QPushButton::clicked, this, &PatientView::on_btAdd_clicked);
    connect(btEdit, &QPushButton::clicked, this, &PatientView::on_btEdit_clicked);
    connect(btDelete, &QPushButton::clicked, this, &PatientView::on_btDelete_clicked);
    connect(btBack, &QPushButton::clicked, this, &PatientView::on_btBack_clicked);
}

// 以下槽函数逻辑与之前一致，直接复用
void PatientView::on_btSearch_clicked() {
    QString keyword = txtSearch->text().trimmed();
    QString filter = QString("NAME like '%%1%'").arg(keyword);
    IDatabase::getInstance().searchPatient(filter);
}

void PatientView::on_btAdd_clicked() {
    int row = IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(row);
}

void PatientView::on_btEdit_clicked() {
    QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex();
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请选择要编辑的患者！");
        return;
    }
    emit goPatientEditView(curIndex.row());
}

void PatientView::on_btDelete_clicked() {
    QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex();
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请选择要删除的患者！");
        return;
    }
    if (QMessageBox::question(this, "确认", "是否删除该患者信息？") == QMessageBox::Yes) {
        IDatabase::getInstance().deleteCurrentPatient()
        ? QMessageBox::information(this, "成功", "删除成功！")
        : QMessageBox::warning(this, "失败", "删除失败！");
    }
}

void PatientView::on_btBack_clicked() {
    emit goPreviousView();
}
