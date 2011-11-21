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
    sagent.cpp \
    price_predictor.cpp


HEADERS += \
    server.h \
    agent.h \
    aagent.h \
    sagent.h \
    price_predictor.h




















