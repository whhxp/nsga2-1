#include "nsga2.h"

//typedef exprtk::symbol_table<double> symbol_table_t;
//typedef exprtk::expression<double> expression_t;
//typedef exprtk::parser<double> parser_t;
//typedef exprtk::parser_error::type error_t;

Nsga2::Nsga2(int n, int t)
    :N(n), T(t)
{}

void Nsga2::init_population(double min, double max)
{
    for(int i = 0; i < N; i++)
    {
        Individual *p = new Individual();
        p->setRandX(min, max);
        P.push_front(p);
    }
}

/*!
 * \brief Nsga2::dominates
 * Funkcja zwraca 1 wtedy gdy rozwiązanie p dominuje nad rozwiązanie q
 * Minimalizacja funkcji celu
 * \param p
 * \param q
 * \return
 */
bool Nsga2::dominates(Individual *p, Individual *q)
{
    double py1 = p->getY1();
    double qy1 = q->getY1();

    int bool1 = py1 <= qy1;

    double py2 = p->getY2();
    double qy2 = q->getY2();

    int bool2 = py2 <= qy2;

    return bool1 || bool2;
}

void Nsga2::fast_non_dominated_sort()
{
    F.push_back(new list<Individual*>);
    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        (*p)->S.empty();
        (*p)->n = 0;

        for(list<Individual *>::iterator q = P.begin(); q != P.end(); q++)
        {
            if(p == q) continue;
            if(dominates(*p,*q))
            {
                (*p)->S.push_back(*q);
            }
            else
            {
               (*p)->n++;
            }
        }

        if( (*p)->n == 0 )
        {
            (*p)->rank = 0;
            F[0]->push_front(*p);
        }
    }
    int i = 0;
    while(F[i]->size()!= 0)
    {
        list<Individual *> *Q = new list<Individual *>();
        for(list<Individual *>::iterator p = F[i]->begin(); p != F[i]->end(); p++)
        {
            for(vector<Individual *>::iterator q = (*p)->S.begin(); q != (*p)->S.end();q++)
            {
                (*q)->n--;
                if((*q)->n == 0)
                {
                    (*q)->rank = i+1;
                    Q->push_front(*q);
                }
            }
        }
        i++;
        F.push_back(new list<Individual*>);
        F[i] = Q;
    }
}

void Nsga2::evaluation()
{
    for(list<Individual *>::iterator iter = P.begin(); iter != P.end();iter++ )
    {
        double x1 = (*iter)->getX1();
        double x2 = (*iter)->getX2();

        (*iter)->setY1( x1 * x1);
        (*iter)->setY2( (x2 + 0.25) * (x2 + 0.25) );

    }
}

void Nsga2::show()
{
    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        (*p)->show();
    }
}

vector<double> Nsga2::returnY1()
{
    vector<double> y1;
    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        y1.push_back( (*p)->getY1() );
    }
    return y1;
}

vector<double> Nsga2::returnY2()
{
    vector<double> y2;
    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        y2.push_back( (*p)->getY2() );
    }
    return y2;
}

vector<double> Nsga2::returnY1F0()
{
    vector<double> y1;
    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        if((*p)->rank == 0)
        {
            y1.push_back( (*p)->getY1() );
        }
    }
    return y1;
}

vector<double> Nsga2::returnY2F0()
{
    vector<double> y2;
    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        if((*p)->rank == 0)
        {
            y2.push_back( (*p)->getY2() );
        }
    }
    return y2;
}

void Nsga2::crowding_distance_assigment()
{
    int i = 0;
    for(list<Individual*>::iterator I = F[i]->begin(); I != F[i]->end();I++)
    {
        (*I)->d = 0;
    }

    for(list<Individual*>::iterator I = F[i]->begin(); I != F[i]->end();I++)
    {

    }

}

//vector<double> returnX1()
//{

//}

//vector<double> returnX2()
//{

//}
