#ifndef ADALINE_H
#define ADALINE_H

#include <vector>
#include "point.h"

using namespace std;

class Adaline
{
public:

    Adaline();

    int            Ls       (vector<double> W, vector<Point> S);
    vector<double> training (vector<double> W, vector<Point> S);
};

#endif // ADALINE_H
