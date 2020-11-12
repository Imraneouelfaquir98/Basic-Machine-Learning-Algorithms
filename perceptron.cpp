#include "perceptron.h"
#include "operators.h"
#include <stdio.h>

Perceptron::Perceptron()
{

}

int signe(double value){
    return (value>0)? 1:-1;
}

vector<double> Perceptron::training(vector<double> W, vector<Point> S){
    if(S.size()>0){
        int t=0;
        FILE *file;
        file = fopen("Perceptron.txt","w");
        fprintf(file,"\n\nLs(W)=[");
        fprintf(file,"%d,",Ls(W,S));
        while(Ls(W,S) != 0 && t<10*S.size()){
            for(int i=0; i<S.size(); i++){
                if(signe(W*S[i].X)*S[i].y < 0 ){;
                    W = W + S[i].y*S[i].X;
                }
            }
            t++;
        }
        fprintf(file,"%d,",Ls(W,S));
        fprintf(file,"]\n");
        fclose(file);
    }
    else
        printf("There is no data for training?");
    return W;
}

int Perceptron::Ls(vector<double> W, vector<Point> S){
    int ls = 0;
    for(int i=0; i<S.size(); i++)
    {
        if(signe(W*S[i].X)*S[i].y < 0){
            ls++;
        }
    }
    return ls;
}


