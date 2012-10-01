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
    abstractview.cpp \
    colorselector.cpp \
    barview.cpp \
    customlabel.cpp

HEADERS  += \
    timer.h \
    pieview.h \
    settings.h \
    settingsdialog.h \
    abstractview.h \
    colorselector.h \
    barview.h \
    customlabel.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    resources/tomato.png \
    README.txt
