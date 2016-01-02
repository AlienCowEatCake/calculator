#-------------------------------------------------
#
# Project created by QtCreator 2014-08-11T05:35:23
#
#-------------------------------------------------

TARGET = calculator
TEMPLATE = app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/helpwindow.cpp

HEADERS  += \
    src/mainwindow.h \
    src/parser/parser.h \
    src/parser/parser_internal.h \
    src/parser/parser_operations.h \
    src/parser/parser_opcodes.h \
    src/parser/parser_compiler_inline.h \
    src/parser/parser_compiler_extcall.h \
    src/helpwindow.h

FORMS    += \
    src/mainwindow.ui \
    src/helpwindow.ui

RESOURCES += src/resources/icons.qrc

win32: RC_FILE += src/resources/icon.rc

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
