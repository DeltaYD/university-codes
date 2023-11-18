#include <stdio.h>
#include <stdlib.h>

typedef struct data{
    int d;
    int m;
    int a;
} Data;

long mergeSort(Data *A, int p, int r);
long intercala(Data *A, int p, int q, int r);
int compare(Data A, Data B);

int main(void){
    int n;
    Data *datas;
    scanf("%d", &n);
    datas = (Data*)malloc(sizeof(Data)*n);

    for(int i=0; i<n; i++){
        //datas[i].a = i;
        scanf("%d", &datas[i].d);
        scanf("%d", &datas[i].m);
        scanf("%d", &datas[i].a);
    }

    long total = mergeSort(datas, 0, n - 1);

    printf("%ld", total);

    //free(datas);

    return 0;
}

long mergeSort(Data *A, int p, int r){
    int q;
    long total = 0;

    if(p >= r) return 0;

    q = p + (r-p)/2;
    total += mergeSort(A, p, q);
    total += mergeSort(A, q+1, r);
    total += intercala(A, p, q, r);

    return total;
}

long intercala(Data *A, int p, int q, int r){
    Data *B = (Data*)malloc(sizeof(Data) * ((r - p)+1));
    int i = p, j = q+1, k = 0;
    long total = 0;

    while(i <= q && j <= r){
        if(compare(A[i], A[j]) <= 0){
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
            total += q - i + 1;
        }
        k++;
    }

    while(i <= q){
        B[k] = A[i];
        i++;
        k++;
    }

    while(j <= r){
        B[k] = A[j];
        j++;
        k++;
    }

    for(int l = 0; l <= r - p; l++){
        A[l + p] = B[l];
    }
    //free(B);

    return total;
}

// compares A to B
// -1 if less, 0 if equal, 1 if more
int compare(Data A, Data B){
    if(A.a < B.a){
        return -1;
    } else if(A.a > B.a){
        return 1;
    }

    if(A.m < B.m){
        return -1;
    } else if(A.m > B.m){
        return 1;
    }

    if(A.d < B.d){
        return -1;
    } else if(A.d > B.d){
        return 1;
    }
    return 0;
}