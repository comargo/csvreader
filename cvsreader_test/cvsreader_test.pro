#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T21:13:23
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_cvsreadertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_cvsreadertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../csvreader/release/ -lcsvreader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../csvreader/debug/ -lcsvreader
else:unix: LIBS += -L$$OUT_PWD/../csvreader/ -lcsvreader

INCLUDEPATH += $$PWD/../csvreader
DEPENDPATH += $$PWD/../csvreader
