#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;

ll tamCrivo;

bitset<10000010> bs;
vector<ll> primos;

mii fatoresPrimosMAP(ll n){
    mii fatores;
    ll FP;
    ll ind = 0;
    FP = primos[ind];

    while(FP*FP <= n){
        while(n % FP == 0){
            fatores[FP]++;
            n = n / FP;
        }
        FP = primos[++ind];
    }

    if(n != 1){ //  e se o n passado e um primo
        fatores[n]++;
    }

    return fatores;
}

//  podemos tbm usar o crivo de erastótenes pra calcular os primose
void crivo(ll n){
    tamCrivo = n+1;

    bs.set();
    bs[0] = bs[1] = 0;

    for (ll i = 2; i < tamCrivo; i++)   //percorre todo o crivo
    {
        if(bs[i]){  //  se ele e primo, elimina todos os seus multiplos e coloca no vetor de primos
            for (ll j = i*i; j <= tamCrivo; j+=i)
            {
                bs[j] = 0;
            }
            primos.push_back(i);
        }
    }
    
}

bool isPrime(ll n){
    if(n <= tamCrivo){
        return bs[n];
    }

    for(ll i = 0; ((unsigned) i) <= primos.size() && primos[i]*primos[i] <= n; i++){
        if(n % i == 0){
            return false;
        }
    }

    return true;
}


int main(int argc, char const *argv[]){
    vi prime_qts;
    mii map;
    int value;
    int check = 0;

    crivo(100);

    while(1){
        scanf("%d", &value);
        map.clear();
        if(value == 0){
            break;
        } else{
            for(int count = 2; count <= value; count++){
                check = 0;
                mii m = fatoresPrimosMAP(count);

                for(mii::iterator i = m.begin(); i != m.end(); i++){
                    map[i->first] += i->second;

                }
            }

            if(value < 100){
                if(value < 10){
                    printf("  %d! =", value);
                } else{
                    printf(" %d! =", value);
                }
            } else{
                printf("%d! =", value);
            }
            //printf("%d! = ", value);
            for(mii::iterator i = map.begin(); i != map.end(); i++){
                check++;
                if(check == 16){
                    check = 0;
                    printf("\n      ");
                }
                if(i->second < 100){
                    if(i->second < 10){
                        printf("  %d", i->second);
                    } else{
                        printf(" %d", i->second);
                    }
                } else{
                    printf("%d ", i->second);
                }
                    //printf("%.*d ", 2, i->second);
            }
            printf("\n");
        }

    }

    return 0;
}