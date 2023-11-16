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


int lineDSV(FILE *source, FILE *destiny);
void transferData(FILE *f, REGISTRO_DADOS *r);
void inicioSetup(CABECALHO c, FILE *f);
void insereCabecalho(FILE *f, CABECALHO c);
void RAMTrash(int amount, char *target);
void completeTrash(FILE *f, int total, int amount);
void sepSubst(char *line, int search, char *spot);
int filterData(FILE *f, int o, int *travas, REGISTRO_DADOS *temp);
void printBabyData(REGISTRO_DADOS r, int sexo);

void binarioNaTela(char *nomeArquivoBinario);
void trim(char *str);
void scan_quote_string(char *str);

REGISTRO_DADOS *criaTemporario();
void destroiTemporario(REGISTRO_DADOS *rd);
int *criaTravas(int tam);
void destroiTravas(int *vet);
int preencheTemporario(REGISTRO_DADOS *crit, char *str);
int comparaCampo(REGISTRO_DADOS A, REGISTRO_DADOS *B, int campo);
int buscaCombinada(FILE *source, CABECALHO c, int o);
void removeRegistroEstatico(FILE *f);
void insereRegistroBinario(FILE *f);
void atualizaCampo(REGISTRO_DADOS A, REGISTRO_DADOS *B, int campo);
int buscaRRN(FILE *f, int RRN);
void skipToRRN(FILE *f, int RRN);
int *inverteTravas(int *travas);
int updateData(FILE *f, int *travas, REGISTRO_DADOS *temp);

#endif