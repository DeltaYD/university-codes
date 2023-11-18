#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int M, N;
int *list1, *list2;

int Edit(){
    int MEMO[M+1][N+1];
    memset(MEMO, -1, sizeof(MEMO));

    for(int i = 0; i <= M; i++){
        for (int j = 0; j <= N; j++)
        {
            //  Se a list1 acabou, entao o que fazer?
            if(i == 0) {
                //  Inserir na list1 todos os caracteres REMANESCENTES
                MEMO[i][j] = j;
            }
            else if(j == 0) {
                MEMO[i][j] = i;
            }
            else if(list1[i-1] == list2[j-1]) {
                MEMO[i][j] = MEMO[i-1][j-1];
            }
            else{
                //  Considerando que nao temos troca entre numeros, este else fica assim
                MEMO[i][j] = 1 + min(MEMO[i-1][j],    //  remocao
                                     MEMO[i][j-1]    //  insercao
                                     );
            }
        }
    }

    return MEMO[M][N];
}

int main(int argc, char const *argv[]){
    int T, B;

    //  Recebimento dos dados iniciais
    scanf("%d",  &T);
    for(int count = 0; count < T; count++){
        scanf("%d", &B);
        list1 = (int*)malloc(sizeof(int) * B);
        list2 = (int*)malloc(sizeof(int) * B);
        M = B;
        N = B;

        for(int kount = 0; kount < B; kount++){
            scanf("%d", &list1[kount]);
        }
        for(int kount = 0; kount < B; kount++){
            scanf("%d", &list2[kount]);
        }

        //  Imprime resultado da PD
        printf("Case %d: %d\n", count+1, Edit());

        free(list1);
        free(list2);
    }

    return 0;
}