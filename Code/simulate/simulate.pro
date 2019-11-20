#-------------------------------------------------
#
# Project created by QtCreator 2019-10-29T14:01:03
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulate
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    logindatabase_w.cpp

HEADERS  += widget.h \
    logindatabase_w.h

FORMS    += widget.ui \
    logindatabase_w.ui
CONFIG += C++11
