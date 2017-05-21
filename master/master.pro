TEMPLATE = app

QT += core gui widgets
CONFIG += c++11

SOURCES += main.cpp \
    taskgenerator.cpp \
    ..\common\keygenerator.cpp

RESOURCES +=

INCLUDEPATH += "..\common"

FORMS    += mainwindow.ui

HEADERS += \
    taskgenerator.h \
    ..\common\keygenerator.h
