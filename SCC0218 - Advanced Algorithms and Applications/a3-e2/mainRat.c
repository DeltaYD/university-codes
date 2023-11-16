#include <stdio.h>
#include <stdlib.h>
#include "Rat.h"

int main(void){
    int N;

    //  Obtain maze size
    scanf("%d", &N);

    squareMaze(N);

    return 0;
}