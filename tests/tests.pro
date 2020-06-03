QT              += core testlib xml

CONFIG += console no_qt_ver_in_path
CONFIG -= app_bundle

TEMPLATE = app

PRECOMPILED_HEADER = project_pch.h
TARGET = PropertySystemTests

include(../common.pri)
include(../PropertySystem.pri)

RC_FILE =

SOURCES += main.cpp \
    test_propertysystem.cpp \
    myclass.cpp \
    myclass2.cpp \
    myclass3.cpp \
    myclass4.cpp \
    simple.cpp \
    test_psvalid.cpp \
    test_metatype.cpp \
    classa.cpp \
    myclass5.cpp \
    myclass6.cpp \
    utils.cpp

HEADERS += \
    test_propertysystem.h \
    myclass.h \
    myclass2.h \
    project_pch.h \
    myclass3.h \
    myclass4.h \
    simple.h \
    test_psvalid.h \
    test_metatype.h \
    classa.h \
    myclass5.h \
    myclass6.h \
    utils.h
