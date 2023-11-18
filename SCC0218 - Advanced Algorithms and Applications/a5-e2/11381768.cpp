#include <stdio.h>
#include <vector>

using namespace std;

//  Vamos aplicar o método da bisseção

void printer(vector<int> v, int locale, int h, int N){
    int center = locale;
    int top = -1, bot = -1;

    //  Eu realmente nao sei pq q isso funciona, mas parece funcionar???
    if(v.at(center) < h){
        center++;
    }

    //  if central value is greater than height, it's the top value
    if(v.at(center) > h){
        top = v.at(center);

    //  otherwise, if may be the bottom value
    } else if(v.at(center) < h){
        bot = v.at(center);
        
    //  if everything fails, then it's equal. We cant confirm anything
    }

    while(bot == -1){
        //  if out of bounds
        if(center - 1 < 0){
            // signal and leave
            bot = -2;

        //  if in bounds, make checks
        } else{
            center--;

            //  if found value is different than top value and itself
            if(v.at(center) != top && v.at(center) != h){
                //  signal it
                bot = v.at(center);
            }
        }
    }

    center = locale;

    while(top == -1){
        //  if out of bounds
        if(center + 1 >= N){
            // signal and leave
            top = -2;

        //  if in bounds, make checks
        } else{
            center++;

            //  if found value is different than bot value and itself
            if(v.at(center) != bot && v.at(center) != h){
                //  signal it
                top = v.at(center);
            }
        }
    }
    
    //  if top non existent
    if(bot == -2){
        printf("X ");
    } else{
        printf("%d ", bot);
    }

    //  if bot non existent
    if(top == -2){
        printf("X\n");
    } else{
        printf("%d\n", top);
    }

    return;
}

void bisection(vector<int> v, int comp, int N){
    int eps = 2, center = 0;
    int high, low;

    low = 0;
    high = N-1;

    if(v.at((high + low) / 2) == comp){
        printer(v, ((high + low) / 2), comp, N);
    } else{
        while(high - center >= eps){
            if(v.at(center) < comp){
                low = center;
            } else if(v.at(center) == comp){
                high = center;
            } else{
                high = center;
            }

            center = ((low + high)/2);
        }

        printer(v, center, comp, N);
    }

    return;
}

int main(void){
    vector<int> v;
    int N, aux;
    int Q;

    //  Number of lady chimps
    scanf("%d", &N);
    for(int count = 0; count < N; count++){

        //  Lady chimp heights in order of size
        scanf("%d", &aux);
        v.push_back(aux);
    }

    //  Number of queries
    scanf("%d", &Q);
    for(int count = 0; count < Q; count++){
        //  Heights of Luchu (wtfrick)
        scanf("%d", &aux);

        //  Do something for each height?
        bisection(v, aux, N);
    }

    //for (auto i = array.begin(); i != array.end(); i++){
        //printf("%d ", *i);
    //}

    return 0;
}
