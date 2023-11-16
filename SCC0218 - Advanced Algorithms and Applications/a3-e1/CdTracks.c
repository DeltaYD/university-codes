#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CdTracks.h"

//  Global Variables
int gN, gT;

//  Algorithm for the Backtracking
void backtrackingSub(int N, int T){
    int Tracks[T], best[2], *aux, *output;
    int prog = 0, sum = 0, big = 0;

    //  Variable declaration
    output = (int*)calloc(T, sizeof(int));
    aux = (int*)calloc(T, sizeof(int));
    gN = N;
    gT = T;
    memset(best, 0, sizeof(best));

    //  Obtain track sizes
    for(int count = 0; count < T; count++){
        scanf("%d", &Tracks[count]);
    }

    //  Start algorithm
    recBack(prog, sum, best, big, Tracks, aux, output);

    //  Print results
    for(int count = 0; count < best[1]; count++){
        printf("%d ", output[count]);
    }
    printf("sum:%d\n", best[0]);

    //  Free allocated memory (probably wasnt needed to be allocated, but I struggled a bit with this code)
    free(output);
    free(aux);

    return;
}

//  Main portion of the recursive algorithm
void recBack(int prog, int sum, int *best, int big, int *trackList, int *auxVec, int *trueVec){

    //  Part that calls itself
    for(int count = prog; count < gT; count++){
        //  If the sum of values equals to or is less than the maximum possible amount, then go in
        if(sum + trackList[count] <= gN){
            //  Write down path at point 'big'
            auxVec[big] = trackList[count];
            //  Calls itself
            recBack(count + 1, sum + trackList[count], best, big + 1, trackList, auxVec, trueVec);
        }
    }

    //  If the sum of elements surpasses previous attempts, update with the new and better solution
    if(sum > best[0]){
        //  Update best[]
        best[0] = sum;
        best[1] = big;

        //  Update trueVec. trueVec is the solution to the problem
        for(int count = 0; count < gT; count++){
            trueVec[count] = auxVec[count];
        }

    //  However if it isn't solely big and actually the same result, check which one fits the most and choose it
    } else if(sum == best[0] && best[1] < big){
        //  Update best[]
        best[0] = sum;
        best[1] = big;

        //  Update trueVec
        for(int count = 0; count < gT; count++){
            trueVec[count] = auxVec[count];
        }
    }

    //  End of this portion of the recursion
    return;
}