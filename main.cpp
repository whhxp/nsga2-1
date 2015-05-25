#include "mainwindow.h"
#include <QApplication>
#include <individual.h>
#include <nsga2.h>
#include <QDebug>



#include <string>
#include <vector>

template <typename T> bool PComp(const T * const & a, const T * const & b)
{
   return a->getY1() > b->getY1();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();




    return a.exec();
}
