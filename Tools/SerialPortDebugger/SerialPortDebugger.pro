#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T21:58:35
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPortDebugger
TEMPLATE = app


SOURCES += main.cpp\
        fos_spd.cpp \
    pcloop.cpp

HEADERS  += fos_spd.h \
    pcloop.h

FORMS    += fos_spd.ui \
    pcloop.ui
