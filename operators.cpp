#include "operators.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

double operator*(const vector<double>& U, const vector<double>& V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            double produit = 0;
            for(int i = 0 ; i < U.size() ; i++)
                produit += U[i] * V[i];
            return produit;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return 0;
    }
}

vector<double> operator*(const double &alpha, const vector<double>& U){
    vector<double> W(U.size() , 0);
    for(int i = 0 ; i < U.size() ; i++)
        W[i] = alpha*U[i];
    return W;
}


vector<double> operator*(const vector<double>& U, const double &alpha){
    vector<double> W(U.size() , 0);
    for(int i = 0 ; i < U.size() ; i++)
                W[i] = alpha*U[i];
    return W;
}



vector<double> operator/(const vector<double> & U, const double &m){
    try{
        if( m == 0){
            throw string("ERREUR : can not devise with zero !");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++)
                        W[i] = U[i]/m;
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}


vector<double> operator-(const vector<double> & U, const vector<double> & V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !1");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++){
                    W[i] = U[i] - V[i];
            }
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}

vector<double> operator+(const vector<double> & U, const vector<double> & V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !2");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++){
                    W[i] = U[i] + V[i];
            }
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}
