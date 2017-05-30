#-------------------------------------------------
#
# Project created by QtCreator 2017-05-21T21:10:16
#
#-------------------------------------------------

QT -= core gui
QT += core sql

CONFIG += c++11

TARGET = common
TEMPLATE = lib

INCLUDEPATH += "C:\Program Files\PostgreSQL\9.6\include"
LIBS += "C:\Program Files\PostgreSQL\9.6\lib\libpq.lib"

SOURCES += dbmanager.cpp \
    keygenerator.cpp \
    task.cpp \
    configmanager.cpp

HEADERS += dbmanager.h \
    keygenerator.h \
    task.h \
    configmanager.h
