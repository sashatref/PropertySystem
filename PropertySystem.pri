INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

!isEmpty(OUT_DIR) {
    LIBS += -L$${OUT_DIR}
} else {
    LIBS += -L$$PWD/bin
}

LIBS += -l$$generateTarget(PropertySystem)


