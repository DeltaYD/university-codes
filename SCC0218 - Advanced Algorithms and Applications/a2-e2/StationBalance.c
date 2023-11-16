#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "StationBalance.h"

#define INF 999999999

void balancing(int C, int S, int it){
    int chamber[C][2];
    int sum[C], spec[S], full[C];
    int smallest = INF, locale = 0, aux = 0, what;
    float med = 0;
    double IMBALANCE = 0;

    //  Sums starting at zero, also chambers
    for(int count = 0; count < C; count++){
        sum[count] = 0;
        full[count] = 0;
        for(int kount = 0; kount < 2; kount++){
            chamber[count][kount] = 0;
        }
    }

    //  S weight input
    for(int count = 0; count < S; count++){
        scanf("%d", &spec[count]);
    }

    //  Sort weights
    quicksort(spec, 0, S);

    //  Chamber distribution for each specimen starting from heaviest
    for(int kount = S - 1; kount >= 0; kount--){
        //  Start @Chamber count
        for(int kaunt = 0; kaunt < C; kaunt++){
            //  Find lowest scored chamber
            if(sum[kaunt] < smallest && !full[kaunt]){
                smallest = sum[kaunt];
                locale = kaunt;
            }
            //  If already empty
            if(smallest == 0){
                locale = kaunt;
                break;
            }
        }

        //  Look for space for new specimen in this slot and encage
        while(chamber[locale][aux] != 0){
            aux++;
        }
        //  Removing 'what' variable breaks the code. I don't know why
        what = kount;
        chamber[locale][aux] = spec[kount];
        kount = what;

        //  Determine a full container
        if(aux == 1){
            full[locale] = 1;
        }

        //  Update total weight of a cage
        sum[locale] += spec[kount];

        //  Reload auxiliary variables
        smallest = INF;
        aux = 0;
    }

    //  Prints chambers
    printf("Set #%d\n", it+1);
    for(int count = 0; count < C; count++){
        printf(" %d:", count);
        for(int kount = 0; kount < 2; kount++){
            if(chamber[count][kount] != 0){
                printf(" %d", chamber[count][kount]);
            }
        }
        printf("\n");
    }

    //  Calculate average
    for(int count = 0; count < C; count++){
        med += sum[count];
    }
    med = med/C;

    //  Calculate   I M B A L A N C E
    for(int count = 0; count < C; count++){
        IMBALANCE += fabs(sum[count] - med);
    }

    //  Feedback
    printf("IMBALANCE = %.5f\n\n", IMBALANCE);

    return;
}

//  Quicksort made using Wikipedia reference: https://pt.wikipedia.org/wiki/Quicksort
void quicksort(int *sort, int start, int end){
    int i = start, j = end - 1, pivot = sort[(start + end) / 2], aux;

    while(i <= j){
        while(sort[i] < pivot && i < end){
            i++;
        }
        while(sort[j] > pivot && j > start){
            j--;
        }

        if(i <= j){
            aux = sort[i];
            sort[i] = sort[j];
            sort[j] = aux;
            i++;
            j--;
        }
    }
    if(j > start){
        quicksort(sort, start, j + 1);
    }
    if(i < end){
        quicksort(sort, i, end);
    }

    return;
}