#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T20:07:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_buffertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_buffertest.cpp \
    ../../FOS/buffer.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += D:\\FOS\\FOS \

HEADERS += \
    ../../FOS/buffer.h
