#-------------------------------------------------
#
# Project created by QtCreator 2015-07-08T23:58:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Core
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x
#QMAKE_CXXFLAGS += -std=gnu++0x
#CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    pluginmanager.cpp \
    toolbox.cpp \
    renderarea.cpp \
    propertieswidget.cpp \
    blockview.cpp \
    simulinkengine.cpp \
    connection.cpp \
    observable.cpp \
    connectionview.cpp

HEADERS  += mainwindow.h \
    blockfactoryinterface.h \
    blockpropertiesinterface.h \
    pluginmanager.h \
    toolbox.h \
    renderarea.h \
    propertieswidget.h \
    blockview.h \
    blockinterface.h \
    simulinkengine.h \
    connection.h \
    connectioninterface.h \
    observer.h \
    observable.h \
    connectionview.h \
    view.h
