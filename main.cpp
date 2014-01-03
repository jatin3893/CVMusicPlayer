#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    
    return a.exec();
}


/*
*Super Class for debug and error signals and slots to be extended by all classes!
*Use Textures for GUI
*
*/
