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
