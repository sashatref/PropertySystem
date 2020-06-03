#/********************************************************************
#	created:        16/02/2017
#	filename:       PropertySystem.pro
#	file ext:	qmake project
#	author:		Aleksandr Neborak

#	Project:        PropertySystem

#*********************************************************************/
QT  +=

TEMPLATE = lib
TARGET = PropertySystem
CONFIG += no_qt_ver_in_path

DEFINES += PROPERTY_SYSTEM_DEFINE
#DEFINES += STATIC

PRECOMPILED_HEADER = project_pch.h

include(../common.pri)

#installs section

isEmpty(INSTALL_DIR) {
    INSTALL_DIR = $$PWD/..
}

priFile.files = /../helperlibrary.pri
priFile.path = $${INSTALL_DIR}

binFiles.files += /../bin/*.so
binFiles.files += /../bin/*.dll
binFiles.files += /../bin/*.lib
binFiles.path = $${INSTALL_DIR}/bin


prop.files +=               export.h                \
                            iproperty.h             \
                            metaobject.h            \
                            metaproperty.h          \
                            metapropertymacro.h     \
                            converters.h            \


prop.path         =       $${INSTALL_DIR}/include/PropertySystem

Variant.files   +=          Variant/variant.h               \
                            Variant/variantconverter.h      \
                            Variant/variantholder.h         \
                            Variant/variantoutput.h         \
                            Variant/variantmacro.h          \
                            Variant/variantvector.h         \
                            Variant/variantmap.h            \

Variant.path    +=          $${INSTALL_DIR}/include/PropertySystem/Variant

MetaFiles.files +=          MetaType/metatype.h              \
                            MetaType/metatypelessbase.h      \
                            MetaType/metatypedestructorbase.h\
                            MetaType/metatypeequalsbase.h    \
                            MetaType/metatypeoutputbase.h

MetaFiles.path =            $${INSTALL_DIR}/include/PropertySystem/MetaType


INSTALLS += priFile             \
            binFiles            \
            prop                \
            MetaFiles           \
            Variant

HEADERS += \
    buildNumber.h \
    export.h \
    iproperty.h \
    metaproperty.h \
    metaobject.h \
    metapropertymacro.h \
    Variant/variant.h \
    Variant/variantmacro.h \
    Variant/variantholder.h \
    Variant/variantconverter.h \
    Variant/variantoutput.h \
    Variant/variantvector.h \
    Variant/variantmap.h \
    converters.h \
    MetaType/metatype.h \
    MetaType/metatypelessbase.h \
    MetaType/metatypedestructorbase.h \
    MetaType/metatypeequalsbase.h \
    MetaType/metatypeoutputbase.h \
    Variant/basetypeconverters.h

SOURCES += \
    iproperty.cpp \
    metaproperty.cpp \
    metaobject.cpp \
    Variant/variant.cpp \
    Variant/variantholder.cpp \
    Variant/variantconverter.cpp \
    Variant/variantoutput.cpp \
    Variant/variantvector.cpp \
    Variant/variantmap.cpp \
    converters.cpp \
    MetaType/metatype.cpp \
    MetaType/metatypelessbase.cpp \
    MetaType/metatypedestructorbase.cpp \
    MetaType/metatypeequalsbase.cpp \
    MetaType/metatypeoutputbase.cpp \
    Variant/basetypeconverters.cpp
