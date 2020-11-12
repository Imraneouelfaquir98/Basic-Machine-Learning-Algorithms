#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include "point.h"

using namespace std;

class Perceptron
{
public:

    Perceptron();

    int            Ls       (vector<double> W, vector<Point> S);
    vector<double> training (vector<double> W, vector<Point> S);
};

#endif // PERCEPTRON_H
