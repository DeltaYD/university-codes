#include <stdio.h>
#include <stdlib.h>

#define RIGHT 1
#define LEFT 2

int main(void){
    int n = 0, q = 0, b = 0, res = 0;
    int* L;

    //n de inteiros na lista
    scanf("%d", &n);

    //declaracao da lista + obtencao dos valores
    L = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &L[i]);
    }

    //os dois funcionam
    heapSort(n, L);
    //mergeSort(L, 0, n-1);
    //printList(L, n);

    //n de consultas a serem feitas
    scanf("%d", &q);

    //n linhas, recebe um inteiro a ser buscado em tal lista
    for(int i = 0; i < q; i++){
        scanf("%d", &b);

        //res = BuscaSequencial(L, n, b);
        res = BuscaBinaria(L, 0, n-1, b);

        if(res == 1){
            printf("Presente\n");
        } else {
            printf("Ausente\n");
        }
    }

    free(L);
    return 0;
}

int BuscaBinaria(int* L, int start, int end, int b){
    int res = 0;
    int i = (start + end) / 2;

    if(L[i] == b) {
        return 1;
    }

    if(start >= end) {
        return 0;
    } else if(L[i] < b) {
        res = BuscaBinaria(L, i+1, end, b);
    } else if(L[i] > b) {
        res = BuscaBinaria(L, start, i-1, b);
    }

    return res;
}

int BuscaSequencial(int* L, int n, int b){

    for(int j = 0; j < n; j++){
        if(L[j] == b) return 1;
    }

    return 0;
}

void mergeSort(int *L, int p, int r){
    int q;

    if(p >= r) return 0;

    q = p + (r-p)/2;
    mergeSort(L, p, q);
    mergeSort(L, q+1, r);
    intercala(L, p, q, r);
}

void intercala(int *L, int p, int q, int r){
    int *B = (int*)malloc(sizeof(int) * ((r - p)+1));
    int i = p, j = q+1, k = 0;

    while(i <= q && j <= r){
        if(L[i] <= L[j]){
            B[k] = L[i];
            i++;
        } else {
            B[k] = L[j];
            j++;
        }
        k++;
    }

    while(i <= q){
        B[k] = L[i];
        i++;
        k++;
    }

    while(j <= r){
        B[k] = L[j];
        j++;
        k++;
    }

    for(int l = 0; l <= r - p; l++){
        L[l + p] = B[l];
    }
    //free(B);

    return;
}

void printList(int* L, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", L[i]);
    }
    printf("\n");
    return;
}

void heapSort(int n, int *a){
    int aux, end = n-1;

    heapify(n, a);

    while(end != 0) {
        //switch values from the start to last, update the end, then fix the heap property
        if(a[0] > a[end]) {
            switching(a, end, 0);
        }
        end--;

        siftDown(a, 0, end);
        //repeat until the end is zero
    }
    switching(a, end, 0);
}

void heapify(int n, int *a){
    int indexTop = 0;

    for(int i = 1; i < n; i++){
        indexTop = floor((i-1)/2);
        //if a[indexTop] is less than a[i], siftUp()
        if(a[indexTop] < a[i]){
            siftUp(a, indexTop, i);
        }
    }

}

void siftDown(int *a, int index, int end){
    //get left and right indexes down
    int indexl = (index*2) + 1, indexr = (index*2) + 2;
    int checked = 0;
    int child1, child2, root;
    root = a[index];

    int doesLeftExist = 0;
    int doesRightExist = 0;
    int isRightSmaller = 0;
    int isLeftSmaller = 0;

    //check if exists in these conditions
    if(indexr <= end) {
        doesRightExist = 1;
    }
    if(indexl <= end) {
        doesLeftExist = 1;
    }

    if(doesRightExist == 1){
        child2 = a[indexr];
        // se o no da direita for menor que a raiz
        if(child2 <= root) {
            isRightSmaller = 1;
        }
    }
    if(doesLeftExist == 1) {
        child1 = a[indexl];
        // se o no da esquerda for menor que a raiz
        if(child1 <= root){
            isLeftSmaller = 1;
        }
    }
    if(doesRightExist != 1 && isLeftSmaller == 1){
        //se o lado direito nao existe e o esquerdo e menor, nao calcular
        return;
    }
    if(isRightSmaller && isLeftSmaller){
        // se os dois lados folha forem menores que a raiz, retornar (nao calcular / nao faz sentido calcular)
        return;
    }
    if(doesLeftExist == 0 && doesRightExist == 0){
        return;
    }

    switch(biggestSide(child1, child2)){
    case LEFT:
        switching(a, indexl, index);
        siftDown(a, indexl, end);
        break;

    case RIGHT:
        if(doesRightExist == 1){
            switching(a, indexr, index);
            siftDown(a, indexr, end);
        }
        break;
    }

    //by the end of this, the first element is already the biggest, and heap order is restored.
    return;
}

void switching(int *a, int indexX, int indexY){
    int aux = a[indexX];
    a[indexX] = a[indexY];
    a[indexY] = aux;

    return;
}

void siftUp(int *a, int indexTop, int i){
    switching(a, indexTop, i);

    if(indexTop == 0){
        return;
    }

    i = indexTop;
    indexTop = floor((i-1)/2);
    if(a[indexTop] < a[i]){
        siftUp(a, indexTop, i);
    }

    return;
}

int biggestSide(int left, int right){
    if(left >= right) return LEFT;
    if(right > left) return RIGHT;
}


