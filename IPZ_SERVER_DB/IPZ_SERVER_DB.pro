#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T22:29:09
#
#-------------------------------------------------

QT       += core gui sql network
CONFIG += c++11

LIBS += -lws2_32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPZ_SERVER_DB
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    admindialog.cpp \
    database.cpp \
    databaseexception.cpp \
    servernetwork.cpp \
    serverthread.cpp

HEADERS  += mainwindow.h \
    admindialog.h \
    database.h \
    databaseexception.h \
    servernetwork.h \
    serverthread.h \
    samelib.h

FORMS    += mainwindow.ui \
    admindialog.ui
