/*
 *  Copyright 2012 Yury Makarevich
 *
 *  This file is part of Tomodoro.
 *
 *  Tomodoro is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Tomodoro is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Tomodoro.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <QtGui/QApplication>
#include "settings.h"

#include "timer.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(false);

    // set up settings
    QCoreApplication::setOrganizationName("Makarevich & Co");
    QCoreApplication::setOrganizationDomain("makarevich-and-co.com");
    QCoreApplication::setApplicationName("Tomodoro");

    QSettings::setDefaultFormat(QSettings::IniFormat);




    Timer       timer;



    return a.exec();
}
