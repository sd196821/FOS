TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    datastack.cpp \
    buffer.cpp \
    dock.cpp \
    list.cpp \
    linker.cpp \
    mmu.cpp

HEADERS += \
    datastack.h \
    buffer.h \
    dock.h \
    list.h \
    FOSCore.h \
    FOSType.h \
    linker.h \
    mmu.h

