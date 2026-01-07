#include "statisticsview.h"
#include "ui_statisticsview.h"
#include "statisticscontroller.h"
#include "loghelper.h"
#include <QMessageBox>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrintDialog>
#include <QTextStream>

StatisticsView::StatisticsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsView)
{
    ui->setupUi(this);
    setupUI();
}

StatisticsView::~StatisticsView()
{
    delete ui;
}

void StatisticsView::setupUI()
{
    this->setWindowTitle("统计报表");

    // 设置日期范围
    ui->dateStart->setDate(QDate::currentDate().addMonths(-1));
    ui->dateEnd->setDate(QDate::currentDate());

    // 报表类型
    ui->comboReportType->addItem("综合统计报告", "comprehensive");
    ui->comboReportType->addItem("科室统计报告", "department");
    ui->comboReportType->addItem("医生工作统计", "doctor");
    ui->comboReportType->addItem("患者统计报告", "patient");

    // 设置默认标题
    ui->editTitle->setText(QString("医院统计报告_%1").arg(QDate::currentDate().toString("yyyy年MM月")));
}

void StatisticsView::on_btGenerate_clicked()
{
    QString reportType = ui->comboReportType->currentData().toString();
    QDate startDate = ui->dateStart->date();
    QDate endDate = ui->dateEnd->date();
    QString title = ui->editTitle->text().trimmed();

    if (startDate > endDate) {
        QMessageBox::warning(this, "警告", "开始日期不能晚于结束日期！");
        return;
    }

    if (title.isEmpty()) {
        QMessageBox::warning(this, "警告", "报告标题不能为空！");
        return;
    }

    StatisticsController *controller = new StatisticsController(this);
    connect(controller, &StatisticsController::reportReady, this, &StatisticsView::onReportReady);

    controller->generateReport(this, reportType, startDate, endDate, title);
}

void StatisticsView::onReportReady(const StatisticsReport &report)
{
    m_currentReport = report;
    displayReport(report);
}

void StatisticsView::displayReport(const StatisticsReport &report)
{
    // 生成HTML格式报告
    QString html;
    html += "<html><head><style>";
    html += "body { font-family: Arial, sans-serif; margin: 20px; }";
    html += "h1 { color: #2c3e50; border-bottom: 2px solid #3498db; padding-bottom: 10px; }";
    html += "h2 { color: #34495e; margin-top: 20px; }";
    html += "table { border-collapse: collapse; width: 100%; margin: 10px 0; }";
    html += "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }";
    html += "th { background-color: #f2f2f2; font-weight: bold; }";
    html += ".summary { background-color: #ecf0f1; padding: 15px; border-radius: 5px; }";
    html += "</style></head><body>";

    html += QString("<h1>%1</h1>").arg(report.reportTitle);
    html += QString("<div class='summary'>");
    html += QString("<p><strong>生成时间:</strong> %1</p>").arg(report.generationTime);
    html += QString("<p><strong>报告日期:</strong> %1</p>").arg(report.reportDate.toString("yyyy年MM月dd日"));
    html += QString("<p><strong>生成人员:</strong> %1</p>").arg(report.generatedBy);
    html += "</div>";

    // 基础统计
    html += "<h2>基础统计</h2>";
    html += "<table>";
    html += "<tr><th>统计项目</th><th>数量</th></tr>";
    html += QString("<tr><td>科室总数</td><td>%1</td></tr>").arg(report.totalDepartments);
    html += QString("<tr><td>医生总数</td><td>%1</td></tr>").arg(report.totalDoctors);
    html += QString("<tr><td>患者总数</td><td>%1</td></tr>").arg(report.totalPatients);
    html += QString("<tr><td>药品总数</td><td>%1</td></tr>").arg(report.totalMedicines);
    html += "</table>";

    // 科室统计
    if (!report.departmentStats.isEmpty()) {
        html += "<h2>科室统计</h2>";
        html += "<table>";
        html += "<tr><th>科室名称</th><th>医生数量</th><th>活跃医生</th></tr>";

        for (const auto &dept : report.departmentStats) {
            html += QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>")
            .arg(dept.departmentName)
                .arg(dept.doctorCount)
                .arg(dept.activeDoctors);
        }
        html += "</table>";
    }

    html += "</body></html>";

    ui->textReport->setHtml(html);
    LogHelper::getInstance().writeLog("报表显示完成", "INFO");
}

void StatisticsView::on_btExport_clicked()
{
    if (m_currentReport.reportDate.isNull()) {
        QMessageBox::information(this, "提示", "请先生成报表再导出！");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(
        this,
        "导出报表",
        QString("医院统计报告_%1.pdf").arg(QDate::currentDate().toString("yyyyMMdd")),
        "PDF文件 (*.pdf);;文本文件 (*.txt)"
        );

    if (filename.isEmpty()) {
        return;
    }

    if (filename.endsWith(".pdf", Qt::CaseInsensitive)) {
        exportToPdf(filename);
    } else if (filename.endsWith(".txt", Qt::CaseInsensitive)) {
        exportToText(filename);
    } else {
        QMessageBox::warning(this, "警告", "不支持的文件格式！");
    }
}

void StatisticsView::exportToPdf(const QString &filename)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QTextDocument document;
    document.setHtml(ui->textReport->toHtml());
    document.print(&printer);

    LogHelper::getInstance().writeLog(QString("报表导出为PDF: %1").arg(filename), "INFO");
    QMessageBox::information(this, "成功", QString("报表已导出到:\n%1").arg(filename));
}

void StatisticsView::exportToText(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");  // 确保中文编码正确
        stream << ui->textReport->toPlainText();
        file.close();

        LogHelper::getInstance().writeLog(QString("报表导出为文本: %1").arg(filename), "INFO");
        QMessageBox::information(this, "成功", QString("报表已导出到:\n%1").arg(filename));
    } else {
        QMessageBox::critical(this, "错误", QString("无法创建文件:\n%1").arg(filename));
    }
}

void StatisticsView::on_btPrint_clicked()
{
    if (m_currentReport.reportDate.isNull()) {
        QMessageBox::information(this, "提示", "请先生成报表再打印！");
        return;
    }

    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QTextDocument document;
        document.setHtml(ui->textReport->toHtml());
        document.print(&printer);
        LogHelper::getInstance().writeLog("报表打印完成", "INFO");
    }
}
