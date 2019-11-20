#-------------------------------------------------
#
# Project created by QtCreator 2019-11-19T09:50:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arm_window
TEMPLATE = app


SOURCES += \
    main.cpp \
    updatecurrrentbuslocation.cpp \
    updatenoticeandweather.cpp \
    widget.cpp

HEADERS  += \
    updatecurrrentbuslocation.h \
    updatenoticeandweather.h \
    widget.h

FORMS    += \
    widget.ui

RESOURCES += \
    img.qrc
CONFIG += C++11
