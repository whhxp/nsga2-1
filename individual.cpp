#include "individual.h"
#include <QDebug>

Individual::Individual()
    :n(0), d(0), x1(0), x2(0), y1(0), y2(0), rank(0)
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

void Individual::show() const
{
    qDebug() << "--------------------" << endl;
    qDebug() << "x1: " << x1 << "x2: " << x2 << endl;
    qDebug() << "y1: " << y1 << "y2: " << y2 << endl;
    qDebug() << "n: " << n << " rank: " << rank << " d: " << d << endl;
}

bool Individual::compare1( const Individual *a, const Individual *b)
{

    a->show();
    b->show();
    return (a->getY1() > b->getY1());
}

bool Individual::compare2( const Individual *a, const Individual *b)
{
    return (a->getY2() > b->getY2());
}


Individual* Individual::crossover1(Individual *p1, Individual *p2)
{
    Individual *nowy = new Individual();
    std::random_device generator;
    std::uniform_real_distribution<double> udistribution(0,1);
    double alfa = udistribution(generator);
    nowy->setX1(alfa * p1->getX1()+ (1 - alfa) * p2->getX1());
    nowy->setX2(alfa * p1->getX2()+ (1 - alfa) * p2->getX2());
    return nowy;
}

Individual* Individual::crossover2(Individual *p2, Individual *p1)
{
    Individual *nowy = new Individual();
    std::random_device generator;
    std::uniform_real_distribution<double> udistribution(0,1);
    double alfa = udistribution(generator);
    nowy->setX1(alfa * p2->getX1()+ (1 - alfa) * p1->getX1());
    nowy->setX2(alfa * p2->getX2()+ (1 - alfa) * p1->getX2());
    return nowy;
}

Individual* Individual::mutation(Individual *p, double min, double max)
{
    Individual *nowy = new Individual();
    std::random_device generator;
    std::uniform_real_distribution<double> udistribution(0,1);
     std::uniform_real_distribution<double> distribution(min,max);
    double alfa = udistribution(generator);
    if(alfa < 0.5)  nowy->setX1(distribution(generator));
    else if (alfa >= 0.5) nowy->setX2(distribution(generator));
    return nowy;
}

bool Individual::crowded_comparison_operator(Individual *p, Individual *q)
{
    if( p->rank < q->rank) return true;
    else if(p->rank == q->rank)
    {
        if(p->d > q->d) return true;
        else return false;
    }
    else if( p->rank > q->rank) return false;
}

int Individual::getRank() const
{
    return rank;
}

double Individual::getD() const
{
    return d;
}
