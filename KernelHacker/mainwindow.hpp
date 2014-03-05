#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT
        
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        
    private slots:
        void on_actionExit_triggered();

    private:
        void RefreshStatic();
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
