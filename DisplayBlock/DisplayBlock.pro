#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T16:39:05
#
#-------------------------------------------------

QT       -= gui

TARGET = DisplayBlock
TEMPLATE = lib

DEFINES += DISPLAYBLOCK_LIBRARY

SOURCES += displayblockfactory.cpp

HEADERS += displayblockfactory.h\
        displayblock_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
