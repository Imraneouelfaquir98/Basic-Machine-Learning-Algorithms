#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>

using namespace std;



double         operator*(const vector<double> & U, const vector<double> & V);
vector<double> operator*(const double &alpha     , const vector<double> & U);
vector<double> operator*(const vector<double> & U, const double         & alpha);
vector<double> operator/(const vector<double> & U, const double         & m);
vector<double> operator-(const vector<double> & U, const vector<double> & V);
vector<double> operator+(const vector<double> & U, const vector<double> & V);

#endif // OPERATORS_H
