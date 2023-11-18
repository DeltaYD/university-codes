#include <stdio.h>
#include <string.h>

typedef struct registry{
    char name[20];
    int age;
    int id;
    float height;
} regType;

int main(void) {
    int n = 0, charcount = 0, c = 0;
    regType *r;

    scanf("%d", &n);
    r = malloc(sizeof(regType)*n);

    for(int i=0; i<n; i++){
        r[i].id = i;
        scanf("%s %d %f", &r[i].name, &r[i].age, &r[i].height);
    }

    quickSort(r, 0, n-1);

    for(int i=0; i<n; i++){
        printf("%d;", r[i].id);
    }

    return 0;
}


int compareEntries(regType r1, regType r2){
    if(strcmp(r1.name, r2.name) < 0){
        return -1;

    } else if(strcmp(r1.name, r2.name) == 0){
        //then compare age

        if(r1.age < r2.age){
            return -1;

        } else if(r1.age == r2.age){
            //then compare height

            if(r1.height < r2.height){
                return -1;

            } else if (r1.height == r2.height){
                return 0;

            }
        }

    }

    return 1;
}

void insertionSort(regType *r, int size){
    regType aux;
    int i = 1, j = 0;

    if(size != 0){
        while(i < size){
            j = i;
            while(j>0 && compareEntries(r[j], r[j-1]) < 0){
                printf("swapping %s and %s\n", r[j], r[j-1]);
                aux = r[j];
                r[j] = r[j-1];
                r[j-1] = aux;
                j -= 1;
            }
            i += 1;
        }
    }

    return;
}

void bubbleSort(regType *r, int size){
    int switched = 1;
    regType aux;

    do{
        switched = 0;
        for(int i = 0; i < size-1; i++){
            if(compareEntries(r[i], r[i+1]) > 0){
                aux = r[i];
                r[i] = r[i+1];
                r[i+1] = aux;
                switched = 1;
            }
        }
    } while (switched);
    return;
}

void shellSort(regType *r, int size){
    regType aux;
    int h = 1, i, j;

    while(h < size){
        h = 3*h+1;
    }

    while(h > 0){
        for(i = h; i < size; i++){
            aux = r[i];
            j = i;
            while(j > h-1 && compareEntries(aux, r[j - h]) <= 0) {
                r[j] = r[j-h];
                j = j-h;
            }
            r[j] = aux;
        }
        h = h/3;
    }

    return;
}

void quickSort(regType *r, int lo, int hi){
    int p = 0;

    if(lo >= hi || lo < 0){
        return;
    }

    p = quickSortPartition(r, lo, hi);

    quickSort(r, lo, p-1);
    quickSort(r, p+1, hi);

    return;
}

int quickSortPartition(regType *r, int lo, int hi){
    regType pivot = r[hi], aux;

    int i = lo - 1;

    for(int j = lo; j < hi; j++){
        if(compareEntries(r[j], pivot) <= 0){
            i = i + 1;
            aux = r[i];
            r[i] = r[j];
            r[j] = aux;
        }
    }

    i = i + 1;

    aux = r[i];
    r[i] = r[hi];
    r[hi] = aux;

    return i;
}

