#include "backpropagation.h"
#include "operators.h"
#include <stdio.h>
#include <cmath>

BackPropagation::BackPropagation()
{

}

int BackPropagation::Ls(vector<double> W, vector<Point> S)
{
    int ls = 0;
    for(int i=0; i<S.size(); i++)
    {
        if((W*S[i].X)*S[i].y <= 0){
            ls++;
        }
    }
    return ls;
}

vector<double> BackPropagation::training(vector<double> W, vector<Point> S)
{
    if(S.size()>0){
        int t=0;
        while(t<10*S.size() && Ls(W,S) != 0)
        {
            for(int i=0; i<S.size(); i++){
                W = W + 0.01*(sigmoid(W*S[i].X)-sigmoid(S[i].y))*S[i].X;
            }
            t++;
        }
    }
    else
        printf("There is no data for training?");
    return W;
}

double BackPropagation::sigmoid(double y)
{
    return 1/(1+exp(y));
}
