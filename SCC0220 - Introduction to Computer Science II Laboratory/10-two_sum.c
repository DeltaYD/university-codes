#include <stdio.h>
#include <stdlib.h>
#define RIGHT 1
#define LEFT 2

int main(void){
    int n = 0, *lista, q = 0, k = 0, aux = 0;

    scanf("%d", &n);
    lista = (int*)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &lista[i]);
    }

    //hashBusca(lista, n);

    heapSort(n, lista);
    aOutraBusca(lista, n);

    free(lista);

    return 0;
}

int hashLocal(int *hashList, int tam, int target){
    int local = target % tam;

    while(hashList[local] != -1){
        local++;
        if(local == tam){
            local = 0;
        }
    }

    return local;
}

int hashFindLocal(int *hashList, int tam, int target){
    int local = target % tam;
    int start = local;

    while(hashList[local] != target){
        local++;
        if(local == tam){
            local = 0;
        }
        if(local == start){
            return -1;
        }
    }

    return local;
}

void hashBusca(int* lista, int n){
    int q, target, aux = 0;
    int *hashList;
    int complement, found = 0;

    hashList = (int*)malloc(n * sizeof(int));
    memset(hashList, -1, n * sizeof(int));

    for(int i=0; i<n; i++){
        aux = hashLocal(hashList, n, lista[i]);
        hashList[aux] = lista[i];
    }

    scanf("%d", &q);

    for(int i=0; i<q; i++){
        scanf("%d", &target);

        found = 0;
        for(int j=0; j<n; j++){
            complement = target - lista[j];
            if(complement >= 0 && hashFindLocal(hashList, n, complement) != -1){
                printf("S\n");
                found = 1;
                break;
            }
        }
        if(found == 0){
            printf("N\n");
        }
    }

    free(hashList);
    return;
}




void aOutraBusca(int *lista, int n){
    int q, k, complemento, res;

    scanf("%d", &q);

    for(int i = 0; i < q; i++){
        scanf("%d", &k);
        res = 0;
        for(int j=0; j<n && res == 0; j++){
            complemento = k - lista[j];
            //res = BuscaSequencial(L, n, b);
            res += BuscaBinaria(lista, 0, n-1, complemento);
        }

        if(res >= 1){
            printf("S\n");
        } else {
            printf("N\n");
        }
    }

    return;
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



