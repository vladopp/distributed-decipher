QT += core sql
QT -= gui

CONFIG += c++11

TARGET = worker
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    confidenceevaluator.cpp \
    vigenerecipher.cpp \
    ..\common\keygenerator.cpp \
    ..\common\task.cpp \
    ..\common\dbmanager.cpp \
    ..\common\configmanager.cpp

INCLUDEPATH += "C:\Program Files\PostgreSQL\9.6\include" \
               "..\common"
LIBS += "C:\Program Files\PostgreSQL\9.6\lib\libpq.lib"


HEADERS += confidenceevaluator.h \
    vigenerecipher.h \
    ..\common\keygenerator.h \
    ..\common\task.h \
    ..\common\dbmanager.h \
    ..\common\configmanager.h
