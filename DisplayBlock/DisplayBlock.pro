 #-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T16:39:05
#
#-------------------------------------------------

TARGET = DisplayBlock
TEMPLATE = lib

QT += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


DEFINES += DISPLAYBLOCK_LIBRARY
INCLUDEPATH    += ../Core

SOURCES += displayblockfactory.cpp \
    displayblock.cpp \
    displayblockproperties.cpp

HEADERS += displayblockfactory.h\
        displayblock_global.h \
    displayblock.h \
    displayblockproperties.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    images.qrc
