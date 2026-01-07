// statisticsview.h
#ifndef STATISTICSVIEW_H
#define STATISTICSVIEW_H

#include <QWidget>
#include "statisticstypes.h"

namespace Ui {
class StatisticsView;
}

class StatisticsView : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsView(QWidget *parent = nullptr);
    ~StatisticsView();

private slots:
    void on_btGenerate_clicked();
    void on_btExport_clicked();
    void on_btPrint_clicked();
    void onReportReady(const StatisticsReport &report);

private:
    Ui::StatisticsView *ui;
    StatisticsReport m_currentReport;

    void setupUI();
    void displayReport(const StatisticsReport &report);
    void exportToPdf(const QString &filename);
    void exportToText(const QString &filename);
};

#endif // STATISTICSVIEW_H
