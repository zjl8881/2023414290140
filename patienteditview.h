#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QWidget>

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditView(int rowNo, QWidget *parent = nullptr);
    ~PatientEditView();

private slots:
    void on_pushButton_clicked();   // 保存按钮
    void on_pushButton_2_clicked(); // 取消按钮

private:
    Ui::PatientEditView *ui;
    int m_rowNo;
};

#endif // PATIENTEDITVIEW_H
