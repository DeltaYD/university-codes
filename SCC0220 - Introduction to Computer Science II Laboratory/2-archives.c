#include <stdio.h>
#include <stdlib.h>

// Gustavo Akira Hirakawa 11381768

struct mainRegistry {
    int id;
    char name[12];
    int age;
};

typedef struct mainRegistry MainRegistry;

MainRegistry *readRegister(FILE *ptr);
void printRegister(MainRegistry *s);

int main(void){
    int opt = -1, seekID = 0, found = 0;
    MainRegistry s1, *buffer;
    char filename[50];
    FILE *ptr;

    do{
        buffer = 1;
        scanf("%d\n", &opt);
        if(opt != 0){
            scanf("%s", &filename);
        }
        switch(opt) {
        case 1:
            // get id
            scanf("%d", &s1.id);
            // get name
            scanf("%s", &s1.name);
            // get age
            scanf("%d", &s1.age);
            // create file if it does not exist
            // write this registry at eof
            ptr = fopen(filename, "ab");

            fwrite(&s1.id, sizeof(int), 1, ptr);
            fwrite(&s1.name, sizeof(char)*12, 1, ptr);
            fwrite(&s1.age, sizeof(int), 1, ptr);

            fclose(ptr);

            break;

        case 2:
            scanf("%d", &seekID);

            ptr = fopen(filename, "rb");
            if(ptr != NULL){
                fseek(ptr, 0, SEEK_SET);

                while(buffer != NULL){
                    buffer = readRegister(ptr);

                    if(buffer != NULL && buffer->id == seekID){
                        printRegister(buffer);
                        //free(buffer);
                        found = 1;
                        break;
                    } else if(buffer != NULL){
                        //free(buffer);
                    }
                }
                if(found != 1){
                    printf("Registro não encontrado.\n");

                } else {
                    found = 0;
                }

                fclose(ptr);
            } else {
                printf("Arquivo não encontrado.\n");
            }
            break;

        case 3:
            ptr = fopen(filename, "rb");

            if(ptr != NULL){
                fseek(ptr, 0, SEEK_SET);

                while(buffer != NULL){
                    buffer = readRegister(ptr);

                    if(buffer != NULL){
                        printRegister(buffer);
                        //free(buffer);
                    }
                }
                fclose(ptr);

            } else {
                printf("Arquivo não encontrado.\n");
            }
            break;

        default:
            break;
        }

        // clean scanf buffer
        fflush(stdin);
    } while (opt != 0);

return 0;
}

// return 0 if not eof
// return -1 if eof
MainRegistry *readRegister(FILE *ptr){
    MainRegistry *s2;
    int notice = 0;
    s2 = malloc(sizeof(MainRegistry));

    fread(&s2->id, sizeof(int), 1, ptr);
    fread(&s2->name, sizeof(char), 12, ptr);
    notice = fread(&s2->age, sizeof(int), 1, ptr);

    if(notice == 0){
        //free(s2);
        s2 = NULL;
    }
    return s2;
}

void printRegister(MainRegistry *s){
    printf("ID: %d | NOME: %s | IDADE: %d\n", s->id, s->name, s->age);
    return;
}
