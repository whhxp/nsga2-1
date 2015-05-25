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
 * Funkcma zwraca 1 wtedy gdy rozwiązanie p dominume nad rozwiązanie q
 * Minimalizacma funkcmi celu
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

        (*iter)->setY1( 4*x1*x1 + 4*x2*x2 );
        (*iter)->setY2((x1-5)*(x1-5) + (x2-5)*(x2-5));

    }
}

void Nsga2::show()
{
//    for(list<Individual *>::iterator p = F[0]->begin(); p != F[0]->end(); p++)
//    {
//        (*p)->show();
//    }

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

//    for(unsigned int i = 0; i < y2.size();i++)
//    {
//        qDebug() << y2[i] << endl;
//    }


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



template <typename T> bool Comp1(const T * const & a, const T * const & b)
{
   return a->getY1() > b->getY1();
}

template <typename T> bool Comp2(const T * const & a, const T * const & b)
{
   return a->getY2() > b->getY2();
}

void Nsga2::crowding_distance_assigment()
{

    for(unsigned int i = 0; i < F.size()-1;i++)
    {
        double min = 0;
        double max = 0;

        for(list<Individual*>::iterator I = F[i]->begin(); I != F[i]->end();I++)
        {
            (*I)->d = 0;
        }

        for(int m = 1;m <= 2; m++)
        {
            if(m == 1)
            {
                F[i]->sort( Comp1<Individual>);

                min = F[i]->back()->getY1();
                max = F[i]->front()->getY1();

                F[i]->back()->d = INT_MAX;
                F[i]->front()->d = INT_MAX;

                if(F[i]->size() == 2 || F[i]->size() == 1)
                {
                    continue;
                }

            }
            if( m == 2)
            {
                F[i]->sort( Comp2<Individual>);

                min = F[i]->back()->getY2();
                max = F[i]->front()->getY2();

                F[i]->back()->d = INT_MAX;
                F[i]->front()->d = INT_MAX;

                if(F[i]->size() == 2 || F[i]->size() == 1)
                {
                    continue;
                }
            }

            for(list<Individual*>::iterator I = next(F[i]->begin()); I != prev(F[i]->end()); I++)
            {



                if(m == 1)
                {
                    (*I)->d +=  (*prev(I))->getY1() - (*next(I))->getY1(); // (max - min);
                }

                if(m == 2)
                {
                    (*I)->d +=  (*prev(I))->getY2() - (*next(I))->getY2(); // (max -min);
                }
            }

//            qDebug() << " --------------------" << endl;
//            qDebug() << "min:" << min << "max:" << max << endl;
//            qDebug() << " i = " << i << endl;
//            qDebug() << " --------------------" << endl;
//            show();
        }
    }
}

void Nsga2::BinaryTournamentSelection()
{
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0,N-1);

    while(Q.size() < N)
    {
        int alfa = distribution(generator);
        list<Individual*>::iterator p1 = next(P.begin(),alfa);
        int beta = distribution(generator);
        list<Individual*>::iterator q1 = next(P.begin(),beta);

        Q.push_back(Individual::crossover1(*p1,*q1));
        //Q.push_back(Individual::crossover2(*p1,*q1));
        Q.push_back(Individual::mutation(*p1,0,5));
    }
}


template <typename T> bool crowded_comparison_operator(const T * const & p, const T * const & q)
{
    if( p->getRank() < q->getRank()) return true;
    else if(p->getRank() == q->getRank())
    {
        if(p->getD() > q->getD()) return true;
        else return false;
    }
    else if( p->getRank() > q->getRank()) return false;
}


void Nsga2::MainLoop()
{
    BinaryTournamentSelection();
    //qDebug() << "1. P size: " << P.size() << "Q size" << Q.size() << endl;
    P.splice(P.begin(),Q);
    Q.clear();
    setZero();
    evaluation();
    fast_non_dominated_sort();
    //qDebug() << "2. P size: " << P.size() << "Q size" << Q.size() << endl;
    crowding_distance_assigment();
    P.sort(crowded_comparison_operator<Individual>);
    //qDebug() << "jflsjd;sljfafklfdkjfdkajlfdjkalfj" << endl;
    while(P.size() > N ) P.pop_back();
    //show();
    t+= 1;

}
void Nsga2::setZero()
{
    for(list<Individual*>::iterator iter = P.begin(); iter != P.end(); iter++)
    {
        (*iter)->rank = 0;
        (*iter)->n = 0;
        (*iter)->S.clear();
        (*iter)->d = 0;
    }

    F.clear();

//    for(vector<list<Individual*>*>::iterator i = F.begin(); i != F.end(); i++)
//    {
//        (*i)->clear();
//    }
}

//vector<double> returnX1()
//{

//}

//vector<double> returnX2()
//{

//}
