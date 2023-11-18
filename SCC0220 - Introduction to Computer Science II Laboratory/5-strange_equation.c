#include <stdio.h>

int q, p;
long long int equation(int n);

int main(void){
    int n;
    long long int res;

    scanf("%d %d %d", &n, &q, &p);

    res = equation(n);

    printf("%lli", res);

    return 0;
}

long long int equation(int n){
    long long int res = 0, fun = 0, res2 = 0;

    if(n <= 1){
        res = p;
        if(p != 0){
            for(int i = p-1; i > 1; i--){
                res = res * i;
            }
            return res;
        } else{
            return 1;
        }
    }

    fun = equation(n/2);

    for(int i = 1; i <= 8; i++){
        res += fun + i;
    }

    for(int i = 1; i <= q; i++){
        for(int j = 1; j <= n; j++){
            res2 += i * j;
        }
    }

    return res + res2;
}
