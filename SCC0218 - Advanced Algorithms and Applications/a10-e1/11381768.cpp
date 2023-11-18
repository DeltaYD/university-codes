#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <string.h>

using namespace std;

typedef long long ll;
#define MAXT 260000
#define MAXP 1001
#define TAM 1010

void kmpPreProcess(ll *b, string pat, ll tam_pat){
    ll i = 0, j = -1; b[0] = -1;

    while(i < tam_pat){
        while(j>=0 && pat[i] != pat[j]){
            j = b[j];
        }
        i++; j++;
        b[i] = j;
    }
}

void kpmSearch(ll *b, string pat, string text, ll tam_pat, ll tam_t){
    ll i = 0, j = 0;
    
    while(i < tam_t){
        while(j>=0 && text[i] != pat[j]){
            j = b[j];
        }
        i++; j++;
        if(j == tam_pat){
            cout << "O padrao foi encontrado na posicao " << i - j << endl;
            j = b[j];
        }
    }
}

int main(int argc, char const *argv[]){
    string texto, padrao;
    ll b[TAM];

    cin >> texto;
    cin >> padrao;

    ll tamT = (ll) texto.length();
    ll tamP = (ll) padrao.length();

    kmpPreProcess(b, padrao, tamP); //para calcular o vetor de borda
    kpmSearch(b, padrao, texto, tamP, tamT);

    return 0;
}