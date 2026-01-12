#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>
#include "idatabase.h"

namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);ASDSDSADA
    ~PatientView();

private slots:
    void on_btAdd_clicked();
    void on_btSearch_clicked();
    void on_btDelete_clicked();
    void on_btEdit_clicked();
    void handleReportFinished(bool success, QString message);

    void on_btReport_clicked();

signals:
    void goPatientEditView(int idx);

private:
    Ui::PatientView *ui;
    IDatabase &m_db;
    QString m_originalFilter;
};

#endif // PATIENTVIEW_H
