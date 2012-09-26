#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T12:48:35
#
#-------------------------------------------------

QT       += core gui

TARGET = tomodoro
TEMPLATE = app


SOURCES += main.cpp \
    timer.cpp \
    pieview.cpp \
    settings.cpp \
    settingsdialog.cpp \
    abstractview.cpp

HEADERS  += \
    timer.h \
    pieview.h \
    settings.h \
    settingsdialog.h \
    abstractview.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    resources/tomato.png \
    README.txt
