#include <stdio.h>

int main(void){
    int n = 12, k = 13;
    scanf("%d %d", &n, &k);
    //printf("%d\n", ite(n, k));

    printf("%d\n", rec(n,k));
    return 0;
}

int ite(int n, int k){
    int res = n;

    for(int i = 1; i < k; i++){
        res = (res*n) % 1000;
    }

    return res;
}

int rec(int n, int k){
    int res = n, a;

    if(k == 1){
        return n;
    }

    if(k > 1){
        a = rec(n, k/2);
        if((k % 2) == 0){
            res = a * a;
        } else {
            res = a * a * n;
        }
    }

    return res % 1000;
}
