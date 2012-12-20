#-------------------------------------------------
#
# Project created by QtCreator 2012-12-20T22:44:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FdoToolbox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    objectexplorerwidget.cpp

HEADERS  += mainwindow.h \
    plugin_interface.h \
    objectexplorerwidget.h

FORMS    += mainwindow.ui \
    objectexplorerwidget.ui

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

win32: LIBS += -L$$PWD/../../Thirdparty/Fdo_x86/Lib/ -lFDO

INCLUDEPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
DEPENDPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
