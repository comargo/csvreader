#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T20:59:37
#
#-------------------------------------------------

QT       -= gui

TARGET = csvreader
TEMPLATE = lib

DEFINES += CSVREADER_LIBRARY

SOURCES += csvreader.cpp \
    csvreader_p.cpp

HEADERS += csvreader.h\
        csvreader_global.h \
    csvreader_p.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
