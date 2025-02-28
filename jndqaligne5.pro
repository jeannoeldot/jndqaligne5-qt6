#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T10:41:42
#
#-------------------------------------------------

isEmpty( PREFIX ){
 PREFIX =  /usr
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jndqaligne5
TEMPLATE = app

CONFIG += qt \
    warn_on

DEFINES += PREFIX=\"$${PREFIX}\"


SOURCES += main.cpp\
        caligne5.cpp \
    cpreference.cpp \
    cjoueur.cpp \
    chumain.cpp \
    cordi.cpp \
    cjeu.cpp \
    sdlplayer.cpp

HEADERS  += caligne5.h \
    enumeration.h \
    constante.h \
    cpreference.h \
    cjoueur.h \
    chumain.h \
    cordi.h \
    cjeu.h \
    sdlplayer.h

RESOURCES += \
    jndqaligne5.qrc

DISTFILES += \
    COPYING \
    desktop/jndqaligne5.desktop \
    desktop/jndqaligne5.png \
    README

unix|win32: LIBS += -lSDL_mixer

unix|win32: LIBS += -lSDL

TRANSLATIONS += jndqaligne5_fr.ts

FORMS += \
    dlgpreference.ui

unix:!mac {
    binary.path += $${PREFIX}/bin/
    binary.files += jndqaligne5
    pixmap.path +=  $${PREFIX}/share/pixmaps/
    pixmap.files +=  desktop/jndqaligne5.png
    desktop.path +=  $${PREFIX}/share/applications/
    desktop.files +=  desktop/jndqaligne5.desktop
    INSTALLS += binary \
                pixmap \
                desktop
}
