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
    about.cpp

HEADERS  += mainwindow.hpp \
    kernelparameter.hpp \
    about.hpp

FORMS    += mainwindow.ui \
    about.ui
