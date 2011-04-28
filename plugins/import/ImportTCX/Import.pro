#-------------------------------------------------
#
# Project created by QtCreator 2011-04-21T09:04:50
#
#-------------------------------------------------

QT       += xml xmlpatterns

QT       -= gui

TARGET = ImportTCX
TEMPLATE = lib

DEFINES += IMPORT_LIBRARY

SOURCES += cimport.cpp \
    cactivity.cpp \
    clap.cpp \
    ctrackpoint.cpp \
    cposition.cpp

HEADERS += cimport.h\
    cactivity.h \
    clap.h \
    common.h \
    ctrackpoint.h \
    cposition.h

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4D9395A
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Import.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}

LIBS	+= -shared -fPIC
