#include "pocketla.h"
#include "operators.h"
#include <stdio.h>

PocketLA::PocketLA()
{

}

int PocketLA::signe(double value){
    return (value>0)? 1:-1;
}

int PocketLA::Ls(vector<double> W, vector<Point> S)
{
    int ls = 0;
    for(int i=0; i<S.size(); i++)
    {
        if(signe(W*S[i].X)*S[i].y < 0){
            ls++;
        }
    }
    return ls;
}

vector<double> PocketLA::training(vector<double> W, vector<Point> S){
    if(S.size()>0){
        vector<double> BestW = W;
        int t=0;
        FILE *file;
        file = fopen("PocketLS.txt","w");
        fprintf(file,"\n\nLs(W)=[");
        fprintf(file,"%d,",Ls(BestW,S));
        while(t<100){ //Ls(BestW,S) != 0 &&
            for(int i=0; i<S.size(); i++){
                if(signe(W*S[i].X)*S[i].y < 0){
                    W = W + S[i].y*S[i].X;
                    if(Ls(BestW,S) > Ls(W,S)){
                        BestW = W;
                    }
                }
            }
            fprintf(file,"%d,",Ls(BestW,S));
            t++;
        }
        fprintf(file,"]\n");
        fclose(file);
        return BestW;
    }
    else{
        printf("There is no data for training?");
        return W;
    }
}
