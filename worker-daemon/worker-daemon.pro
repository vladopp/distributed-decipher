QT += core sql
QT -= gui

CONFIG += c++11

TARGET = worker-daemon
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    dbmanager.cpp \
    confidenceevaluator.cpp
    vigenerecipher.cpp

INCLUDEPATH += "C:\Program Files\PostgreSQL\9.6\include"
LIBS += "C:\Program Files\PostgreSQL\9.6\lib\libpq.lib"

HEADERS += \
    dbmanager.h \
    confidenceevaluator.h
    vigenerecipher.h
