QT   +=

CONFIG += console no_qt_ver_in_path
CONFIG -= app_bundle

TEMPLATE = app

PRECOMPILED_HEADER = project_pch.h
TARGET = example1

include(../../common.pri)
include(../../PropertySystem.pri)

RC_FILE =

SOURCES += main.cpp

HEADERS += \
    project_pch.h
