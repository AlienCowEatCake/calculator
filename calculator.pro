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

DEFINES += QT_NO_CAST_FROM_ASCII

*g++*|*clang* {
    QMAKE_CXXFLAGS *= -Wno-long-long
    QMAKE_CXXFLAGS_RELEASE *= -DNDEBUG
}

SOURCES += \
    src/evaluator/evaluator_internal/transition_table.cpp \
    src/evaluator/evaluator_internal/jit/common.cpp \
    src/evaluator/evaluator_internal/jit/func_templates.cpp \
    src/evaluator/evaluator_internal/jit/oper_templates.cpp \
    src/evaluator/evaluator_internal/jit/real_templates.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/helpwindow.cpp

HEADERS  += \
    src/evaluator/evaluator.h \
    src/evaluator/evaluator_operations.h \
    src/evaluator/evaluator_xyz.h \
    src/evaluator/evaluator_internal/evaluator_object.h \
    src/evaluator/evaluator_internal/var_container.h \
    src/evaluator/evaluator_internal/transition_table.h \
    src/evaluator/evaluator_internal/type_detection.h \
    src/evaluator/evaluator_internal/misc.h \
    src/evaluator/evaluator_internal/parse.h \
    src/evaluator/evaluator_internal/simplify.h \
    src/evaluator/evaluator_internal/calculate.h \
    src/evaluator/evaluator_internal/jit/common.h \
    src/evaluator/evaluator_internal/jit/opcodes.h \
    src/evaluator/evaluator_internal/jit/func_templates.h \
    src/evaluator/evaluator_internal/jit/oper_templates.h \
    src/evaluator/evaluator_internal/jit/real_templates.h \
    src/evaluator/evaluator_internal/jit/complex_templates.h \
    src/evaluator/evaluator_internal/jit/compile_inline.h \
    src/evaluator/evaluator_internal/jit/compile_extcall.h \
    src/mainwindow.h \
    src/helpwindow.h

FORMS    += \
    src/mainwindow.ui \
    src/helpwindow.ui

RESOURCES += src/resources/icons.qrc

win32: RC_FILE += src/resources/icon.rc

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
