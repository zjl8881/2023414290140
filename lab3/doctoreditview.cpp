#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QMessageBox>

DoctorEditView::DoctorEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::DoctorEditView),
    m_editIndex(index),
    dataMapper(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("编辑医生信息");

    // 1. 获取数据库单例和医生模型
    IDatabase &db = IDatabase::getInstance();
    QSqlTableModel *doctorModel = db.doctorTabModel;
    if (!doctorModel) {
        QMessageBox::critical(this, "错误", "医生数据模型未初始化！");
        return;
    }

    // 2. 初始化映射器（完全对齐PatientEditView）
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(doctorModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 3. 绑定UI控件到数据库字段（字段名必须和数据库表一致）
    dataMapper->addMapping(ui->dbEditID_Doctor, doctorModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, doctorModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard, doctorModel->fieldIndex("EMPLOYEEON"));
    dataMapper->addMapping(ui->dbEditDepartmentNo, doctorModel->fieldIndex("DEPARTMENT_ID"));
    dataMapper->addMapping(ui->dbComboTitle, doctorModel->fieldIndex("TITLE"));
    dataMapper->addMapping(ui->dbComboStatus, doctorModel->fieldIndex("STATUS"));

    // 4. 核心修复：区分“添加”和“修改”场景
    if (index >= 0) {
        // 修改场景：加载选中行的原有数据
        dataMapper->setCurrentIndex(index);
    } else {
        // 添加场景：强制清空所有UI控件（避免残留数据）
        ui->dbEditID_Doctor->clear();
        ui->dbEditName->clear();
        ui->dbEditIDCard->clear();
        ui->dbEditDepartmentNo->clear();
        ui->dbComboTitle->setCurrentIndex(-1); // 下拉框置空
        ui->dbComboStatus->setCurrentIndex(-1); // 下拉框置空
        // 映射器绑定到新行
        dataMapper->setCurrentIndex(index);
    }

    // 5. 关键修改：ID字段改为可编辑（添加/修改都能改）
    ui->dbEditID_Doctor->setReadOnly(false); // 从true改为false，放开编辑限制
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}

// 新增：输入验证方法
bool DoctorEditView::validateInput()
{
    if (ui->dbEditID_Doctor->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "医生ID不能为空！");
        return false;
    }
    if (ui->dbEditName->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "医生姓名不能为空！");
        return false;
    }
    return true;
}

// 修改保存按钮逻辑，先验证再保存
void DoctorEditView::on_pushButton_clicked()
{
    // 新增：输入验证
    if (!validateInput()) {
        return;
    }

    dataMapper->submit();
    bool success = IDatabase::getInstance().submitDoctorEdit();
    if (success) {
        QMessageBox::information(this, "提示", "医生信息修改成功！");
    } else {
        QMessageBox::critical(this, "错误", "保存失败：" + IDatabase::getInstance().doctorTabModel->lastError().text());
        IDatabase::getInstance().revertDoctorEdit();
    }
    emit goPreviousView();
}

// 取消按钮（无修改）
void DoctorEditView::on_pushButton_2_clicked()
{
    IDatabase::getInstance().revertDoctorEdit();
    dataMapper->revert();
    emit goPreviousView();
}
