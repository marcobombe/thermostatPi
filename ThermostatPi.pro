#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T21:36:11
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThermostatPi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thermostatmodel.cpp \
    login.cpp \
    dashboard.cpp \
    SlidingStackedWidget.cpp \
    dbmanager.cpp

HEADERS  += mainwindow.h \
    thermostatmodel.h \
    login.h \
    dashboard.h \
    SlidingStackedWidget.h \
    dbmanager.h

FORMS    += mainwindow.ui \
    dashboard.ui \
    login.ui
