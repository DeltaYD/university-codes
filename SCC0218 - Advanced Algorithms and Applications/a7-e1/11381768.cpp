#include <iostream>
#include <cstdio>

using namespace std;

#define INF 999999999

int V, Q;

int coinDP(int MEMO[], int coin[]){
    for(int count = 1; count < (V + 1); count++){
        for(int kount = 0; kount < Q; kount++){
            if(count - coin[kount] >= 0){
				MEMO[count] = min(MEMO[count], (MEMO[count - coin[kount]] + 1));
			}
        }
    }

    return MEMO[V];
}

int main(void){
    int N, R;

    //  Nro de casos de teste
    scanf("%d", &N);
    for(int count = 0; count < N; count++){
        //  Valor maximo total e Nro de moedas diferentes
        scanf("%d %d", &V, &Q);

        int coin[Q], MEMO[V + 1];

        for(int kount = 0; kount < Q; kount++){
            //  Valor da moeda e colocado
            scanf("%d", &coin[kount]);
        }

        for(int kount = 0; kount < (V + 1); kount++){
            MEMO[kount] = INF;
        }
        MEMO[0] = 0;

        //  Rodar PD aqui
        R = coinDP(MEMO, coin);
        if(R != INF){
            printf("%d\n", R);
        } else{
            printf("sem solucao\n");
        }
    }

    return 0;
}