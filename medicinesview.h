#ifndef MEDICINESVIEW_H
#define MEDICINESVIEW_H

#include <QWidget>

namespace Ui {
class MedicinesView;
}

class MedicinesView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicinesView(QWidget *parent = nullptr);
    ~MedicinesView();

signals:
    void goMedicinesEditView(int rowNo);

private slots:
    void on_btAdd_clicked();
    void on_btEdit_clicked();
    void on_btDelete_clicked();
    void on_btRefresh_clicked();

private:
    Ui::MedicinesView *ui;
};

#endif // MEDICINESVIEW_H
