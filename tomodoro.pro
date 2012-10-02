#
# Copyright 2012 Yury Makarevich
#
# This file is part of Tomodoro.
#
# Tomodoro is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Tomodoro is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Tomodoro.  If not, see <http://www.gnu.org/licenses/>.
#

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
    COPYING \
    README
