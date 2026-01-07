#ifndef MEDICINESEDITVIEW_H
#define MEDICINESEDITVIEW_H

#include <QWidget>

namespace Ui {
class MedicinesEditView;
}

class MedicinesEditView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicinesEditView(int rowNo, QWidget *parent = nullptr);
    ~MedicinesEditView();

private slots:
    void on_pushButton_3_clicked();  // 保存按钮
    void on_pushButton_4_clicked();  // 取消按钮

private:
    Ui::MedicinesEditView *ui;
    int m_rowNo;
};

#endif // MEDICINESEDITVIEW_H
