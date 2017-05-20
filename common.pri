#DEFINES
    #PLUGIN     - для плагинов, другой каталог автоинкремента, другой каталог выходных бинырных файлов
    #STATIC     - для статической версии библиотеки или программы
    #NO_RCFILE  - если не нужен RC-файл
    #NO_PDB     - если не нужны pdb файлы в релизной версии
    #NO_AI      - если не нужен автоинкремент версии
    #NO_TR      - если не нужны файлы переводов
    #DEPLOY
    #DEBUGINFO
    #PREPROCESSOR   - формирования вывода работы препроцессора

#RESERVER INSTALLS
    #translations - для переводов

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

equals(compileName, win32-g++) {
    MYCOMPILER_POSTFIX = _gcc
}

equals(compileName, linux-g++) {
    MYCOMPILER_POSTFIX =
}




DEBUG_POSTFIX =
CONFIG(debug, debug|release) {
    DEBUG_POSTFIX = _d
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

contains(DEFINES, AVIA) {
    TARGET = Avia$${MYCOMPILER_POSTFIX}_$${TARGET}$${STATIC_POSTFIX}$${DEBUG_POSTFIX}
} else {
    TARGET = $${TARGET}$${STATIC_POSTFIX}$${MYCOMPILER_POSTFIX}$${DEBUG_POSTFIX}
}

contains(DEFINES, PLUGIN) {
    TARGET = plugins/$${TARGET}
}

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




#каталог, где будут собиарься бинарные файлы
!contains(DEFINES, NO_DESTDIR) {
    isEmpty(DESTDIR) {

        DEST_FOLDER = ../bin/$${QT_VERSION}
        BASE_DESTDIR = $${DEST_FOLDER}

        contains(DEFINES, SUBPROJECT) {
            DEST_FOLDER = ../$${DEST_FOLDER}
        }

        DESTDIR = $${DEST_FOLDER}
        DESTDIR_TARGET = $${DEST_FOLDER}
    }
}

#работа автоинкремента вервсии
!contains(DEFINES, NO_AI) {

    AI_PATH = $$PWD/../bin

    win32 {
        build_nr.commands = $${AI_PATH}/VersionAutoIncrement.exe $$BASEPWD/buildNumber.h
    }

    unix {
        build_nr.commands = $${AI_PATH}/VersionAutoIncrement $$BASEPWD/buildNumber.h
    }

    build_nr.depends = FORCE
    QMAKE_EXTRA_TARGETS += build_nr
    PRE_TARGETDEPS += build_nr
}




#windeployqt
#проверяем установлен ли DEFINES += DEPLOY, если да, то проверяем есть ли windeployqt.exe
#если найден, то проверяем установлен ли DEST_DIR, если да,
# то проверяем это приложение или библиотека и выполняем windeployqt
win32{
    contains(DEFINES, DEPLOY) {
        !contains(DEFINES, STATIC){

            exists( $(QTDIR)/bin/windeployqt.exe ) {
                equals(IS_DESTDIR_EMPTY ,0) {
                    equals(TEMPLATE, lib) {
                            contains(DEFINES, PLUGIN) {
                                QMAKE_POST_LINK += $(QTDIR)/bin/windeployqt.exe $$DESTDIR/$${TARGET}.dll -libdir $${BASE_DESTDIR} -plugindir $${BASE_DESTDIR}
                            } else {
                                QMAKE_POST_LINK += $(QTDIR)/bin/windeployqt.exe $$DESTDIR/$${TARGET}.dll
                            }
                        }

                    equals(TEMPLATE, app) {
                            QMAKE_POST_LINK += $(QTDIR)/bin/windeployqt.exe $$DESTDIR/$${TARGET}.exe
                        }
                } else {
                   warning("You must set DEST_DIR to use DEPLOY tool")
                }
            } else {
                warning("Windeployqt not found")
            }#end exist
        }#end check STATIC
    }#end check DEPLOY
}

#файлы переводов
!contains(DEFINES, NO_TR) {
    TRANSLATIONS    = translate/ru_$$basename(BASE_TARGET).ts translate/en_$$basename(BASE_TARGET).ts

    translations.files = translate/*.qm
    translations.path = $${DESTDIR}/translate

    INSTALLS += translations
}
