#include <stdio.h>
#include <stdlib.h>
#include "CoinAlg.h"

int main(void){
    int T, n;
    int *coin;

    //  Obtain T test cases
    scanf("%d", &T);

    //  Main loop for T test cases
    for(int count = 0; count < T; count++){

        //  Obtain number of types of coins
        scanf("%d", &n);
        coin = createArray(n);

        //  Obtain types of coins
        for(int kount = 0; kount < n; kount++){
            scanf("%d", &coin[kount]);
        }

        //  Call coin function and print out result
        printf("%d\n", maxNoCoins(coin, n));

        //  Undo bag
        deleteArray(coin);
    }

    //  End
    return 0;
}