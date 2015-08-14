#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T16:39:05
#
#-------------------------------------------------

TARGET = DisplayBlock
TEMPLATE = lib

DEFINES += DISPLAYBLOCK_LIBRARY
INCLUDEPATH    += ../Core

SOURCES += displayblockfactory.cpp \
    displayblock.cpp

HEADERS += displayblockfactory.h\
        displayblock_global.h \
    displayblock.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    images.qrc
