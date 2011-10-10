#-------------------------------------------------
#
# Project created by QtCreator 2011-10-09T17:20:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AuctionServer
CONFIG   += console x86_64
CONFIG   -= app_bundle i386
LIBS += -lssl -lcrypto

TEMPLATE = app


SOURCES += \
    server.cpp \
    agent.cpp \
    aagent.cpp \
    dagent.cpp \
    sagent.cpp


HEADERS += \
    server.h \
    agent.h \
    aagent.h \
    dagent.h \
    sagent.h
















