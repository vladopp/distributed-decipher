TEMPLATE = app

QT += core gui widgets
QT += core sql
CONFIG += c++11

SOURCES += main.cpp \
    taskgenerator.cpp \
    ..\common\keygenerator.cpp \
    ..\common\dbmanager.cpp \
    ..\common\task.cpp

RESOURCES +=

INCLUDEPATH += "..\common"

FORMS    += mainwindow.ui

HEADERS += taskgenerator.h \
    ..\common\keygenerator.h \
    ..\common\dbmanager.h \
    ..\common\task.h
