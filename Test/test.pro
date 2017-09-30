#-------------------------------------------------
#
# Project created by QtCreator 2017-09-27T08:43:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

DESTDIR = ../lib     # 生成文件在这

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui \
    form.ui

INCLUDEPATH += $$PWD/../include
LIBS += -L../lib -llibHandWriteLibrary
