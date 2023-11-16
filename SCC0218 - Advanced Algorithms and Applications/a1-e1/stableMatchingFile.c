//functions file
#include <stdio.h>
#include <stdlib.h>
#include "stableMatchingFile.h"

int **makePreferenceList(int nMatches){
    int **matrizPref;

    //  Matrix allocation
    matrizPref = (int**)malloc((nMatches+1) * sizeof(int*));
    for(int count = 0; count <= nMatches; count++){
        matrizPref[count] = (int*)calloc(nMatches+1, sizeof(int));
    }

    //  Value agregation
    for(int count = 1; count <= nMatches; count++){
        for(int kount = 0; kount <= nMatches; kount++){
            scanf("%d", &matrizPref[count][kount]);
        }
    }

    return matrizPref;
}

void destroyPref(int **target, int n){
    //  Destroy helper tool
    for(int count = 0; count <= n; count++){
        free(target[count]);
    }
    free(target);

    return;
}

//  Returns 1 if she will switch, else wont
int isPreference(int **matrizPref, int h, int m, int cand, int nMatches){
    //  Determine if proposal is better or not
    for(int count = 1; count <= nMatches; count++){
        if(matrizPref[m][count] == h){
            return 0;
        }
        if(matrizPref[m][count] == cand){
            return 1;
        }
    }
    
    return 2;
}

void matchingAlgorithm(int **mPref, int **fPref, int nMatches){
    //  Everyone's already been set as free
    int frPeople = nMatches;
    int m, f, dude;

    //  While there are unmatched people
    while(frPeople > 0){
        //  Find who's still lonely and sad
        for(dude = 1; dude <= nMatches; dude++){
            //  If we find someone lonely
            if(mPref[0][dude] == 0){
                //  We force them to find a soulmate yay
                break;
            }
        }
        //  If no one is lonely
        if(dude > nMatches){
            //  Then our job is done here
            return;
        }

        //  Now who are his preferences
        for(int count = 1; count <= nMatches; count++){
            //  We will go one by one and put her name on 'f'
            f = mPref[dude][count];

            //  Now if she's also lonely and sad
            if(fPref[0][f] == 0){
                //  Then just get together already
                fPref[0][f] = dude;
                mPref[0][dude] = f;
                frPeople--;
                break;

            //  Now if she isn't
            } else{
                //  It's not your choice anymore
                m = fPref[0][f];
                if(isPreference(fPref, m, f, dude, nMatches)){
                    //  Dump whoever was the other guy
                    mPref[0][m] = 0;

                    //  Now you're engaged, gg
                    fPref[0][f] = dude;
                    mPref[0][m] = f;

                    //  Since there was a switch, not a get-together, the number of lonely people remains
                    break;
                }
            }

        }
    }

    return;
}

void printMatches(int **mPref, int **fPref, int nMatches){
    int f;

    //  Print them out
    for(int count = 1; count <= nMatches; count++){
        f = mPref[0][count];
        printf("%d %d\n", count, f);
    }

    return;
}