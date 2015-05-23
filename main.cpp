#include "mainwindow.h"
#include <QApplication>
#include <individual.h>
#include <nsga2.h>

#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
