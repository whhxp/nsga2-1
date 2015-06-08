#ifndef NSGA2_H
#define NSGA2_H

#include <individual.h>
#include <string>
#include <iterator>
#include <qdebug.h>
#include <time.h>
#include <stdlib.h>
#include <float.h>


#include <vector>

#include <muParser.h>

using namespace mu;

using namespace std;

class Nsga2
{
    unsigned int N;
    int M;
    int T;

    double mum;
    double mu;
    double corrosover;
    double mutation;
    int offspring;
    int k = 4;


    list<Individual *> P;
    list<Individual *> Q;

    string str1;
    string str2;

    int v1;
    int v2;
    int v_max;

    double a;
    double b;

    vector<double> min;
    vector<double> max;


public:

    Individual *ReturnBeter();
    void crowding_distance_assigment();
    void fast_non_dominated_sort();
    void init_population();
    bool dominates(Individual *p, Individual *q);
    void BinaryTournamentSelection();
    void MainLoop();
    void setZero();

    Nsga2(unsigned int n,int Offspring, double Corrosover, double Mutation,  double MU, double MUM, string s1, int zv1, string s2, int zv2, vector<double> Min, vector<double> Max);
    void evaluation();
    void exe1();
    void exe2();
    vector<list<Individual *>*> F;

    vector<double> returnY1();
    vector<double> returnY2();

    vector<double> returnY1F0();
    vector<double> returnY2F0();
    bool Pareto();

    string toStringF1(int f);

    string toStringMinMax() const;

};

#endif // NSGA2_H
