#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T20:59:37
#
#-------------------------------------------------

QT       -= gui

TARGET = csvreader
TEMPLATE = lib
CONFIG *= static create_prl

CONFIG(shared):DEFINES += CSVREADER_LIBRARY

SOURCES += csvreader.cpp

HEADERS += csvreader.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

STATECHARTS +=
