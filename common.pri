 #DEFINES
    #PLUGIN     - для плагинов, другой каталог автоинкремента, другой каталог выходных бинырных файлов
    #STATIC     - для статической версии библиотеки или программы
    #NO_RCFILE  - если не нужен RC-файл
    #AVIA       - формирования имени файла в стиле AVIA
    #AVIA_2     - формирования имени файла в стиле AVIA

    #NO_PDB     - если не нужны pdb файлы в релизной версии
    #NO_AI      - если не нужен автоинкремент версии
    #NO_TR      - если не нужны файлы переводов
    #DEPLOY
    #NO_DEPLOY
    #DEBUGINFO
    #PREPROCESSOR   - формирования вывода работы препроцессора
    #SEH

#CONFIG
    #no_qt_ver_in_path

BASEPWD = $${_PRO_FILE_PWD_}

DEFINES += COMMON_PRI_INCLUDED

contains(DEFINES, PREPROCESSOR) {
    QMAKE_CXXFLAGS_RELEASE += /P
    QMAKE_CXXFLAGS_DEBUG += /P
}

!isEmpty(OUT_DIR) {
    DESTDIR = $${OUT_DIR}
}

BASE_TARGET = $${TARGET}  #имя выходного файла, заданное пользователем
BASE_DESTDIR = $${DESTDIR}  #каталог для выходных файлов
isEmpty(DESTDIR) {
    IS_DESTDIR_EMPTY = 1
} else {
    IS_DESTDIR_EMPTY = 0
}

contains(DEFINES, SEH) {
    QMAKE_CXXFLAGS_STL_ON = -EHa
    QMAKE_CXXFLAGS_EXCEPTIONS_ON = -EHa
}


#если в QMAKESPEC есть static, то проект будет собран в статике
ISSTATIC = $$find(QMAKESPEC, "static")

count(ISSTATIC, 1) {
    DEFINES += STATIC
}

isEmpty(MYCOMPILER_POSTFIX) {
    MYCOMPILER_POSTFIX = _vc10
}

compileName=$$basename(QMAKESPEC)

equals(compileName, win32-msvc2013) {
        MYCOMPILER_POSTFIX = _vc12
}

equals(compileName, win32-msvc2010) {
        MYCOMPILER_POSTFIX = _vc10
}

equals(compileName, win32-msvc2015) {
        MYCOMPILER_POSTFIX = _vc14
}

equals(compileName, win32-msvc) {
        MYCOMPILER_POSTFIX = _vc14
    }

equals(compileName, win32-g++) {
        MYCOMPILER_POSTFIX = _gcc
}

equals(compileName, linux-g++) {
        MYCOMPILER_POSTFIX =
}




contains(QMAKE_TARGET.arch, x86_64) {
    ARCH_PREFIX = -amd64
} else {
    ARCH_PREFIX =
}


DEBUG_POSTFIX =
CONFIG(debug, debug|release) {
    DEBUG_POSTFIX = _d
}

ACE_STATIC_PREFIX =


mpc_comp{
    CONFIG(debug, debug|release) {
        contains(DEFINES, STATIC) {
            DEBUG_POSTFIX = -sd
            ACE_STATIC_PREFIX = lib
        } else {
            DEBUG_POSTFIX = -d
        }

        ACE_DEBUG_POSTFIX = -d

    } else {
        contains(DEFINES, STATIC) {
            DEBUG_POSTFIX = -s
            ACE_STATIC_PREFIX = lib
        } else {
            DEBUG_POSTFIX =
        }

        ACE_DEBUG_POSTFIX =
    }
}


STATIC_POSTFIX =
contains(DEFINES, STATIC) {
    STATIC_POSTFIX = _static

    equals(TEMPLATE, lib) {
        CONFIG += staticlib
    } else {
        RC_FILE += $$basename(TARGET).rc
    }
} else {
    RC_FILE += $$basename(TARGET).rc
}

contains(DEFINES, NO_RCFILE){
    RC_FILE -= $${TARGET}.rc
}

TARGET = $${TARGET}$${STATIC_POSTFIX}$${MYCOMPILER_POSTFIX}$${DEBUG_POSTFIX}

win32{
    msvc {
        !contains(DEFINES, NO_PDB){
            QMAKE_CXXFLAGS_RELEASE -= -O2
            QMAKE_CXXFLAGS_RELEASE += /Zi /Od
            QMAKE_LFLAGS_RELEASE += /DEBUG
        }
    }
}

unix{

}




no_qt_ver_in_path {
    AVIA_QT_VER =
} else {
    AVIA_QT_VER = $${QT_VERSION}
}




#каталог, где будут собиарься бинарные файлы
!contains(DEFINES, NO_DESTDIR) {
    isEmpty(DESTDIR) {

        DEST_FOLDER = ../bin/$${AVIA_QT_VER}
        BASE_DESTDIR = $${DEST_FOLDER}

        contains(DEFINES, SUBPROJECT) {
            DEST_FOLDER = ../$${DEST_FOLDER}
        }

        contains(DEFINES, SUBPROJECT2) {
            DEST_FOLDER = ../../$${DEST_FOLDER}
        }

        DESTDIR = $${DEST_FOLDER}
        DESTDIR_TARGET = $${DEST_FOLDER}
    }
}


defineReplace(generateTarget){
    baseTarget = $$1

    newTarget = $${baseTarget}$${STATIC_POSTFIX}$${MYCOMPILER_POSTFIX}$${DEBUG_POSTFIX}

    return($$newTarget)
}



