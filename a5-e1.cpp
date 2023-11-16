#include <stdio.h>
#include <iostream>

using namespace std;

int *ms, *aux;

void createArray(int C);
void freeArray();
int mergeSortRec(int start, int end);
int mergeSort(int start, int mid, int end);

void createArray(int C){
    ms = (int*)malloc(sizeof(int) * (C+1));
    aux = (int*)malloc(sizeof(int) * (C+1));
    return;
}

void freeArray(){
    free(ms);
    ms = NULL;
    free(aux);
    aux = NULL;
    return;
}

int mergeSortRec(int start, int end){
    int ret = 0;

    if(start < end){
        int mid = (start + end) / 2;
        ret += mergeSortRec(start, mid);
        ret += mergeSortRec(mid + 1, end);
        ret += mergeSort(start, mid, end);
    }

    return ret;
}

int mergeSort(int start, int mid, int end){
    int i, j, k, inversoes = 0;
    i = start;
    j = mid + 1;
    k = start;

    while(i <= mid && j <= end){
        if(aux[i] < aux[j]){
            ms[k] = aux[i];
            i++;
        } else{
            ms[k] = aux[j];
            j++;
            // ????????????????????
            inversoes += mid - i + 1;
        }
        k++;
    }

    while(i <= mid){
        ms[k] = aux[i];
        i++;
        k++;
    }

    while(j <= end){
        ms[k] = aux[j];
        j++;
        k++;
    }

    for(int p = start; p <= end; p++){
        aux[p] = ms[p];
    }

    return inversoes;
}

int main(void){
    int N, C;

    //  Obter n de casos de teste
    scanf("%d", &N);
    for(int count = 0; count < N; count++){

        //  Obter n de inteiros
        scanf("%d", &C);
        createArray(C);

        for(int kount = 1; kount <= C; kount++){
            scanf("%d", &aux[kount]);
        }

        printf("%d\n", mergeSortRec(1, C));


        freeArray();
    }

    return 0;
}