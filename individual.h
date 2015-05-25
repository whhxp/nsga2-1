#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <list>
#include <vector>
#include <random>

using namespace std;




class Individual
{

    // argumenty funkcji celu
    double x1;
    double x2;

    // wartości funkcji celu
    double y1;
    double y2;

public:
    Individual();

    // zbior elementow ktore sa zdominowane przez ten element
    vector<Individual *> S;

    // ilość elementów które dominują nad tym elementem
    int n;

    // przypisany front
    int rank;

    // odległość
    double d;


    static bool compare1(const Individual *a, const Individual *b);

    static bool compare2(const Individual *a, const Individual *b);

    void setX1(double x);
    void setX2(double x);
    void setY1(double y);
    void setY2(double y);

    void setRandX(double min, double max);

    void setX1andX2(double x1, double x2);
    void setY1andY2(double y1, double y2);

    double getY1() const;
    double getY2() const;
    double getX1() const;
    double getX2() const;
    int getRank() const;
    double getD() const;


    static Individual* crossover1(Individual *p1, Individual *p2);
    static Individual* mutation(Individual *p, double min, double max);
    static Individual* crossover2(Individual *p1, Individual *p2);

   static bool crowded_comparison_operator(Individual *p, Individual *q);
    void show() const;
};

#endif // INDIVIDUAL_H
