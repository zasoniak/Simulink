#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T13:29:35
#
#-------------------------------------------------


TARGET = ConstantValueBlock
TEMPLATE = lib

DEFINES += CONSTANTVALUEBLOCK_LIBRARY
INCLUDEPATH    += ../Core

SOURCES += constantvalueblockfactory.cpp \
    constantvalueblock.cpp \
    constantvalueblockproperties.cpp

HEADERS += constantvalueblockfactory.h\
        constantvalueblock_global.h \
    constantvalueblock.h \
    constantvalueblockproperties.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    images.qrc
