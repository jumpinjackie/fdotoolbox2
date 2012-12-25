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
    aboutdialog.cpp \
    aboutpluginsdialog.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    aboutpluginsdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    aboutpluginsdialog.ui

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

win32: LIBS += -L$$PWD/../../Thirdparty/Fdo_x86/Lib/ -lFDO

INCLUDEPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc
DEPENDPATH += $$PWD/../../Thirdparty/Fdo_x86/Inc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FdoTbShared/release/ -lFdoTbShared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FdoTbShared/debug/ -lFdoTbShared

INCLUDEPATH += $$PWD/../FdoTbShared
DEPENDPATH += $$PWD/../FdoTbShared

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FdoTbCore/release/ -lFdoTbCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FdoTbCore/debug/ -lFdoTbCore

INCLUDEPATH += $$PWD/../FdoTbCore
DEPENDPATH += $$PWD/../FdoTbCore
