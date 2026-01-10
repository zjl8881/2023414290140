#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "idatabase.h"

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT
企鹅其额2
public:
    explicit PatientEditView(QWidget *parent = nullptr, int index = 0);
    ~PatientEditView();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_btReport_clicked();
    void handleReportFinished(bool success, QString message);

private:
    Ui::PatientEditView *ui;
    QDataWidgetMapper *dataMapper;
    int m_editIndex;

signals:
    void goPreviousView();
};

#endif // PATIENTEDITVIEW_H
