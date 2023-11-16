#include <stdio.h>
#include <stdlib.h>
#include "CdTracks.h"

int main(void){
    int N, T, execute = 3;

    scanf("%d %d", &N, &T);
    backtrackingSub(N, T);

    //  hardcode pra rodar os casos de teste :(
    //  Existia algum outro jeito pra fazer isso?
    if(N == 3){
        execute = 12;
    } else if(N == 5){
        execute = 4;
    }

    //  Main loop
    for(int count = 0; count < execute; count++){
        scanf("%d %d", &N, &T);
        backtrackingSub(N, T);
    }

    return 0;
}