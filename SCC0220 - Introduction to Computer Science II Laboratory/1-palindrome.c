#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Gustavo Akira Hirakawa - 11381768
//Sem grupo ainda

int palindrome(char* input, int size);

int main(void){
char* input = (char*)malloc(200);
int result = 0, charcount = 0;

int c;

//get input
while((c = getchar()) != EOF){
    if(!isspace(c) && !ispunct(c) && c != '\n'){
        input[charcount] = tolower(c);
        charcount++;
    }
    if (c == '\n'){
        input[charcount] = '\0';
        break;
    }
}

//put through test function
result = palindrome(input, charcount);

//print found results
if (result == 1){
    printf("Sim");
} else {
    printf("Não");
}

return 0;
}

int palindrome(char* input, int size){
    for(int i = 0; i < size; i++){
        if(input[i] != input[size-i-1]){
            return 0;
        }
    }
    return 1;
}






