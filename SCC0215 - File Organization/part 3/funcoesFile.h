#ifndef _H_FFILEC
#define _H_FFILEC

#define StackType int

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

// 17 bytes + 55 lixo ($)
typedef struct indice{
    char status;
    int noRaiz;
    int nroNiveis;
    int proxRRN;
    int nroChaves;
} INDICE_CABECALHO;

typedef struct chave{
    int C;
    int PR;
    int P;
    struct chave *next;
    struct chave *prev;

} CHAVE;

typedef struct lista{
    int nivel;
    int N;
    int P1;
    CHAVE *start;
    CHAVE *end;

} NO_LISTA;

//struct stack
typedef struct stpos{
    int content;
    struct stpos *prox; 
} ST_POS;

typedef struct stack{
    ST_POS *topo;
    int tamanho;
} STACK;

int lineDSV(FILE *source, FILE *destiny);
void transferData(FILE *f, REGISTRO_DADOS *r);
void inicioSetup(CABECALHO c, FILE *f);
void insereCabecalho(FILE *f, CABECALHO c);
void RAMTrash(int amount, char *target);
void completeTrash(FILE *f, int total, int amount);
void sepSubst(char *line, int search, char *spot);
int filterData(FILE *f, int o, int *travas, REGISTRO_DADOS *temp, INDICE_CABECALHO *i);
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
int insereRegistroBinario(FILE *f);
void atualizaCampo(REGISTRO_DADOS A, REGISTRO_DADOS *B, int campo);
int buscaRRN(FILE *f, int RRN);
void skipToRRN(FILE *f, int RRN);
int *inverteTravas(int *travas);
int updateData(FILE *f, int *travas, REGISTRO_DADOS *temp);

INDICE_CABECALHO *criaHeaderIndice();
void insereHeaderIndice(FILE *b, INDICE_CABECALHO *i, int firstTime);
void destroiHeaderIndice(INDICE_CABECALHO *i);
int lerHeaderIndice(FILE *b, INDICE_CABECALHO *i);
void insereNaArvore(FILE *b, INDICE_CABECALHO *i, NO_LISTA *no, CHAVE *ch);
void inserePagina(FILE *b, NO_LISTA *no, int RRN);
NO_LISTA *extraiPagina(FILE *b, int RRN);
int interfaceArvore(FILE *f, FILE *b, INDICE_CABECALHO *i);
void buildTree(FILE *f, FILE *b, INDICE_CABECALHO *i, int key);
void insertRecursive(FILE *b, INDICE_CABECALHO *i, NO_LISTA *no, CHAVE *ch, STACK *s, int RRN);

int searchIndex(FILE *f, FILE *b, INDICE_CABECALHO *i, int busca);

STACK *criaStack();
void pushStack(STACK *s, StackType content);
int popStack(STACK *s);
void destroiStack(STACK *s);

NO_LISTA *criaLista(int nivel, int P1);
CHAVE *criaChave(int C, int PR, int P);
void destroiLista(NO_LISTA *no);
void destroiChave(CHAVE *ch);
void insereChave(NO_LISTA *no, CHAVE *ch);
CHAVE *removeChave(NO_LISTA *no, int pos);
void printLista(NO_LISTA *no);
int filhoRRN(NO_LISTA *no, int value);
int seekEqualKeys(NO_LISTA *no, int value);

#endif