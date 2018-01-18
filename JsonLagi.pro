#-------------------------------------------------
#
# Project created by QtCreator 2018-01-11T13:54:12
#
#-------------------------------------------------

QT       += core sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JsonLagi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    redis.cpp \
    time.cpp

HEADERS  += mainwindow.h \
    client.h \
    redis.h \
    time.h \
    time2.h

FORMS    += mainwindow.ui
