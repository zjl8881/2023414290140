#include "PatientEditView.h"
#include "IDatabase.h"
#include <QDataWidgetMapper>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QMessageBox>
#include <QFont>

PatientEditView::PatientEditView(int row, QWidget *parent) :
    QWidget(parent), currentRow(row) {
    // 1. 基础设置
    setWindowTitle("编辑患者信息");
    setFixedSize(500, 400);

    // 2. 创建控件
    QLabel* titleLabel = new QLabel("患者信息编辑", this);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    titleLabel->setAlignment(Qt::AlignCenter);

    // 表单控件
    dbEditID = new QLineEdit(this);
    dbEditName = new QLineEdit(this);
    dbEditIDCard = new QLineEdit(this);
    dbComboSex = new QComboBox(this);
    dbDataEditDOB = new QDateEdit(this);
    dbSpinHeight = new QDoubleSpinBox(this);
    dbSpinWeight = new QDoubleSpinBox(this);
    dbEditMobile = new QLineEdit(this);
    dbCreatedTimeStamp = new QLineEdit(this);

    // 控件属性设置
    dbEditID->setReadOnly(true); // ID只读
    dbCreatedTimeStamp->setReadOnly(true); // 创建时间只读
    dbComboSex->addItems({"男", "女"}); // 性别选项
    dbDataEditDOB->setCalendarPopup(true); // 日期选择弹窗
    dbSpinHeight->setRange(50.0, 250.0); // 身高范围
    dbSpinWeight->setRange(10.0, 200.0); // 体重范围
    dbEditName->setPlaceholderText("请输入患者姓名");
    dbEditIDCard->setPlaceholderText("请输入身份证号");
    dbEditMobile->setPlaceholderText("请输入手机号");

    // 按钮
    QPushButton* btnSave = new QPushButton("保存", this);
    QPushButton* btnCancel = new QPushButton("取消", this);
    btnSave->setFixedSize(100, 40);
    btnCancel->setFixedSize(100, 40);
    btnSave->setStyleSheet("background-color:#2E86AB; color:white; border-radius:5px;");
    btnCancel->setStyleSheet("background-color:#A23B72; color:white; border-radius:5px;");

    // 3. 布局设置
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 20, 30, 20);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(20);

    // 表单布局
    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("患者ID：", dbEditID);
    formLayout->addRow("姓  名：", dbEditName);
    formLayout->addRow("身份证号：", dbEditIDCard);
    formLayout->addRow("性  别：", dbComboSex);
    formLayout->addRow("出生日期：", dbDataEditDOB);
    formLayout->addRow("身  高(cm)：", dbSpinHeight);
    formLayout->addRow("体  重(kg)：", dbSpinWeight);
    formLayout->addRow("手机号：", dbEditMobile);
    formLayout->addRow("创建时间：", dbCreatedTimeStamp);
    formLayout->setVerticalSpacing(15);
    mainLayout->addLayout(formLayout);

    // 按钮布局
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(btnSave);
    btnLayout->addSpacing(30);
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();
    mainLayout->addSpacing(25);
    mainLayout->addLayout(btnLayout);

    // 4. 数据映射（绑定模型与控件）
    IDatabase& db = IDatabase::getInstance();
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(db.patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    dataMapper->setCurrentIndex(currentRow);

    // 绑定字段
    dataMapper->addMapping(dbEditID, db.patientTabModel->fieldIndex("ID"));
    dataMapper->addMapping(dbEditName, db.patientTabModel->fieldIndex("NAME"));
    dataMapper->addMapping(dbEditIDCard, db.patientTabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(dbComboSex, db.patientTabModel->fieldIndex("SEX"));
    dataMapper->addMapping(dbDataEditDOB, db.patientTabModel->fieldIndex("DOB"));
    dataMapper->addMapping(dbSpinHeight, db.patientTabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(dbSpinWeight, db.patientTabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(dbEditMobile, db.patientTabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(dbCreatedTimeStamp, db.patientTabModel->fieldIndex("CREATEDTIMESTAMP"));

    // 5. 绑定信号槽
    connect(btnSave, &QPushButton::clicked, this, &PatientEditView::on_pushButton_clicked);
    connect(btnCancel, &QPushButton::clicked, this, &PatientEditView::on_pushButton_2_clicked);
}

// 保存与取消槽函数复用之前逻辑
void PatientEditView::on_pushButton_clicked() {
    if (dbEditName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "患者姓名不能为空！");
        return;
    }
    dataMapper->submit();
    IDatabase::getInstance().submitPatientEdit()
        ? (QMessageBox::information(this, "成功", "保存成功！"), emit goPreviousView())
        : QMessageBox::warning(this, "失败", "保存失败！");
}

void PatientEditView::on_pushButton_2_clicked() {
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();
}
