#-------------------------------------------------
#
# Project created by QtCreator 2015-07-08T23:57:03
#
#-------------------------------------------------

QT       -= gui

TARGET = SumBlock
TEMPLATE = lib

DEFINES += SUMBLOCK_LIBRARY
INCLUDEPATH    += ../Core
SOURCES += sumblockfactory.cpp

HEADERS += sumblockfactory.h\
        sumblock_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
