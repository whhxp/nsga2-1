#include "individual.h"
#include <QDebug>

Individual::Individual(int zv1, int zv2)
    :n(0), d(0), y1(0), y2(0), rank(0), v1(zv1), v2(zv2)
{
    while(x.size() < v1) x.push_back(0);
    v_max = v1 > v2 ? v1 : v2 ;
    genetic = 0;
}


int Individual::getGenetic()
{
    return genetic;
}

int Individual::setGenetic()
{
    genetic = 1;
}

int Individual::setGeneticZero()
{
    genetic = 0;
}

vector<double> Individual::getX() const
{
    return x;
}

double Individual::getY1() const
{
    return y1;
}

double Individual::getY2() const
{
    return y2;
}

void Individual::setY1andY2(double y1, double y2)
{
    setY1(y1);
    setY2(y2);
}

void Individual::setRandX(vector<double> min, vector<double> max)
{
    std::random_device generator;
    vector<double>  help;

    for(int i = 0; i < v_max;i++)
    {
        std::uniform_real_distribution<double> distribution(min[i],max[i]);
        help.push_back(distribution(generator));
    }

    setX(help);
}

void Individual::setX(vector<double> x)
{
    this->x = x;
}

void Individual::setY1(double y)
{
    y1 = y;
}

void Individual::setY2(double y)
{
    y2 = y;
}

bool Individual::compare1( const Individual *a, const Individual *b)
{

    return (a->getY1() > b->getY1());
}

bool Individual::compare2( const Individual *a, const Individual *b)
{
    return (a->getY2() > b->getY2());
}

/*!
 * \brief Individual::crossover
 * \param p1 szczesliwy rodzic I
 * \param p2 szczesliwy rodzic II
 * \return mały gnojek
 */
Individual* Individual::crossover(Individual *p1, Individual *p2, double ota_c, vector<double> min, vector<double> max)
{
    Individual *nowy = new Individual(p1->v1,p1->v2);
    std::random_device generator;
    std::uniform_real_distribution<double> udistribution(0,1);
    try
    {



        vector<double> help;
        vector<double> px1 = p1->getX();
        vector<double> px2 = p2->getX();

        double u = udistribution(generator);
        double beta = 0;
        if(u < 0.5) beta = pow(2*u,1/(ota_c+1));
        else beta = 1/( pow(2*(1 - u),1/(ota_c+1)));
        double z = 0;


        for(int i = 0; i < p1->v_max; i++)
        {

                z = 0.5*( (1 - beta) * px1[i] + (1 + beta) * px2[i]); // magia
                if( z > max[i])
                {
                    z = max[i];
                    help.push_back(z);
                }
                else if(z < min[i])
                {
                    z = min[i];
                    help.push_back(z);
                }
                else help.push_back(z);
        }
        nowy->setX(help);

    }
    catch (exception &e)
    {
        qDebug() << "Blad" << endl;
    }
    return nowy;
}

/*!
 * \brief Individual::mutation
 * \param p elemet do mutacji
 * \param min zawiera min ograniczenia dla zmiennych
 * \param max zawiera max ograniczenia dla zmiennych
 * \return z mutant X-men
 */
Individual* Individual::mutation(Individual *p, double ota_m, vector<double> min, vector<double> max)
{
    Individual *nowy = new Individual(p->v1,p->v2);
    std::random_device generator;
    std::uniform_real_distribution<double> udistribution(0,1); //generowanie liczb p-losowych z zakresu 0.0 - 1.0
    double rk = udistribution(generator);
    double delta_k;

    if(rk < 0.5) delta_k = pow(2*rk,1/(ota_m + 1)) - 1;
    else delta_k = 1 - pow(2*(1-rk),1/(ota_m+1));

    vector<double> x; // nowy zbior argumentów
    vector<double> parent_x = p->getX();

    double new_x = 0;
    for(int i = 0; i < p->v_max; i++)
    {
        new_x = parent_x[i] + (max[i] - min[i]) * delta_k;
        if( new_x > max[i])
        {
            new_x = max[i];
            x.push_back(new_x);
        }
        else if(new_x < min[i])
        {
            new_x = min[i];
            x.push_back(new_x);
        }
        else x.push_back(new_x);
    }
    nowy->setX(x); // ustawia argumenty
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

string Individual::toStringX() const
{
    stringstream stream;

    stream << "x: ";
    for(int i = 0; i < x.size(); i++)
    {
         stream << x[i] << "; ";
    }
    return stream.str();
}

string Individual::toStringY() const
{
    stringstream stream;

    stream << "f1: " << getY1() << " f2: " << getY2() << endl;

    return stream.str();
}
