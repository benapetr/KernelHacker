#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T13:51:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KernelHacker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    kernelparameter.cpp \
    about.cpp \
    terminal.cpp \
    processinfo.cpp \
    linuxtools.cpp \
    systeminfo.cpp \
    config.cpp

HEADERS  += mainwindow.hpp \
    kernelparameter.hpp \
    about.hpp \
    terminal.hpp \
    processinfo.hpp \
    linuxtools.hpp \
    systeminfo.hpp \
    config.hpp

FORMS    += mainwindow.ui \
    about.ui
