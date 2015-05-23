#ifndef NSGA2_H
#define NSGA2_H

#include <individual.h>
#include <string>
#include <iterator>

#include <exprtk.hpp>

using namespace std;

class Nsga2
{
    int N;
    int M;
    int t;
    int T;

    list<Individual *> P;
    list<Individual *> Q;

    /*
    void make_new_pop();
    void main_loop();
    void mutation();
    void crossover();
    void evaluation();
    */

public:
    void crowding_distance_assigment();
    void fast_non_dominated_sort();
    void init_population(double min, double max);
    bool dominates(Individual *p, Individual *q);
    Nsga2(int n, int t);
    void evaluation();
    vector<list<Individual *>*> F;
    void show();

    vector<double> returnY1();
    vector<double> returnY2();

    vector<double> returnY1F0();
    vector<double> returnY2F0();

//    vector<double> returnX1();
//    vector<double> returnX2();
};

#endif // NSGA2_H
