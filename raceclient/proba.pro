#-------------------------------------------------
#
# Project created by QtCreator 2020-08-06T14:20:52
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#requires(qtConfig(udpsocket))

TARGET = proba
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
