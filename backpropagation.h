#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include <vector>
#include "point.h"

using namespace std;

class BackPropagation
{
public:
    BackPropagation();

    int            Ls       (vector<double> W, vector<Point> S);
    vector<double> training (vector<double> W, vector<Point> S);
    double         sigmoid  (double y);
};

#endif // BACKPROPAGATION_H
