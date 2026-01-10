#include "dialogadddevice.h"
#include "ui_dialogadddevice.h"

DialogAddDevice::DialogAddDevice(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAddDevice)
{
    ui->setupUi(this);
    this->setWindowTitle("新增实验室设备");
}

// 新增：补充缺失的析构函数实现，解决链接报错
DialogAddDevice::~DialogAddDevice()
{12312312
    delete ui;
}

QVariantMap DialogAddDevice::getDeviceData() const
{
    QVariantMap data;
    int total = ui->editCount->text().toInt();
    int normal = ui->editNormalQty->text().toInt();
    int fault = ui->editFaultQty->text().toInt();

    data["name"] = ui->editName->text().trimmed();
    data["model"] = ui->editModel->text().trimmed();
    data["total_qty"] = total;
    // 关键点：将状态拼接成你要求的字符串格式
    data["status"] = QString("正常:%1, 故障中:%2").arg(normal).arg(fault);

    // 注意：current_qty (可用库存) 通常对应“正常”的数量
    data["current_qty"] = normal;

    return data;
}

// 实现校验函数
bool DialogAddDevice::validateData(QString &errorMsg) const {
    int total = ui->editCount->text().toInt();
    int normal = ui->editNormalQty->text().toInt();
    int fault = ui->editFaultQty->text().toInt();

    if (ui->editName->text().trimmed().isEmpty()) {
        errorMsg = "设备名称不能为空！";
        return false;
    }
    if (normal + fault != total) {
        errorMsg = QString("数量校验失败：正常(%1) + 故障(%2) 必须等于 总数(%3)！")
                       .arg(normal).arg(fault).arg(total);
        return false;
    }
    return true;
}
