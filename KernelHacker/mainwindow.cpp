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
    this->ui->tableWidget->setColumnCount(4);
    QStringList header;
    header << "Parameter" << "Value" << "Modifiable online" << "Modifiable offline";
    this->ui->tableWidget->setHorizontalHeaderLabels(header);
    this->ui->tableWidget->verticalHeader()->setVisible(false);
    this->ui->tableWidget->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
#if QT_VERSION >= 0x050000
// Qt5 code
    //this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
// Qt4 code
    //this->ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    this->ui->tableWidget->setShowGrid(false);
    Loaded = false;
    connect(this->ui->tableWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(Resize()));
    this->RefreshStatic();
    Loaded = true;
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

void MainWindow::RefreshStatic()
{
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
        this->ui->tableWidget->setItem(size, 3, new QTableWidgetItem(String2Bool(kp->IsModifiable_Offline)));
        this->ui->tableWidget->resizeRowToContents(size);
        id++;
    }
}
