TEMPLATE = app

QT += core gui widgets
QT += core gui
QT += core sql
CONFIG += c++11

SOURCES += main.cpp \
    taskgenerator.cpp \
    ..\common\keygenerator.cpp \
    ..\common\dbmanager.cpp \
    ..\common\task.cpp \
    mainwindow.cpp \
    ..\common\configmanager.cpp

RESOURCES +=

INCLUDEPATH += "..\common"

FORMS    += \
    mainwindow.ui

HEADERS += taskgenerator.h \
    ..\common\keygenerator.h \
    ..\common\dbmanager.h \
    ..\common\task.h \
    mainwindow.h \
    ..\common\configmanager.h
