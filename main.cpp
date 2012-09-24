#include <QtGui/QApplication>


#include "timer.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(false);

//    PieView     pie;

//    pie.show();



    Timer       timer;





    return a.exec();
}
