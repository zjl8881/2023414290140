#ifndef MEDICINESVIEW_H
#define MEDICINESVIEW_H

#include <QWidget>
#include "idatabase.h"
#include "loghelper.h"

namespace Ui {
class MedicinesView;
}

class MedicinesView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicinesView(QWidget *parent = nullptr);
    ~MedicinesView();

private:
    Ui::MedicinesView *ui;
    IDatabase &m_db;
    QString m_originalFilter;  // 修改为成员变量

private slots:
    void on_btAdd_clicked();     // 必须与ui文件中的槽名称完全一致
    void on_btEdit_clicked();
    void on_btDelete_clicked();
    void on_btSearch_clicked();

signals:
    void goMedicinesEditView(int index);
};

#endif // MEDICINESVIEW_H
