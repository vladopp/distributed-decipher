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

SOURCES += dbmanager.cpp \
    keygenerator.cpp \
    task.cpp

HEADERS += dbmanager.h \
    keygenerator.h \
    task.h
