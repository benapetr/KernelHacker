#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->RefreshStatic();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::RefreshStatic()
{
    utsname b;
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
}
