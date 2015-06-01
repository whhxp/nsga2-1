#include "nsga2.h"




Nsga2::Nsga2(unsigned int n,double CorrosoverToMutation,double MU, double MUM, string s1, int zv1, string s2, int zv2, vector<double> Min, vector<double> Max)
    :N(n),corrosoverToMutation(CorrosoverToMutation), mu(MU),mum(MUM), str1(s1), str2(s2), v1(zv1), v2(zv2), min(Min), max(Max)
{
    v_max = v1 > v2 ? v1 : v2;
}

void Nsga2::init_population()
{
    for(int i = 0; i < N; i++)
    {
        Individual *p = new Individual(v1,v2);
        p->setRandX(min, max);
        P.push_front(p);
    }
}

template <typename T> bool Comp1(const T * const & a, const T * const & b)
{
   return a->getY1() > b->getY1();
}

template <typename T> bool Comp2(const T * const & a, const T * const & b)
{
   return a->getY2() > b->getY2();
}


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
    Parser f1;
    Parser f2;
    double *tab = new double[v_max];
    vector<double> x;

    for(list<Individual *>::iterator iter = P.begin(); iter != P.end();iter++ )
    {


        x = (*iter)->getX();

        for(int i = 0; i < v_max; i++)
        {
            tab[i] = x[i];
        }

        const string table[] = {"x","y","z","g","h"};

        try
        {

            for(int i = 0; i < v1; i++)
            {
                f1.DefineVar(table[i], &(tab[i]));
            }
            f1.SetExpr(str1);
        }
        catch (Parser::exception_type &e)
        {
            qDebug() << "Problem funkcja 1" << endl;
        }

        try
        {
            for(int i = 0; i < v2; i++)
            {
                f2.DefineVar(table[i], &(tab[i]));
            }
            f2.SetExpr(str2);
        }
        catch (Parser::exception_type &e)
        {
            qDebug() << "Problem funkcja 1" << endl;
        }

        try
        {
            (*iter)->setY1(f1.Eval());
        }
        catch(Parser::exception_type &e)
        {
            qDebug() << "Wywolanie funkcji f1" << endl;
            qDebug() <<  QString().fromStdString( e.GetMsg()) << endl;
        }

        try
        {
            (*iter)->setY2(f2.Eval());
        }
        catch(Parser::exception_type &e)
        {
            qDebug() << "Wywolanie funkcji f2" << endl;
            qDebug() <<  QString().fromStdString( e.GetMsg()) << endl;
        }
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


string Nsga2::toStringF1(int f)
{

    list<Individual *> wypis;
    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        if((*p)->rank == 0)
        {
            wypis.push_back(*p);
        }
    }

    if(f == 0)
    {
        wypis.sort(Comp1<Individual>);
    }
    else if(f == 1)
    {
        wypis.sort(Comp2<Individual>);
    }

    stringstream stream;
    int i = 1;
    for(list<Individual *>::iterator p = wypis.begin(); p != wypis.end(); p++)
    {
        if((*p)->rank == 0)
        {
            stream << i << ". " << (*p)->toStringX()<< (*p)->toStringY() << " d: " << (*p)->getD() << " rank: " << (*p)->getRank() << endl;
            i++;
        }
    }

    return stream.str();
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

    for(unsigned int i = 0; i < F.size()-1;i++)
    {

        for(list<Individual*>::iterator I = F[i]->begin(); I != F[i]->end();I++)
        {
            (*I)->d = 0;
        }

        for(int m = 1;m <= 2; m++)
        {
            if(m == 1)
            {
                F[i]->sort( Comp1<Individual>);

                //min = F[i]->back()->getY1();
                //max = F[i]->front()->getY1();

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

                //min = F[i]->back()->getY2();
                //max = F[i]->front()->getY2();

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

        }
    }
}

template <typename T>
bool crowded_comparison_operator(const T * const & p, const T * const & q)
{
    if( p->getRank() < q->getRank()) return true;
    else if(p->getRank() == q->getRank())
    {
        if(p->getD() > q->getD()) return true;
        else return false;
    }
    else if( p->getRank() > q->getRank()) return false;
}

void Nsga2::BinaryTournamentSelection()
{
    int i = 0;
    int j = 1;

    std::random_device generator;
    std::uniform_real_distribution<double> udistribution(0,1); //generowanie liczb p-losowych z zakresu 0.0 - 1.0
    while(Q.size() < N)
    {


        list<Individual*>::iterator p1 = next(P.begin(),i);
        list<Individual*>::iterator q1 = next(P.begin(),j);

//      Individual *p1 = ReturnBeter(); //next(P.begin(),i);
//      Individual *q1 = ReturnBeter(); //next(P.begin(),j);
        int alfa = udistribution(generator);
        if(alfa < corrosoverToMutation)
        {
            Q.push_back(Individual::crossover(*p1,*q1,mu));
            Q.push_back(Individual::crossover(*q1,*p1,mu));
            qDebug() << "Crossover" << endl;
        }
        else
        {
            Q.push_back(Individual::mutation(*p1,mum,min,max));
            Q.push_back(Individual::mutation(*q1,mum,min,max));
            qDebug() << "Mutation" << endl;
        }
        i+=2;
        j+=2;

    }
    //qDebug() << "ffffffffffff" << endl;

    for(list<Individual *>::iterator p = P.begin(); p != P.end(); p++)
    {
        (*p)->setGeneticZero();
    }

    //qDebug() << "zzzzzzzzzzzzz" << endl;
}


Individual* Nsga2::ReturnBeter()
{
    k = 4;
    list<Individual*> zbior;
    std::random_device generator;
    std::uniform_int_distribution<int> udistribution(0,N-1); //generowanie liczb p-losowych z zakresu 0.0 - 1.0
    list<Individual*>::iterator iter;
    int s = 0;
    while(zbior.size() < k)
    {
        s = udistribution(generator);
        iter =  next(P.begin(),s);
        if(!((*iter)->getGenetic()))
        {
            zbior.push_back(*iter);
            (*iter)->setGenetic();
        }
    }
    zbior.sort(crowded_comparison_operator<Individual>);

    Individual *w = zbior.front();
    zbior.clear();
    //qDebug() << "kkkkk"<< endl;
    return w;
}




void Nsga2::MainLoop()
{
    try
    {
        P.sort(crowded_comparison_operator<Individual>);

        BinaryTournamentSelection();
    }
    catch (int i)
    {
        qDebug() << "MainLoop: BinaryTournamentSelection" << endl;

    }
    P.splice(P.begin(),Q);
    Q.clear();
    setZero();
    evaluation();
    fast_non_dominated_sort();
    crowding_distance_assigment();


    try
    {
        P.sort(crowded_comparison_operator<Individual>);
    }
    catch (int i)
    {
        qDebug() << "MainLoop: Sortowanie" << endl;

    }

    while(P.size() > N )
    {

        if( P.back() != NULL) delete P.back();
        P.pop_back();
    }
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

}



string Nsga2::toStringMinMax() const
{
    stringstream stream;
    return stream.str();
}

bool Nsga2::Pareto()
{
    for(list<Individual*>::iterator iter = P.begin(); iter != P.end(); iter++)
    {
        if( (*iter)->rank != 0)
        {
            return false;
        }
    }
    return true;
}

void Nsga2::exe1()
{

}

void Nsga2::exe2()
{

}


