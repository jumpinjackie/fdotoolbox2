#-------------------------------------------------
#
# Project created by QtCreator 2012-12-25T13:42:53
#
#-------------------------------------------------

QT       += xml

QT       -= gui

TARGET = FdoTbCore
TEMPLATE = lib

DEFINES += FDOTBCORE_LIBRARY

SOURCES += \
    qfdoconnectionmanager.cpp \
    qfdoconnectionhandle.cpp

HEADERS +=\
        FdoTbCore_global.h \
    qfdoconnectionmanager.h \
    qfdoconnectionhandle.h

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

win32: LIBS += -L$$PWD/../../Thirdparty/Fdo_x86/Lib/ -lFDO -lFDOCommon

INCLUDEPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
DEPENDPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
