#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <list>
#include <vector>
#include <random>
#include <sstream>
#include <math.h>

using namespace std;

class Individual
{

    // argumenty funkcji celu
    vector<double> x;

    // wartości funkcji celu
    double y1;
    double y2;

public:
        int v1;
        int v2;
        int v_max;

    Individual(int zv1, int zv2);

    // zbior elementow ktore sa zdominowane przez ten element
    vector<Individual *> S;

    // ilość elementów które dominują nad tym elementem
    int n;

    // przypisany front
    int rank;

    // odległość
    double d;

    // use;
    int genetic;

    int getGenetic();
    int setGenetic();
    int setGeneticZero();

    static bool compare1(const Individual *a, const Individual *b);

    static bool compare2(const Individual *a, const Individual *b);

    void setX(vector<double> vx);
    void setY1(double y);
    void setY2(double y);

    void setRandX(vector<double> min, vector<double> max);

    void setY1andY2(double y1, double y2);

    double getY1() const;
    double getY2() const;
    vector<double> getX() const;
    int getRank() const;
    double getD() const ;


    static Individual* crossover(Individual *p1, Individual *p2,double ota_c);
    static Individual* mutation(Individual *p,double ota_m, vector<double> min, vector<double> max);

    static bool crowded_comparison_operator(Individual *p, Individual *q);
    string toStringX() const;
    string toStringY() const;
};

#endif // INDIVIDUAL_H
