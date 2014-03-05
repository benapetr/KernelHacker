//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->tableWidget->setColumnCount(3);
    QStringList header;
    header << tr("Parameter") << tr("Value") << tr("Modifiable");
    this->ui->tableWidget->setHorizontalHeaderLabels(header);
    this->ui->tableWidget->verticalHeader()->setVisible(false);
    this->ui->tableWidget->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->setShowGrid(false);
    this->ui->tableWidget_2->setColumnCount(4);
    header.clear();
    header << "PID" << tr("Name") << "VM (kb)" << "RSS (kb)";
    this->ui->tableWidget_2->setHorizontalHeaderLabels(header);
    this->stat = new QLabel(this);
    this->ui->tableWidget_2->verticalHeader()->setVisible(false);
    this->ui->tableWidget_2->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableWidget_2->setShowGrid(false);
    Loaded = false;
    connect(this->ui->tableWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(Resize()));
    this->RefreshStatic();
    Loaded = true;
    proc = new QTimer(this);
    this->ui->statusBar->addWidget(this->stat);
    connect(proc, SIGNAL(timeout()), this, SLOT(ProcessReload()));
    proc->start(2000);
    this->ProcessReload();
    this->RenderStatus();
}

QString MainWindow::String2Bool(bool b)
{
    if (b)
    {
        return "true";
    }
    return "false";
}

MainWindow::~MainWindow()
{
    delete proc;
    delete stat;
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::Resize()
{
    if (Loaded)
    {
        this->ui->tableWidget->resizeRowsToContents();
    }
}

void MainWindow::RenderStatus()
{
    this->stat->setText(tr("Processes: ") + QString::number(this->ui->tableWidget_2->rowCount()));
}

void MainWindow::ProcessReload()
{
    ProcessInfo::Reload();
    this->ui->tableWidget_2->clearContents();
    int x = 0;
    while (x < ProcessInfo::ProcessList.count())
    {
        ProcessInfo info = ProcessInfo::ProcessList.at(x);
        if (x + 1 > this->ui->tableWidget_2->rowCount())
        {
            this->ui->tableWidget_2->insertRow(x);
        }
        this->ui->tableWidget_2->setItem(x, 0, new QTableWidgetItem(QString::number(info.PID)));
        this->ui->tableWidget_2->setItem(x, 1, new QTableWidgetItem(info.Name));
        this->ui->tableWidget_2->setItem(x, 2, new QTableWidgetItem(QString::number(info.VmSize / 1024)));
        this->ui->tableWidget_2->setItem(x, 3, new QTableWidgetItem(QString::number(info.VmRss / 1024)));
        this->ui->tableWidget_2->resizeRowToContents(x);
        x++;
    }
    while (x < this->ui->tableWidget_2->rowCount())
    {
        this->ui->tableWidget_2->removeRow(x);
    }
    this->RenderStatus();
}

void MainWindow::RefreshStatic()
{
    Terminal::Write("Fetching kernel info");
    QFile c("/proc/cpuinfo");
    if (c.open(QIODevice::ReadOnly))
    {
        this->ui->textEdit->setText(QString(c.readAll()));
        c.close();
    }
    utsname b;
    KernelParameter::Init();
    int rs = uname(&b);
    if (rs == 0)
    {
        this->ui->label_2->setText(QString(b.release));
        this->ui->label_4->setText(QString(b.domainname));
        this->ui->label_6->setText(QString(b.machine));
        this->ui->label_8->setText(QString(b.nodename));
        this->ui->label_10->setText(QString(b.sysname));
        this->ui->label_12->setText(QString(b.version));
    } else
    {
        QMessageBox mb;
        mb.setText("Error @uname:" + QString::number(errno) + " " + QString(strerror(errno)));
        mb.exec();
    }
    int id = 0;
    while (id < KernelParameter::Parameters.count())
    {
        KernelParameter *kp = KernelParameter::Parameters.at(id);
        int size = this->ui->tableWidget->rowCount();
        this->ui->tableWidget->insertRow(size);
        this->ui->tableWidget->setItem(size, 0, new QTableWidgetItem(kp->Name));
        this->ui->tableWidget->setItem(size, 1, new QTableWidgetItem(kp->Value));
        this->ui->tableWidget->setItem(size, 2, new QTableWidgetItem(String2Bool(kp->IsModifiable_Online)));
        this->ui->tableWidget->resizeRowToContents(size);
        id++;
    }
}

void MainWindow::on_actionDisabled_triggered()
{
    this->ui->actionDisabled->setChecked(true);
    this->ui->action10_seconds->setChecked(false);
    this->ui->action20_seconds->setChecked(false);
    this->ui->action2_seconds->setChecked(false);
    this->proc->stop();
}

void MainWindow::on_action10_seconds_triggered()
{
    this->ui->actionDisabled->setChecked(false);
    this->ui->action10_seconds->setChecked(true);
    this->ui->action20_seconds->setChecked(false);
    this->ui->action2_seconds->setChecked(false);
    this->proc->stop();
    this->proc->start(10000);
}

void MainWindow::on_action2_seconds_triggered()
{
    this->ui->actionDisabled->setChecked(false);
    this->ui->action10_seconds->setChecked(false);
    this->ui->action20_seconds->setChecked(false);
    this->ui->action2_seconds->setChecked(true);
    this->proc->stop();
    this->proc->start(2000);
}

void MainWindow::on_action20_seconds_triggered()
{
    this->ui->actionDisabled->setChecked(false);
    this->ui->action10_seconds->setChecked(false);
    this->ui->action20_seconds->setChecked(true);
    this->ui->action2_seconds->setChecked(false);
    this->proc->stop();
    this->proc->start(20000);
}

void MainWindow::on_actionDisplay_about_triggered()
{

}
