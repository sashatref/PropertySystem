INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

!isEmpty(OUT_DIR) {
    LIBS += -L$${OUT_DIR}
} else {
    LIBS += -L$$PWD/bin/$${QT_VERSION}
}

LIBNAME = PropertySystem

contains(DEFINES, AVIA) {
    LIBS += -lAvia$${MYCOMPILER_POSTFIX}_$${LIBNAME}$${STATIC_POSTFIX}$${DEBUG_POSTFIX}
} else {
    LIBS += -l$${LIBNAME}$${STATIC_POSTFIX}$${MYCOMPILER_POSTFIX}$${DEBUG_POSTFIX}
}

