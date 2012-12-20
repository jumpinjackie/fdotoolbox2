#-------------------------------------------------
#
# Project created by QtCreator 2012-12-20T22:58:31
#
#-------------------------------------------------

QT       += core gui widgets xml

TARGET = CorePlugin
TEMPLATE = lib

CONFIG += plugin

INCLUDEPATH += $$PWD/../FdoToolbox

DEFINES += COREPLUGIN_LIBRARY

SOURCES += coreplugin.cpp

HEADERS += coreplugin.h\
        CorePlugin_global.h

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

Debug:DESTDIR = ../FdoToolbox/debug/plugins
Release:DESTDIR = ../FdoToolbox/release/plugins

win32: LIBS += -L$$PWD/../../Thirdparty/Fdo_x86/Lib/ -lFDO

INCLUDEPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
DEPENDPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
