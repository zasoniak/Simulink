#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T13:29:35
#
#-------------------------------------------------

QT       -= gui

TARGET = ConstantValueBlock
TEMPLATE = lib

DEFINES += CONSTANTVALUEBLOCK_LIBRARY

SOURCES += constantvalueblockfactory.cpp

HEADERS += constantvalueblockfactory.h\
        constantvalueblock_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
