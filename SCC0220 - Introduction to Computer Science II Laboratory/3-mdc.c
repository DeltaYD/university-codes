#include <stdio.h>
#include <time.h>

unsigned int MDCiterativa(unsigned int m, unsigned int n);
unsigned int MDCrecursiva(unsigned int m, unsigned int n);

int main(void){
    unsigned int m, n;
    //double elapsed_r, elapsed_i;
    //clock_t iniciorec, inicioiter;
    //time_t finalrec, finaliter;

    scanf("%u %u", &m, &n);

    //iniciorec = clock();
    printf("%u", MDCrecursiva(m, n));
    //finalrec = clock();
    /*
    inicioiter = clock();
    printf("%u\n", MDCiterativa(m, n));
    finaliter = clock();

    elapsed_r = (double)(finalrec - iniciorec) / CLOCKS_PER_SEC;
    elapsed_i = (double)(finaliter - inicioiter) / CLOCKS_PER_SEC;

    printf("Recursivo: %lf\nIterativo: %lf\n", elapsed_r, elapsed_i);
    */
return 0;
}

/*
unsigned int MDCiterativa(unsigned int m, unsigned int n){
    unsigned int big, sma;

    if(m >= n){
        big = m;
        sma = n;
    } else {
        big = n;
        sma = m;
    }

    for(unsigned int i = sma; i > 0; i--){
        if((big % i) == 0 && (sma % i) == 0){
            return i;
        }
    }

    return 0;
}
*/
//alg de euclides recursiva
unsigned int MDCrecursiva(unsigned int m, unsigned int n){

    //cond de stop
    if(n == 0){
        //encontrou
        return m; //retornar valor aqui
    } else {
        //nao encontrou
        return MDCrecursiva(n, m%n);
    }

    //erro
    return -1;
}
