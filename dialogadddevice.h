#ifndef DIALOGADDDEVICE_H
#define DIALOGADDDEVICE_H

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class DialogAddDevice;
}

class DialogAddDevice : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddDevice(QWidget *parent = nullptr);
    ~DialogAddDevice();

    // 获取界面输入的所有数据
    QVariantMap getDeviceData() const;

    // 增加一个校验函数，方便在 accepted 之前检查
    bool validateData(QString &errorMsg) const;

private:
    Ui::DialogAddDevice *ui;
};

#endif // DIALOGADDDEVICE_H
