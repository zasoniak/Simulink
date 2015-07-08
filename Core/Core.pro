#-------------------------------------------------
#
# Project created by QtCreator 2015-07-08T23:58:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Core
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pluginmanager.cpp \
    toolbox.cpp \
    renderarea.cpp \
    propertieswidget.cpp \
    blockview.cpp

HEADERS  += mainwindow.h \
    blockfactoryinterface.h \
    connectorinterface.h \
    blockpropertiesinterface.h \
    pluginmanager.h \
    toolbox.h \
    renderarea.h \
    propertieswidget.h \
    blockview.h \
    blockinterface.h
