//#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

#define MAX 200

int v[21], tam, sum = 0;

void wssp(){
    int MEMO[210];

    memset(MEMO, 0, sizeof(MEMO));

    for (int i = 0; i <= tam; ++i)
    {
        for (int p = sum/2; p >= v[i]; --p)
        {
            if(MEMO[p] < MEMO[p - v[i]] + v[i])
                MEMO[p] = MEMO[p - v[i]] + v[i];
        }
        
    }

    puts((sum - 2 * MEMO[sum/2] == 0)
        ? "YES" : "NO");

    return;
}

int main(){
    int m, value;
    char c;

    scanf("%d", &m);

    for(int kount = 0; kount < m; kount++){
        for(int count = 0; scanf("%d%c", &value, &c) == 2; count++){
            if(c != '\n'){
                v[count] = value;
                sum += value;
            } else{
                v[count] = value;
                sum += value;
                tam = count;
                count = 0;

                wssp();

                sum = 0;
                break;
            }
        }
    }


    return 0;
}


//while(scanf("%d %c")){    d for numbers and c for spacebar or \n. if \n, end scan??

//}