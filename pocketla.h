#ifndef POCKETLA_H
#define POCKETLA_H

#include <vector>
#include "point.h"

using namespace std;

class PocketLA
{
public:
    PocketLA();

    int            signe    (double value);
    int            Ls       (vector<double> W, vector<Point> S);
    vector<double> training (vector<double> W, vector<Point> S);
};

#endif // POCKETLA_H
