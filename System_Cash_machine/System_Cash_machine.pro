#-------------------------------------------------
#
# Project created by QtCreator 2016-02-19T17:17:10
#
#-------------------------------------------------

QT       += core gui network

LIBS += -lws2_32
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = System_Cash_machine
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    mainmenu.cpp \
    add_get_window.cpp \
    check_balance.cpp \
    transactionhistory.cpp \
    clientnetwork.cpp

HEADERS  += login.h \
    mainmenu.h \
    add_get_window.h \
    check_balance.h \
    transactionhistory.h \
    clientnetwork.h

FORMS    += login.ui \
    mainmenu.ui \
    add_get_window.ui \
    check_balance.ui \
    transactionhistory.ui

RESOURCES += \
    myresourse.qrc
