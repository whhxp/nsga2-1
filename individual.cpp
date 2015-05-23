#include "individual.h"
#include <QDebug>

Individual::Individual()
    :n(0), d(0)
{}

double Individual::getX1() const
{
    return x1;
}

double Individual::getX2() const
{
    return x2;
}

double Individual::getY1() const
{
    return y1;
}

double Individual::getY2() const
{
    return y2;
}

void Individual::setX1andX2(double x1, double x2)
{
    setX1(x1);
    setX2(x2);
}

void Individual::setY1andY2(double y1, double y2)
{
    setY1(y1);
    setY2(y2);
}

void Individual::setRandX(double min, double max)
{
    std::random_device generator;
    std::uniform_real_distribution<double> distribution(min,max);
    setX1(distribution(generator));
    setX2(distribution(generator));
}

void Individual::setX1(double x)
{
    x1 = x;
}

void Individual::setX2(double x)
{
    x2 = x;
}

void Individual::setY1(double y)
{
    y1 = y;
}

void Individual::setY2(double y)
{
    y2 = y;
}

void Individual::show()
{
    qDebug() << "--------------------" << endl;
    qDebug() << "x1: " << x1 << "x2: " << x2 << endl;
    qDebug() << "y1: " << y1 << "y2: " << y2 << endl;
    qDebug() << "n: " << n << "rank: " << rank << endl;
}

bool Individual::compare1( const Individual &a, const Individual &b)
{
    return a.getY1() > b.getY1();
}

bool Individual::compare2( const Individual &a, const Individual &b)
{
    return a.getY2() > b.getY2();
}
