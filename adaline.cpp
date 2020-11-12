#include "adaline.h"
#include "operators.h"
#include <stdio.h>
#include <math.h>

Adaline::Adaline()
{

}

vector<double> Adaline::training(vector<double> W, vector<Point> S){
    if(S.size()>0){
        int t=0;
        FILE *file;
        file = fopen("Adaline.txt","w");
        fprintf(file,"\n\nLs(W)=[");
        fprintf(file,"%d,",Ls(W,S));
        while(t<100){ // && Ls(W,S) != 0
            for(int i=0; i<S.size(); i++){
                W = W + 0.2*(S[i].y - W*S[i].X)*S[i].X;
                if(Ls(W,S) == 0)
                    break;
            }
            fprintf(file,"%d,",Ls(W,S));
            t++;
        }
        fprintf(file,"]\n");
        fclose(file);
    }
    else
        printf("There is no data for training?");

    return W;
}

int Adaline::Ls(vector<double> W, vector<Point> S)
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
