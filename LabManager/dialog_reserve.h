#ifndef DIALOG_RESERVE_H
#define DIALOG_RESERVE_H

#include <QDialog>

namespace Ui {
class DialogReserve;
}

class DialogReserve : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReserve(QWidget *parent = nullptr);
    ~DialogReserve();

    QString getDevice() const;
    QString getUser() const;
    int getCount() const;

private slots:
    void on_buttonBox_accepted(); // 处理确定
    void on_buttonBox_rejected(); // 处理取消

private:
    Ui::DialogReserve *ui;
    void initDeviceList();
};

#endif
