#include "welcomeview.h"
#include "ui_welcomeview.h"
#include <QDebug>

WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
{
    qDebug() << "create WelcomeView";
    ui->setupUi(this);
}

WelcomeView::~WelcomeView()
{
    qDebug() << "destroy WelcomeView";
    delete ui;
}

void WelcomeView::on_pushButton_clicked()  // 科室管理
{
    emit goDepartmentView();
}

void WelcomeView::on_pushButton_2_clicked()  // 医生管理
{
    emit goDoctorView();
}

void WelcomeView::on_pushButton_3_clicked()  // 患者管理
{
    emit goPatientView();
}

void WelcomeView::on_pushButton_4_clicked()  // 药品管理
{
    emit goMedicinesView();
}

void WelcomeView::on_pushButton_5_clicked()  // 统计报表
{
    emit goStatisticsView();
}
