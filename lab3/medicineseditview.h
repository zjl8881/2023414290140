#ifndef MEDICINESEDITVIEW_H
#define MEDICINESEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class MedicinesEditView;
}

// 前向声明，避免循环包含
class IDatabase;

class MedicinesEditView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicinesEditView(QWidget *parent = nullptr, int index = -1);
    ~MedicinesEditView();

private slots:
    void on_pushButton_3_clicked();  // 保存
    void on_pushButton_4_clicked();  // 取消

private:
    Ui::MedicinesEditView *ui;
    int m_editIndex;
    QDataWidgetMapper *dataMapper;
    IDatabase* m_db;  // 改为指针

    bool validateInput();

signals:
    void goPreviousView();
};

#endif // MEDICINESEDITVIEW_H
