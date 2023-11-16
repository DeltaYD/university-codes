#include <stdio.h>
#include <stdlib.h>
#include "CoinAlg.h"


//  Creation and destruction of arrays
int *createArray(int size){
    int *a = (int*)malloc(sizeof(int) * size);
    return a;
}
void deleteArray(int *a){
    free(a);
    return;
}

//  Main algorithm (Coin collector)
int maxNoCoins(int *coinsBag, int size){
    int qt = 2;
    long int total = coinsBag[0];

    //  Special case where tere are 2 or less types of coin
    if(size <= 2){
        return size;
    }

    //  Main loop, in an attempt for each coin type from smallest to gratest
    for(int count = 1; count < size; count++){
        //  If the total is smaller than current interaction and wont affect next interaction (while avoiding to invade memory)
        if((total < coinsBag[count]) && ( ((total + coinsBag[count]) < coinsBag[count + 1]) && !(count + 1 == size))){
            //  Count this coin in
            qt++;

            //  Update next
            total += coinsBag[count];
        }
    }

    //  End and return sought value
    return qt;
}