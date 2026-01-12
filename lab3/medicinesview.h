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
    QString m_originalFilter;

private slots:
    void on_btAdd_clicked();
    void on_btEdit_clicked();
    void on_btDelete_clicked();
    void on_btSearch_clicked();
    void handleReportFinished(bool success, QString message);

    void on_btReport_clicked();

signals:
    void goMedicinesEditView(int index);
};

#endif // MEDICINESVIEW_H
