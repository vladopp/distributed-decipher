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
    ..\common\configmanager.cpp \
    ..\common\vigenerecipher.cpp

RESOURCES += \
    resources.qrc

INCLUDEPATH += "..\common"

FORMS    += \
    mainwindow.ui

HEADERS += taskgenerator.h \
    ..\common\keygenerator.h \
    ..\common\dbmanager.h \
    ..\common\task.h \
    mainwindow.h \
    ..\common\configmanager.h \
    ..\common\vigenerecipher.h
