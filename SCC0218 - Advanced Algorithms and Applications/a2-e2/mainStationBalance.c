#include <stdio.h>
#include <stdlib.h>
#include "StationBalance.h"

#define RUN 4

int main(void){
    int C, S;

    //  Main loop for definable (in code) amount of runs 'RUN'
    for(int count = 0; count < RUN; count++){
        scanf("%d %d", &C, &S);
        balancing(C, S, count);
    }

    return 0;
}