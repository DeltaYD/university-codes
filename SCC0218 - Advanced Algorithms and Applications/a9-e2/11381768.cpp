#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

string x;
string y;

int o;
int p;

int **MEMO;

int min(int a, int b, int c){
    return min(a, min(b, c));
}

int Edit(){
    int ca = 0, cb = 0, cc = 0;

    for(int m = 0; m <= o; m++){
        for(int n = 0; n <= p; n++){
            if(m == 0){
                for(int i = n-1; i >= 0; i--){
                    MEMO[m][n] += y[i] - 'a' + 1;
                }

            }
            else if(n == 0){
                for(int i = m-1; i >= 0; i--){
                    MEMO[m][n] += x[i] - 'a' + 1;
                }

            } else if(x[m-1] == y[n-1]){
                MEMO[m][n] = MEMO[m-1][n-1];

            } else{
                //  remocao
                ca = x[m-1] - 'a' + 1;
                //  insercao
                cb = x[n-1] + 'a' + 1;
                //  troca
                if(x[m-1] >= y[n-1]){
                    cc = x[m-1] - y[n-1];
                } else{
                    cc = y[n-1] - x[m-1];
                }

                MEMO[m][n] = min(ca + MEMO[m-1][n],          //remocao
                                 cb + MEMO[m][n-1],          //insercao
                                 cc + MEMO[m-1][n-1]         //troca
                                 );
            }
        }
    }
    return MEMO[o][p];
}

int main(int argc, char const *argv[]){

    cin >> x;
    cin >> y;
    o = x.length();
    p = y.length();

    MEMO = (int**)calloc(o+1, sizeof(int*));
    for(int i = 0; i <= o; i++){
        MEMO[i] = (int*)calloc(p+1, sizeof(int));
    }

    printf("%d\n", Edit());
    //printMAT();

    for(int i = 0; i <= o; i++){
        free(MEMO[i]);
    }
    free(MEMO);

    return 0;
}