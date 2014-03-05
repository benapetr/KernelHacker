//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include "about.hpp"
#include "kernelparameter.hpp"
#include "terminal.hpp"
#include "processinfo.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT
        
    public:
        explicit MainWindow(QWidget *parent = 0);
        static QString String2Bool(bool b);
        ~MainWindow();
        bool Loaded;
        
    private slots:
        void on_actionExit_triggered();
        void Resize();
        void RenderStatus();
        void ProcessReload();

    private:
        void RefreshStatic();
        QLabel *stat;
        QTimer *proc;
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
