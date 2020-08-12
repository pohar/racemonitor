#-------------------------------------------------
#
# Project created by QtCreator 2020-08-06T14:20:52
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#requires(qtConfig(udpsocket))

TARGET = RaceClient
TEMPLATE = app


SOURCES += main.cpp \
    RaceClient.cpp

HEADERS  += \
    ../common/common.h \
    ../r3e-api/sample-c/src/r3e.h \
    RaceClient.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    RaceClient.qrc
