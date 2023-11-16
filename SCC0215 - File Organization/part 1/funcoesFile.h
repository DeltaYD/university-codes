#ifndef _H_FFILEC
#define _H_FFILEC

typedef struct cabecalho{
    char status;
    int RRNproxRegistro;
    int numeroRegistrosInseridos;
    int numeroRegistrosRemovidos;
    int numeroRegistrosAtualizados;
} CABECALHO;

typedef struct dados{
    int tamCampoMae;
    int tamCampoBebe;
    char cidadeMae[48];
    char cidadeBebe[48];
    int idNascimento;
    int idadeMae;
    char dataNascimento[11];
    char sexoBebe;
    char estadoMae[3];
    char estadoBebe[3];
} REGISTRO_DADOS;

void criaCabecalho(CABECALHO *c);
void destroiCabecalho(CABECALHO *c);
void startupCabecalho(CABECALHO *c);
int lineDSV(FILE *source, FILE *destiny);
void transferData(FILE *f, REGISTRO_DADOS r);
void inicioSetup(CABECALHO c, FILE *f);
void insereCabecalho(FILE *f, CABECALHO c);
void RAMTrash(int amount, char *target);
void completeTrash(FILE *f, int total, int amount);
void sepSubst(char *line, int search, char *spot);
void filterData(FILE *f);
void printBabyData(REGISTRO_DADOS r, int sexo);

void binarioNaTela(char *nomeArquivoBinario);
void trim(char *str);

#endif