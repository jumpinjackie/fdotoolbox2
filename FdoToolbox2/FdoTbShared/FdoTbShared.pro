#-------------------------------------------------
#
# Project created by QtCreator 2012-12-25T12:33:18
#
#-------------------------------------------------

QT       += core gui widgets xml

TARGET = FdoTbShared
TEMPLATE = lib

DEFINES += FDOTBSHARED_LIBRARY

SOURCES += \
    objectexplorerwidget.cpp

HEADERS +=\
        FdoTbShared_global.h \
    objectexplorerwidget.h \
    plugin_interface.h

FORMS += \
    objectexplorerwidget.ui

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

win32: LIBS += -L$$PWD/../../Thirdparty/Fdo_x86/Lib/ -lFDO

INCLUDEPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc \
               $$PWD/../FdoTbShared
DEPENDPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
