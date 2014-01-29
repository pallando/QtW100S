#-------------------------------------------------
#
# Project created by QtCreator 2014-01-28T10:26:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtW100S
TEMPLATE = app

LIBS += -lxinput -lm

SOURCES += main.cpp\
        mainwindow.cpp \
        workerthread.cpp

HEADERS  += mainwindow.h \
            workerthread.h

FORMS    += mainwindow.ui
