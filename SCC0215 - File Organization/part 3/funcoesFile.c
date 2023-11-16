
//Nome: Gustavo Akira Hirakawa
//NUSP: 11381768

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesFile.h"

#define ORDEM 6
#define StackType int
#define sizeIndex 72

/*  >> Esta funcao recebe dois ponteiros de arquivo.
 *          > *source sera o ponteiro do arquivo de
 *          onde as informacoes serao extraidas;
 *          > *destiny sera o ponteiro de destino da
 *          extracao.
 *  >> A funcao so funciona se o arquivo 'source':
 *          > tiver um numero constante de informacoes
 *          por linha;
 *          > estiver separado linha a linha.
 *  >> O retorno da funcao sera:
 *          > '0', se a leitura estiver incompleta e
 *          ainda existirem informacoes em 'source';
 *          > '1', se chegou no fim do arquivo.
 *  >> Observacao: Esta funcao e hardcoded, pois usa
 *  variaveis mutaveis, sujeitos a modificacoes no
 *  decorrer dos trabalhos.
 *  >> Contudo, ela usa funcoes softcoded para CSV, que
 *  podem ser reutilizados para outras leituras
 *  futuras.
 */
int lineDSV(FILE *source, FILE *destiny){
    char line[129], spot[129];
    REGISTRO_DADOS r;

    /*  >> Esta funcao usa tres funcoes principais + funcoes de string.h:
     *          1) sepSubst(): Filtra uma linha até '\n' por
     *          'posicao de dado' (1 = primeira string, ... ,
     *          8 = ultima string);
     *          2) RAMTrash(): Cria uma string de lixo para colocar
     *          um '\0' na frente.
     *          3) transferData(): Envia as informacoes extraidas
     *          e guardadas no REGISTRO_DADOS, para o arquivo binario;
     * 
     *  >> Variaveis:
     *          1) line[129]: String de armazenamento de uma
     *          linha de registro inteira. Sera filtrada.
     *          2) spot[129]: String que recebe a informacao
     *          filtrada.
     *          3) r: estrutura de dados que armazena a resultante
     *          de cada bloco de processamento.
     */

    if(fgets(line, 129, source) == NULL){
        return(1);
    }

    // BLOCO 1: cidadeMae
    sepSubst(line, 1, spot);                // Obtencao da primeira info
    strcpy(r.cidadeMae, spot);              // Guarda no registro de dados
    r.tamCampoMae = strlen(r.cidadeMae);    // Guarda tamanho da string

    // BLOCO 2: cidadeBebe
    sepSubst(line, 2, spot);                // Obtencao da segunda info
    strcpy(r.cidadeBebe, spot);             // Guarda no registro de dados
    r.tamCampoBebe = strlen(r.cidadeBebe);  // Guarda tamanho da string

    // BLOCO 3: idNascimento
    sepSubst(line, 3, spot);                // Obtencao da terceira info
    if(strlen(spot) == 0){
        r.idNascimento = -1;                // Caso esteja vazio
    } else {
        r.idNascimento = atoi(spot);        // Caso contenha algum valor
    }

    // BLOCO 4: idadeMae
    sepSubst(line, 4, spot);                // Obtencao da quarta info
    if(strlen(spot) == 0){
        r.idadeMae = -1;                    // Caso esteja vazio
    } else {
        r.idadeMae = atoi(spot);            // Caso contenha algum valor
    }

    // BLOCO 5: dataNascimento
    sepSubst(line, 5, spot);                // Obtencao da quinta info
    if(strlen(spot) == 0){
        RAMTrash(11, spot);                 // Enche a string com lixo
        strcpy(r.dataNascimento, spot);
        r.dataNascimento[0] = '\0';         // Caso esteja vazio
    } else {
        strcpy(r.dataNascimento, spot);     // Caso contenha algum valor
    }

    // BLOCO 6: sexoBebe
    sepSubst(line, 6, spot);                // Obtencao da sexta info
    if(strlen(spot) == 0){
        r.sexoBebe = '0';                   // Caso esteja vazio
    } else {
        r.sexoBebe = spot[0];               // Caso contenha algum valor
    }

    // BLOCO 7: estadoMae
    sepSubst(line, 7, spot);                // Obtencao da setima info
    if(strlen(spot) == 0){
        RAMTrash(3, spot);                  // Enche a string com lixo
        strcpy(r.estadoMae, spot);
        r.estadoMae[0] = '\0';              // Caso esteja vazio
    } else{
        strcpy(r.estadoMae, spot);          // Caso contenha algum valor
    }

    // BLOCO 8: estadoBebe
    sepSubst(line, 8, spot);                // Obtencao da oitava info
    if(strlen(spot) == 0){
        RAMTrash(3, spot);                  // Enche a string com lixo
        strcpy(r.estadoBebe, spot);
        r.estadoBebe[0] = '\0';             // Caso esteja vazio
    } else {
        strcpy(r.estadoBebe, spot);         // Caso contenha algum valor
    }
    // Envio de dados para serem inseridos no arquivo binario.
    transferData(destiny, &r);

    return(0);
}

/*  >> Esta funcao recebe um ponteiro de arquivo.
 *          > *f sera o destino dos dados guardados
 *          na estrutura de registro de dados 'r'.
 *  >> Ele foi programado para seguir estritamente
 *  as especificacoes fornecidas.
 *  >> Observacao: Novamente, esta funcao e hardcoded.
 *  Ele depende de lineDSV() e vice-versa.
 */
void transferData(FILE *f, REGISTRO_DADOS *r){

    /* >> Esta funcao usa uma funcao principal + fwrite():
                1) completeTrash(): Carrega um arquivo
                com lixo ate determinado byte offset
                referente ao REGISTRO! Nao ao arquivo.
     */

    // BLOCO 1: Escrita do tamanho das strings variaveis
    fwrite(&(r->tamCampoMae), sizeof(int), 1, f);
    fwrite(&(r->tamCampoBebe), sizeof(int), 1, f);

    // BLOCO 2: Escrita das strings variaveis (somente se existirem)
    if(r->tamCampoMae != 0){
        fwrite(&(r->cidadeMae), sizeof(char) * r->tamCampoMae, 1, f);
    }
    if(r->tamCampoBebe != 0){
        fwrite(&(r->cidadeBebe), sizeof(char) * r->tamCampoBebe, 1, f);
    }

    // BLOCO 3: Preenchimento de lixo ate o byte 104, continuando do 105
    completeTrash(f, 8 + r->tamCampoMae + r->tamCampoBebe, 105);

    // BLOCO 4: Escrita dos segmentos de tamanho fixo
    fwrite(&(r->idNascimento), sizeof(int), 1, f);
    fwrite(&(r->idadeMae), sizeof(int), 1, f);
    fwrite(&(r->dataNascimento), sizeof(char) * 10, 1, f);
    fwrite(&(r->sexoBebe), sizeof(char) * 1, 1, f);
    fwrite(&(r->estadoMae), sizeof(char) * 2, 1, f);
    fwrite(&(r->estadoBebe), sizeof(char) * 2, 1, f);

    return;
}

/*  >> Esta funcao recebe um ponteiro de arquivo e
 *  uma estrutura de cabecalho.
 *          > *f sera o destino dos dados guardados
 *          na estrutura de registro de cabecalho 'c'.
 *  >> Ele sempre escreve na mesma ordem e requer que
 *  o ponteiro 'f' esteja no inicio do arquivo.
 */
void insereCabecalho(FILE *f, CABECALHO c){

    if(f == NULL){
        printf("Ops! Este arquivo não existe!\n");
        return;
    }

    fwrite(&(c.status), sizeof(char), 1, f);
    fwrite(&(c.RRNproxRegistro), sizeof(int), 1, f);
    fwrite(&(c.numeroRegistrosInseridos), sizeof(int), 1, f);
    fwrite(&(c.numeroRegistrosRemovidos), sizeof(int), 1, f);
    fwrite(&(c.numeroRegistrosAtualizados), sizeof(int), 1, f);

    return;
}

/*  >> Esta funcao enche uma string *target com lixo.
 *  >> Ela deve receber o parametro 'amount', que deve
 *  ser o tamanho, ou seja, quantidade de bytes dessa
 *  string.
 */
void RAMTrash(int amount, char *target){
    char trash = '$';

    /*  >> Esta funcao retorna, em target, o numero
     *  correto de lixo ($);
     */
    for(int count = 0; count < amount; count++){
        target[count] = trash;
    }

    return;
}

/*  >> Esta funcao preenche um arquivo *f com lixo.
 *  >> Ela deve receber o byte offset 'amount' de onde
 *  o ponteiro do arquivo deve parar.
 *  >> Ela tambem deve receber quantos bytes 'total'
 *  ja foram escritos antes do limite 'amount'.
 *  >> Se receber total > amount, fara nada.
 */
void completeTrash(FILE *f, int total, int amount){
    char trash = '$';

    /*  >> Variaveis:
     *          1) trash: Trata-se do lixo que sera inserido nos
     *          registros.
     */
    for(int count = total; count < amount; count++){
        fwrite(&trash, sizeof(char), 1, f);
    }

    return;
}

/*  >> Esta e uma funcao substitutiva de strsep().
 *  >> Ela recebe uma string *line, contendo uma linha
 *  inteira de CSV.
 *  >> Depois, recebe 'search', que se trata da busca.
 *          > search deve ser menor que o numero de
 *          informacoes guardadas numa linha. Por exemplo,
 *          neste trabalho, temos 8 informacoes em cada
 *          linha do CSV. Portanto, search nao deve ser
 *          zero nem nove. Se buscamos a informacao 8,
 *          então search = 8;
 *  >> Enfim, recebe *spot, que sera o local de armazenamento
 *  da string extraida.
 */
void sepSubst(char *line, int search, char *spot){
    char symbol, transfer[100];
    int count = 0, kount = 0, click = 0;

    /*  >> Variaveis:
     *          1) symbol: caractere qualquer que for lido de 'line'.
     *          Usado para encontrar virgulas.
     *          2) transfer: local que recebe um dado, caractere por
     *          caractere.
     *          3) count, kount e click sao contadores de posicao e
     *          deteccao.
     */

    /* Neste segmento, transportaremos o char symbol atraves de todos os chars que nao nos interessem
     * quando achar a virgula que nos interesse, vai parar o laco.
     */
    for(count = 0; click != (search - 1); count++){
        symbol = line[count];
        if(symbol == ','){
            click++;
        }
    }
    /* Note que nao zeramos o valor de count. Aqui, ele continua a ler de onde ele parou com uma nova variavel, kount.
     * 'kount' sao as posicoes do vetor de chars 'transfer', indicando char uma por uma.
     * Quando encontrar as delimitacoes definidas (',' ... '\n' ... '\0'), vai interromper o laco.
     * No final, indicamos o fim da string 'transfer' com um '\0'.
     */
    for(kount = 0; line[count] != ',' && line[count] != '\n' && line[count] != '\0'; count++){
        transfer[kount] = line[count];
        kount++;
    }
    transfer[kount] = '\0';

    strcpy(spot, transfer);
    return;
}

/*  >> Esta funcao ja faz parte da funcionalidade '2' do
 *  trabalho.
 *  >> Ela le e formata cada campo do arquivo *f (fonte), aberto
 *  em binario, para fazer exatamente o que a especificacao
 *  pede.
 *  >> Desse modo, nenhuma informacao e guardada errada no
 *  registro de dados.
 *  >> No entanto, informacoes guardadas aqui sao volateis,
 *  ou seja, so podem ser utilizadas enquanto dentro desta
 *  funcao.
 *  >> NEW: Retorna um inteiro que indica se o REGISTRO 'temp'
 *  e semelhante ao REGISTRO 'r', ou nao. Retorno 1 = E SEMELHANTE.
 *  Retorno 0 = NAO E SEMELHANTE.
 */
int filterData(FILE *f, int o, int *travas, REGISTRO_DADOS *temp, INDICE_CABECALHO *i){
    REGISTRO_DADOS r;
    int sum = 0, found = 0;
    char trash[128];

    // BLOCO 1: Recebimento do tamanho de campos variaveis
    fread(&(r.tamCampoMae), sizeof(int), 1, f);
    fread(&(r.tamCampoBebe), sizeof(int), 1, f);

    if(r.tamCampoMae == -1 && o != 7){
        fread(&trash, sizeof(char) * 120, 1, f);
        return 0;
    }

    // BLOCO 2: Leitura dos campos variaveis SE EXISTIREM (maiores que zero)
    // > Campo da Mae
    if(r.tamCampoMae != 0){
        fread(&(r.cidadeMae), sizeof(char)*r.tamCampoMae, 1, f);
        r.cidadeMae[r.tamCampoMae] = '\0';
    } else {
        strcpy(r.cidadeMae, "-");
    }
    // > Campo do Bebe
    if(r.tamCampoBebe != 0){
        fread(&(r.cidadeBebe), sizeof(char)*r.tamCampoBebe, 1, f);
        r.cidadeBebe[r.tamCampoBebe] = '\0';
    } else {
        strcpy(r.cidadeBebe, "-");
    }

    // BLOCO 3: Pula o lixo na memoria ate o byte onde continuam as informacoes
    // Conta: (byte offset de continuacao) - (bytes ja corridos) - (tamanho dos campos variaveis) = posicao buscada.
    // Ou seja, 105 - (4 + 4) - (tamCampoMae + tamCampoBebe).
    fread(&trash, sizeof(char), 97 - (r.tamCampoBebe + r.tamCampoMae), f);

    // BLOCO 4: Leitura de inteiros
    fread(&(r.idNascimento), sizeof(int), 1, f);
    fread(&(r.idadeMae), sizeof(int), 1, f);

    // BLOCO 5: Leitura de tamanhos fixos
    fread(&(r.dataNascimento), sizeof(char)*10, 1, f);
    r.dataNascimento[10] = '\0';
    if(strlen(r.dataNascimento) == 0){
        strcpy(r.dataNascimento, "-");
    }
    // BLOCO 6: Leitura de char
    fread(&(r.sexoBebe), sizeof(char), 1, f);

    // BLOCO 7: Leitura dos Estados da Mae e do Bebe
    // > estadoMae
    fread(&(r.estadoMae), sizeof(char)*2, 1, f);
    r.estadoMae[2] = '\0';
    if(strlen(r.estadoMae) == 0){
        strcpy(r.estadoMae, "-");           // Caso esteja vazio
    }
    // > estadoBebe
    fread(&(r.estadoBebe), sizeof(char)*2, 1, f);
    r.estadoBebe[2] = '\0';
    if(strlen(r.estadoBebe) == 0){
        strcpy(r.estadoBebe, "-");          // Caso esteja vazio
    }

    //  NEW: Switch case, usando entrada nova 'o' /opcao/.
    //  Cada caso faz alguma coisa diferente, usando os dados que
    //  acabaram de ser lidos e armazenados no REGISTRO 'r'.
    switch(o){
        case 2:
            //  Impressao padrao do TRABALHO PRATICO 1.
            printBabyData(r, r.sexoBebe);
            found = 1;
        break;


        case 3:
            //  Usa comparaCampo() para ver se o REGISTRO 'r' e compativel
            //  com o REGISTRO de busca 'temp'.
            //  Usa as travas que indicam qual e o campo analisado, vez por vez.
            for(int count = 1; count < travas[0]; count++){
                if(comparaCampo(r, temp, travas[count]) != 0){
                    sum++;
                }
            }
            //  Caso nao hajam diferencas, 'sum' nao recebe valor e permite a
            //  impressao desse registro.
            if(sum == 0){
                printBabyData(r, r.sexoBebe);
                found = 1;
            }
        break;


        case 4:
            //  Faz algo parecido com a busca/3/, mas so no campo '4'/idNascimento/.
            if(comparaCampo(r, temp, 4) == 0){
                printBabyData(r, r.sexoBebe);
                found = 1;
            }
            
        break;


        case 5:
            //  Basicamente, compara igual na busca, mas ao inves de imprimir os
            //  dados do registro, ira remove-lo usando removeRegistroEstatico().
            for(int count = 1; count < travas[0]; count++){
                if(comparaCampo(r, temp, travas[count]) != 0){
                    sum++;
                }
            }
            if(sum == 0){
                removeRegistroEstatico(f);
                found = 1;
            }
        break;



        //  O caso 6 nao existe, porque nao faz uso de leitura de registros. Vide
        //  a main: /programaTrab.c/, o ponteiro de arquivo pula direto ao fim.



        case 7:
            //  Inverte as indicacoes de trava.
            travas = inverteTravas(travas);
            //  Agora copia os campos indicados pelas travas novas no REGISTRO temp.
            for(int count = 1; count < travas[0]; count++){
                atualizaCampo(r, temp, travas[count]);
            }
            //  Sobreescreve o registro antigo com os novos dados.
            //fseek(f, -128, SEEK_CUR);
            transferData(f, temp);
        break;


        case 8:
            atualizaCampo(r, temp, 10);
            found = 1;
        break;
    }

    //  Novo estilo de retorno que indica se a busca foi feita com sucesso, ou nao.
    return found;
}


/*  >> Esta funcao usa os parametros obtidos em filterData()
 *  para imprimir exatamente o que foi pedido.
 *  >> Ela recebe o registro de dados 'r' com as informacoes
 *  ja filtradas e simplesmente imprime.
 */
void printBabyData(REGISTRO_DADOS r, int sexo){

    // Realiza uma impressao especifica com base no sexo do bebe
    if(sexo == '0'){
        printf("Nasceu em %s/%s, em %s, um bebê de sexo IGNORADO.\n", r.cidadeBebe, r.estadoBebe, r.dataNascimento);
    } else if(sexo == '1'){
        printf("Nasceu em %s/%s, em %s, um bebê de sexo MASCULINO.\n", r.cidadeBebe, r.estadoBebe, r.dataNascimento);
    } else {
        printf("Nasceu em %s/%s, em %s, um bebê de sexo FEMININO.\n", r.cidadeBebe, r.estadoBebe, r.dataNascimento);
    }

    return;
}

/*  >> Esta funcao auxiliar foi fornecida no site da disciplina SCC0215012020.
 *  http://wiki.icmc.usp.br/index.php/SCC0215012020_Trabalhos_(cdac)
 *  >> Ela gera uma visualizacao do arquivo binario.
 */
void binarioNaTela(char *nomeArquivoBinario) {

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

/*  >> Esta funcao auxiliar foi fornecida no site da disciplina SCC0215012020.
 *  http://wiki.icmc.usp.br/index.php/SCC0215012020_Trabalhos_(cdac)
 *  >> Ela "limpa" uma string fornecida para o usuario.
 */
void trim(char *str) {

	/*
	*	Essa função arruma uma string de entrada "str".
	*	Manda pra ela uma string que tem '\r' e ela retorna sem.
	*	Ela remove do início e do fim da string todo tipo de espaçamento (\r, \n, \t, espaço, ...).
	*	Por exemplo:
	*
	*	char minhaString[] = "    \t TESTE  DE STRING COM BARRA R     \t  \r\n ";
	*	trim(minhaString);
	*	printf("[%s]", minhaString); // vai imprimir "[TESTE  DE STRING COM BARRA R]"
	*
	*/

	size_t len;
	char *p;

	// remove espaçamentos do fim
	for(len = strlen(str); len > 0 && isspace(str[len - 1]); len--);
	str[len] = '\0';
	
	// remove espaçamentos do começo
	for(p = str; *p != '\0' && isspace(*p); p++);
	len = strlen(p);
	
	memmove(str, p, sizeof(char) * (len + 1));
}

/*  >> Esta funcao auxiliar foi fornecida no site da disciplina SCC0215012020.
 *  http://wiki.icmc.usp.br/index.php/SCC0215012020_Trabalhos_(cdac)
 *  >> Ela remove as aspas de uma string.
 */
void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}



//******************************************************************************************************************//
//*                                    SEGUNDO TRABALHO PRATICO COMECA AQUI                                         //
//******************************************************************************************************************//
/*  >> Notas de atualizacao:                                                                                        //
 *      1) Algumas funcoes do codigo anterior foram alteradas (Trab. pratico 1);                                    //
 *          > transferData() agora recebe um PONTEIRO de REGISTRO_DADOS, ao contrario de antes, que era um parametro//
 *          > filterData() recebe tres novos parametros, desnecessarios no primeiro trabalho:                       //
 *              (o) 'o': um inteiro que indica a opcao escolhida                                                    //
 *              (o) 'travas': um vetor de inteiros -chave de busca-                                                 //
 *              (o) 'temp': um registro de dados de transporte de informacoes                                       //
 *          > scan_quote_string() foi transferido da funcao fornecida no site da disciplina para ca.                //
 *      2) As funcoes usadas nas seguintes, conectam para as funcoes criadas para o PRIMEIRO TRABALHO PRATICO.      //
 *          > Para facilitar, a funcao modificada e:                                                                //
 *              (o) filterData(): SWITCH/CASE no fim da funcao + Entradas novas de funcao                           //
 *              (o) As outras sao chamadas somente para cumprirem seu proposito inicial, determinado no PRIMEIRO TRAB.
 ********************************************************************************************************************/

/*  >> Esta funcao cria um registro de dados movel.
 *  Ela serve para carregar dados de busca/atualizacao entre funcoes.
 */
REGISTRO_DADOS *criaTemporario(){
    REGISTRO_DADOS *rd = (REGISTRO_DADOS*)malloc(sizeof(REGISTRO_DADOS));
    return rd;
}

/*  >> Esta funcao destroi o registro de dados movel.
 */
void destroiTemporario(REGISTRO_DADOS *rd){
    free(rd);
    return;
}

/*  >> Esta funcao cria um vetor que serve de 'chave de busca'.
 *  O primeiro espaco do vetor diz quantos parametros estao dentro dela. Por exemplo:
 *      int v[3];
 *      > v[0] = 2;  (quantidade de parametros)
 *      > v[1] = x;  (parametro 1)
 *      > v[2] = y;  (parametro 2)...
 */
int *criaTravas(int tam){
    int *vet = (int*)malloc(sizeof(int) * tam);
    vet[0] = tam;
    return vet;
}

/*  >> Esta funcao desaloca o vetor 'chave de busca'.
 */
void destroiTravas(int *vet){
    free(vet);
    return;
}

/*  >> Esta funcao usa o NOME DO CAMPO 'str', digitado pelo utilizador, para fazer a leitura do dado.
 *      Dependendo do campo, ele sera armazenado em um local diferente do registro de criterio de busca, 'crit'.
 *  >> RETORNA um INTEIRO que diz de qual campo foi preenchido.
 *      Por exemplo:
 *          )) NOME DO CAMPO 'str' = cidadeMae. Retorna 2.
 *          )) NOME DO CAMPO 'str' = idNascimento. Retorna 4.
 */
int preencheTemporario(REGISTRO_DADOS *crit, char *str){
    char *manipula;
    int ret = -1, aux = 0;

    /*  >> Esta funcao usa tres funcoes principais + funcoes de string.h:
     *          1) preencheTemporario(): Uso recursivo de si mesmo
     *          para preencher o mesmo registro de dados com dados
     *          de mae e filho;
     *          2) scan_quote_string(): Obtem os dados de entrada,
     *          removendo as aspas e trocando 'NULO' por vazio;
     *          3) atoi(): Para converter uma string numerica para
     *          um numero inteiro, podendo ser guardado no registro
     *          de dados 'crit'.
     * 
     *  >> Variaveis:
     *          1) manipula[50]: String que recebe as informacoes
     *          nao-filtradas, para serem filtradas e organizadas
     *          aqui;
     *          2) ret: Recebe qual vai ser o valor retornado. Ao
     *          inves de colocar varios returns em cada categoria,
     *          essa variavel recebe o valor do return no fim do
     *          codigo;
     *          3) aux: Converte imediatamente o valor da string
     *          'manipula' em um inteiro. Se nao houverem numeros,
     *          retorna zero.
     */

    manipula = (char*)malloc(sizeof(char)*50);

    //  Trecho a parte, que usa esse nome de string para preencher
    //  os quatro primeiros campos do registro 'crit'.
    if(!strcmp(str, "ComboMaeFilho")){
        preencheTemporario(crit, "cidadeMae");
        preencheTemporario(crit, "cidadeBebe");
        crit->tamCampoMae = strlen(crit->cidadeMae);
        crit->tamCampoBebe = strlen(crit->cidadeBebe);
        free(manipula);
        return 0;
    }

    //  Leitura da entrada e conversao no aux.
    scan_quote_string(manipula);
    aux = atoi(manipula);
    
    //  Dependendo do nome do campo, preenche um local diferente e
    //  atribui um valor para 'ret' diferente. Alguns casos que possam
    //  receber NULO como entrada, automaticamente converter o vazio
    //  para '-1' ou '\0$$...$'.
    if(!strcmp(str, "tamCampoMae")){
        crit->tamCampoMae = aux;
        ret = 0;

    } else if(!strcmp(str, "tamCampoBebe")){
        crit->tamCampoBebe = aux;
        ret = 1;

    } else if(!strcmp(str, "cidadeMae")){
        strcpy(crit->cidadeMae, manipula);
        crit->tamCampoMae = strlen(crit->cidadeMae);

        ret = 2;

    } else if(!strcmp(str, "cidadeBebe")){
        strcpy(crit->cidadeBebe, manipula);
        crit->tamCampoBebe = strlen(crit->cidadeBebe);
        ret = 3;

    } else if(!strcmp(str, "idNascimento")){
        if(aux == 0){
            crit->idNascimento = -1;
        } else {
            crit->idNascimento = aux;
        }
        ret = 4;

    } else if(!strcmp(str, "idadeMae")){
        if(aux == 0){
            crit->idadeMae = -1;
        } else {
            crit->idadeMae = aux;
        }
        ret = 5;

    } else if(!strcmp(str, "dataNascimento")){
        if(strlen(manipula) == 0){
            RAMTrash(11, manipula);                 // Enche a string com lixo
            strcpy(crit->dataNascimento, manipula);
            crit->dataNascimento[0] = '\0';         // Caso esteja vazio
        } else {
            strcpy(crit->dataNascimento, manipula);     // Caso contenha algum valor
        }
        ret = 6;

    } else if(!strcmp(str, "sexoBebe")){
        if(strlen(manipula) != 0){
            crit->sexoBebe = manipula[0];
        } else {
            crit->sexoBebe = '0';
        }
        ret = 7;

    } else if(!strcmp(str, "estadoMae")){
        if(strlen(manipula) == 0){
            RAMTrash(3, manipula);
            strcpy(crit->estadoMae, manipula);
            crit->estadoMae[0] = '\0';
        } else{
            strcpy(crit->estadoMae, manipula);
        }
        ret = 8;

    } else if(!strcmp(str, "estadoBebe")){
        if(strlen(manipula) == 0){
            RAMTrash(3, manipula);
            strcpy(crit->estadoBebe, manipula);
            crit->estadoBebe[0] = '\0';
        } else{
            strcpy(crit->estadoBebe, manipula);
        }
        ret = 9;

    }

    //  Libera a memoria alocada para a string.
    free(manipula);

    //  Fim.
    return ret;
}

/*  >> Esta funcao compara campos ESPECIFICOS de DOIS REGISTROS DE DADOS.
 *      O campo a ser verificado e determinado pela entrada 'campo'.
 *  >> RETORNA um INTEIRO 'ZERO' ou 'DIFERENTE DE ZERO'.
 *      Se retornar ZERO, significa que os campos sao iguais.
 *      Se retornar DIFERENTE DE ZERO, significa que os campos sao diferentes
 */
int comparaCampo(REGISTRO_DADOS A, REGISTRO_DADOS *B, int campo){
    int ret = 1;

    /*  >> Esta funcao usa funcoes de string.h
     *  >> Variavel:
     *          1) ret: Recebe qual vai ser o valor retornado. Ao
     *          inves de colocar varios returns em cada categoria,
     *          essa variavel recebe o valor do return no fim do
     *          codigo;
     */

    //  Esta e uma verificacao inicial antes de comparar os dados
    //  lidos. Basicamente, case este registro A seja considerado
    //  removido, o retorno imediato sera de diferenca, ou seja,
    //  'DIFERENTE DE ZERO'.
    if(A.tamCampoMae == -1){
        return ret;
    }

    //  Compara com base na entrada 'campo'. Caso nao haja um campo
    //  compativel, simplesmente retorna 'DIFERENTE DE ZERO'.
    switch(campo){
        //INT tamCampoMae
        case 0:
            if(A.tamCampoMae == B->tamCampoMae){
                ret = 0;
            }
        break;

        //INT tamCampoBebe
        case 1:
            if(A.tamCampoBebe == B->tamCampoBebe){
                ret = 0;
            }
        break;

        //STR cidadeMae
        case 2:
            ret = (strcmp(A.cidadeMae, B->cidadeMae));
        break;
        
        //STR cidadeBebe
        case 3:
            ret = (strcmp(A.cidadeBebe, B->cidadeBebe));
        break;
        
        //INT idNascimento
        case 4:
            if(A.idNascimento == B->idNascimento){
                ret = 0;
            }
        break;

        //INT idadeMae
        case 5:
            if(A.idadeMae == B->idadeMae){
                ret = 0;
            }
        break;

        //STR dataNascimento
        case 6:
            ret = (strcmp(A.dataNascimento, B->dataNascimento));
        break;

        //CHA sexoBebe
        case 7:
            if(A.sexoBebe == B->sexoBebe){
                ret = 0;
            }
        break;
        
        //STR estadoMae
        case 8:
            ret = (strcmp(A.estadoMae, B->estadoMae));
        break;
        
        //STR estadoBebe
        case 9:
            ret = (strcmp(A.estadoBebe, B->estadoBebe));
        break;
    }

    return ret;
}

/*  >> Esta funcao tem comportamento variado com base na opcao 'o'.
 *      Recebe um FILE 'source', que se trata do arquivo binario onde a busca sera feita.
 *      Recebe o cabecalho c, obtido nos procedimentos iniciais de abertura de arquivo.
 *  >> RETORNA um INTEIRO 'ZERO' ou 'DIFERENTE DE ZERO'.
 *      Se retornar ZERO, significa que a busca NAO TEVE SUCESSSO.
 *      Se retornar DIFERENTE DE ZERO, significa que a busca TEVE SUCESSO.
 */
int buscaCombinada(FILE *source, CABECALHO c, int o){
    int qt;
    REGISTRO_DADOS *temp;
    int *travas, notice = 0;
    char field[50];

    /*  >> Esta funcao usa duas funcoes principais + funcoes de string.h:
     *          1) preencheTemporario(): Usado para preencher o
     *          registro de dados auxiliar 'temp' com conteudos
     *          relevantes.
     *          2) filterData(): Processamento registro/registro
     *          do arquivo binario.
     * 
     *  >> Funcoes que alocam e desalocam variaveis na HEAP:
     *          1) criaTemporario() + destroiTemporario():
     *          2) criaTravas() + destroiTravas():
     * 
     *  >> Variaveis:
     *          1) qt: Dita o numero de campos que serao usados na
     *          pesquisa. Ele e recebido por uma entrada do usuario.
     *          2) temp: E um REGISTRO DE DADOS usado para guardar
     *          as informacoes de entrada do usuario.
     *          3) travas: VETOR DE INTEIROS que funciona como 'chave
     *          de busca'.
     *          4) notice: Variavel de retorno. Se, em algum momento,
     *          foi detectada uma interacao positiva da busca em achar
     *          um dado procurado para processamento, assume valor 1.
     */
    temp = criaTemporario();

    //  Separa caso para especifico da opcao 4. Guarda somente o RRN.
    if(o == 4){
        preencheTemporario(temp, "idNascimento");

    } else{
        //  Recebe a quantidade de campos que serao inseridos.
        scanf("%d", &qt);
        travas = criaTravas(qt + 1);

        //  Loop que recebe o nome do campo, guarda o valor referente,
        //  alem de preparar suas chaves na trava.
        for(int count = 1; count < qt + 1; count++){
            scanf("%s", field); 
            travas[count] = preencheTemporario(temp, field);
        }
    }

    //  Separa caso para especifico da opcao 7. A atualizacao ocorre
    //  num registro especifico apenas. Portanto, nao ha necessidade
    //  de percorrer o arquivo inteiro.
    if(o == 7){
        notice = updateData(source, travas, temp);
        //filterData(source, 0, travas, temp);

    } else {
        //  Percorre o arquivo inteiro usando os criterios de busca.
        //  Sera lido registro/registro em filterData(), ate o fim
        //  do arquivo, sempre notificando quando achar dados que
        //  que correspondam com a busca.
        for(int count = 0; count < c.RRNproxRegistro && c.numeroRegistrosInseridos != 0; count++){
            notice += filterData(source, o, travas, temp, 0);
        }
    }

    //  Finalizacao padrao da funcao, desalocando memoria.
    destroiTravas(travas);
    destroiTemporario(temp);

    return notice;
}

/*  >> Esta funcao so serve para inserir "-1" no registro que se busca remover.
 *  >> Depois, retorna o ponteiro para a posicao correta.
 */
void removeRegistroEstatico(FILE *f){
    int removed = -1;
    char trash[124];

    /*  >> Esta funcao usa funcoes de manuseio de arquivos.

     *  >> Variaveis:
     *          1) removed: Variavel que contem o valor a ser colocado
     *          para marcar como removido.
     *          2) trash[124]: Literalmente o que o nome indica. Le o
     *          resto do registro considerado removido para nada alem
     *          de ler.
     */

    //  Retorna ao primeiro inteiro do registro lido
    fseek(f, sizeof(char)*(-128), SEEK_CUR);
    //  Insere -1
    fwrite(&removed, sizeof(int), 1, f);
    //  Normalmente, aqui, deveria ser lido 124 bytes normalmente, ja
    //  que o que devia ter sido inserido, esta inserido. Contudo,
    //  ocorre um erro estranho que desconheco.
    //  O ponteiro 'f' vai para um lugar alem de 4 bytes momentaneamente,
    //  e creio ser porque trabalho em Windows. Se leio os 124 bytes,
    //  como o esperado, devia ter 'f' apontado para um novo registro.
    //  Isso, no entanto, nao acontece. Um meio que achei de dar a volta
    //  nisso e retornar 4 bytes usando fseek(), que sei que nao e uma
    //  boa pratica. Mas, por algum motivo, isso conserta o problema.
    fseek(f, -4, SEEK_CUR);

    //  Releitura /estranha/ de 128 bytes.
    fread(&trash, sizeof(char), 128, f);
    return;
}

/*  >> Esta funcao junta algumas funcoes ja criadas anteriormente para a funcao especifica de insercao.
        'f' e o ponteiro do arquivo binario.
 *  >> Nao possui valor de retorno.
 */
int insereRegistroBinario(FILE *f){
    REGISTRO_DADOS *temp;
    int idNascimento;
    temp = criaTemporario();

    /*  >> Esta funcao usa duas funcoes principais + funcoes de string.h:
     *          1) preencheTemporario(): Usado para preencher o
     *          registro de dados auxiliar 'temp' com conteudos
     *          relevantes.
     *          2) transferData(): Envio do registro a ser inserido
     *          no arquivo 'f'.
     * 
     *  >> Funcoes que alocam e desalocam variaveis na HEAP:
     *          1) criaTemporario() + destroiTemporario():
     * 
     *  >> Variaveis:
     *          1) temp: E um REGISTRO DE DADOS usado para guardar
     *          as informacoes de entrada do usuario.
     */

    //  Preenche o registro novo de dados usando a nova forma de entrada com scan_quote_string().
    preencheTemporario(temp, "ComboMaeFilho");
    preencheTemporario(temp, "idNascimento");
    preencheTemporario(temp, "idadeMae");
    preencheTemporario(temp, "dataNascimento");
    preencheTemporario(temp, "sexoBebe");
    preencheTemporario(temp, "estadoMae");
    preencheTemporario(temp, "estadoBebe");

    //  Escreve.
    transferData(f, temp);
    idNascimento = temp->idNascimento;
    //  Finalizacao padrao da funcao.
    destroiTemporario(temp);
    return idNascimento;
}

/*  >> Esta funcao iguala valores de um REGISTRO DE DADOS /A/ a OUTRO /B/.
        Ele iguala com base no campo entrado, variando de 0 a 9.
 *  >> Nao possui valor de retorno.
 */
void atualizaCampo(REGISTRO_DADOS A, REGISTRO_DADOS *B, int campo){
    switch(campo){
        //INT tamCampoMae
        case 0:
            B->tamCampoMae = A.tamCampoMae;
        break;

        //INT tamCampoBebe
        case 1:
            B->tamCampoBebe = A.tamCampoBebe;
        break;

        //STR cidadeMae
        case 2:
            strcpy(B->cidadeMae, A.cidadeMae);
            B->tamCampoMae = strlen(B->cidadeMae);
        break;
        
        //STR cidadeBebe
        case 3:
            strcpy(B->cidadeBebe, A.cidadeBebe);
            B->tamCampoBebe = strlen(B->cidadeBebe);
        break;
        
        //INT idNascimento
        case 4:
            B->idNascimento = A.idNascimento;
        break;

        //INT idadeMae
        case 5:
            B->idadeMae = A.idadeMae;
        break;

        //STR dataNascimento
        case 6:
            strcpy(B->dataNascimento, A.dataNascimento);
        break;

        //CHA sexoBebe
        case 7:
            B->sexoBebe = A.sexoBebe;
        break;
        
        //STR estadoMae
        case 8:
            strcpy(B->estadoMae, A.estadoMae);
        break;
        
        //STR estadoBebe
        case 9:
            strcpy(B->estadoBebe, A.estadoBebe);
        break;

        case 10:
            B->tamCampoMae = A.tamCampoMae;
            B->tamCampoBebe = A.tamCampoBebe;
            strcpy(B->cidadeMae, A.cidadeMae);
            B->tamCampoMae = strlen(B->cidadeMae);
            strcpy(B->cidadeBebe, A.cidadeBebe);
            B->tamCampoBebe = strlen(B->cidadeBebe);
            B->idNascimento = A.idNascimento;
            B->idadeMae = A.idadeMae;
            strcpy(B->dataNascimento, A.dataNascimento);
            B->sexoBebe = A.sexoBebe;
            strcpy(B->estadoMae, A.estadoMae);
            strcpy(B->estadoBebe, A.estadoBebe);
        break;
    }

    return;
}

//  Realiza um salto de RRN para BUSCA em especifico.
int buscaRRN(FILE *f, int RRN){
    skipToRRN(f, RRN);
    return filterData(f, 2, 0, 0, 0);
}

//  Salto de RRN
void skipToRRN(FILE *f, int RRN){
    fseek(f, (RRN+1)*128, SEEK_SET);
    return;
}

/*  >> Esta funcao INVERTE a 'chave de busca'. Considerando que a chave tem, no maximo,
 *      10 opcoes diferentes, variando de 0 a 9.
 *      Por exemplo:
 *          )) travas[0] = 2
 *          )) travas[1] = 7
 *          )) travas[2] = 9
 *      Nova travas:
 *          )) travas[0] = 7
 *          )) travas[1] = 1
 *          )) travas[2] = 3
 *          ...
 *          )) travas[7] = 8
 *  >> Retorna um PONTEIRO NOVO para substituir 'travas'.
 */
int *inverteTravas(int *travas){
    int tam = (10 - travas[0] + 1), *newTravas, found, ins = 1;

    /*  >> Esta funcao nao usa outras funcoes alem de malloc() e free().
     * 
     *  >> Variaveis:
     *          1) tam: E o novo tamanho das de 'travas'. Como o tamanho
     *          da chave de busca poderia variar, ela esta disponivel na
     *          declaracao da variavel.
     *          2) newTravas[]: Novo vetor inteiro de chaves de busca
     *          inversas.
     *          3) found: Localizador/Sinalizador
     *          4) ins: Variavel internalizada para controlar o progresso
     *          de preenchimento da nova chave.
     */
    newTravas = (int*)malloc(sizeof(int) * tam);

    //  Atribui tamanho no espaco zero.
    newTravas[0] = tam;

    //  Loop principal de geracao.
    for(int count = 0; count < 10; count++){
        found = 0;
        //  Percorre as travas e verifica se o numero 'count' pode ser
        //  inserido.
        for(int kount = 1; kount <= travas[0]; kount++){
            if(count == travas[kount]){
                found = 1;
            }
        }
        //  Caso possa, visto pela ausencia de sinalizacao por 'found',
        //  adiciona o valor e incrementa a posicao relativa da nova trava.
        if(found == 0){
            newTravas[ins] = count;
            ins++;
        }
    }

    //  Destroi chave antiga e retorna chave nova.
    free(travas);
    return newTravas;
}

/*  >> Esta funcao recebe o ponteiro de arquivo 'f', o vetor chave de busca 'travas' e o registro de dados temporario 'temp'.
 *      De modo geral, estando com o ponteiro 'f' no local correto por uso de skipToRRN(), ele processa somente o registro que lhe foi indicado.
 *      ERA PARA ESTAR FUNCIONANDO, MAS POR ALGUM MOTIVO, O FWRITE NAO ESCREVE NADA. Nao consegui entender o motivo, socorro :(
 *      Os parametros estao passados corretamente no registro 'temp'.
 *      O programa esta entrando em cada um dos 'ifs' apropriadamente, de acordo com o que foi pedido pelo usuario.
 *      Supostamente, os comandos de escrita tambem estao, confirmadamente, sendo acessados, mas nao fazem nenhuma mudanca.
 *      Tem comandos de debug comentados (e espalhados, infelizmente) no codigo caso queiram usar para verificar o codigo.
 *  >> RETORNA um INTEIRO que sinaliza se a atualizacao foi realizada com sucesso ou nao.
 *      )) 1: Atualizacao realizada com procedencia
 *      )) 0: Falha ao atualizar. Neste caso, o unico erro seria que o registro a atualizar esta removido.
 */
int updateData(FILE *f, int *travas, REGISTRO_DADOS *temp){
    REGISTRO_DADOS r;
    int pos = 0, size, yes = 0;
    char trash[128];

    /*  >> Esta funcao usa funcoes de manuseio de arquivos como principal

     *  >> Variaveis:
     *          1) r: REGISTRO DE DADOS auxiliar que extrai dados
     *          sem uso (ou com uso) para utilizacao.
     *          2) pos: Variavel auxiliar que controla a posicao atual
     *          do vetor chave de busca 'travas'.
     *          3) size: Variavel que guarda o tamanho maximo do vetor
     *          chave de busca para evitar overflow do vetor.
     *          4) yes: Funciona como uma unidade logica que pode variar
     *          entre zero e tres. Serve para escolher o tipo especifico
     *          de processamento dos campos de tamanho variavel do
     *          registro alterado.
     *          5) trash: Faz a leitura de lixo ($) e pode ler ate 128
     *          bytes de lixo, para casos onde a atualizacao nao e possivel.
     */

    //  Obtem o tamanho do vetor 'chave de busca'
    size = travas[pos];
    //printf("pos: %d\n", pos);   //faz o print da posicao atual do vetor de chaves
    pos++;
    //printf("pos: %d\n", pos);   //faz o print da posicao atual do vetor de chaves

    //  Faz a leitura dos campos variaveis para processamento posterior.
    //  Caso esteja identificado com -1, significa que se trata de um registro removido
    //  Assim, retorna o ponteiro de funcao para fora do registro e retorna 'zero', indicando que nao houve atualizacao.
    fread(&(r.tamCampoMae), sizeof(int), 1, f);
    if(r.tamCampoMae == -1){
        fread(&trash, sizeof(char), 124, f);
        return 0;
    }
    fread(&(r.tamCampoBebe), sizeof(int), 1, f);
    fread(&(r.cidadeMae), sizeof(char)*r.tamCampoMae, 1, f);
    fread(&(r.cidadeBebe), sizeof(char)*r.tamCampoBebe, 1, f);

    //  Retorna o ponteiro para o inicio do registro correspondente
    fseek(f, -(r.tamCampoMae + r.tamCampoBebe + 8), SEEK_CUR);

    //  Caso tamCampoMae (Atualizacao do tamCampoMae)
    if(travas[pos] == 2){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        //printf("tamCampoMae: %d\n", temp->tamCampoMae);
        fwrite(&(temp->tamCampoMae), sizeof(int), 1, f);
        yes+=1;
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.tamCampoMae), sizeof(int), 1, f);
    }
    //printf("pos: %d\n", pos);

    //  Caso tamCampoBebe (Atualizacao do tamCampoBebe)
    if(travas[pos] == 3){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        fwrite(&(temp->tamCampoBebe), sizeof(int), 1, f);
        yes+=2;
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.tamCampoBebe), sizeof(int), 1, f);
        //printf("oq foi lido do registro: %d\n", r.tamCampoBebe);
    }
    //printf("pos: %d\n", pos);

    //  Caso cidades (Atualizacao do tamCampoBebe)
    //  Trata os quatro casos possiveis de processamento de atualizacao.
    //      Caso 1: Atualiza 'cidadeMae', concatena 'cidadeBebe' antigo e pula bytes de lixo ($)
    //      Caso 2: Atualiza 'cidadeBebe' e pula bytes de lixo ($)
    //      Caso 3: Atualiza os dois campos e pula bytes de lixo ($)
    //      Caso 4: Nao faz atualizacoes e pula tudo
    if(yes > 0){
        if(yes == 1){
            //printf("ENTREI AQUI: 1111111\n", travas[pos]);
            fwrite(&(temp->cidadeMae), sizeof(char)*temp->tamCampoMae, 1, f);
            fwrite(&(r.cidadeBebe), sizeof(char)*r.tamCampoBebe, 1, f);
            fread(&trash, sizeof(char), 97 - (r.tamCampoBebe + temp->tamCampoMae), f);
        } else{
            if(yes == 2){
                //printf("ENTREI AQUI: 2222222\n", travas[pos]);
                fread(&(r.cidadeMae), sizeof(char)*r.tamCampoMae, 1, f);
                //printf("tamCampoBebe: %d\n", temp->tamCampoBebe);
                fwrite(&temp->cidadeBebe, sizeof(char)*temp->tamCampoBebe, 1, f);
                fread(&trash, sizeof(char), 97 - (temp->tamCampoBebe + r.tamCampoMae), f);
            } else{
                //printf("ENTREI AQUI: 3333333\n", travas[pos]);
                fwrite(&temp->cidadeMae, sizeof(char)*temp->tamCampoMae, 1, f);
                fwrite(&temp->cidadeBebe, sizeof(char)*temp->tamCampoBebe, 1, f);
                fread(&trash, sizeof(char), 97 - (temp->tamCampoBebe + temp->tamCampoMae), f);
            }
        }
    } else{
        //printf("ENTREI AQUI: 4444444\n", travas[pos]);
        fread(&trash, sizeof(char), 97 - (r.tamCampoBebe + r.tamCampoMae), f);
    }
    //printf("pos: %d\n", pos);

    //  Caso idNascimento (Atualizacao do idNascimento)
    if(travas[pos] == 4){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        fwrite(&(temp->idNascimento), sizeof(int), 1, f);
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.idNascimento), sizeof(int), 1, f);
    }
    //printf("pos: %d\n", pos);

    //  Caso idadeMae (Atualizacao do idadeMae)
    if(travas[pos] == 5){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        fwrite(&(temp->idadeMae), sizeof(int), 1, f);
        //printf("idade: %d", temp->idadeMae);
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.idadeMae), sizeof(int), 1, f);
    }
    //printf("pos: %d\n", pos);

    //  Caso dataNascimento (Atualizacao do dataNascimento)
    if(travas[pos] == 6){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        fwrite(&(temp->dataNascimento), sizeof(char)*10, 1, f);
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.dataNascimento), sizeof(char)*10, 1, f);
    }
    //printf("pos: %d\n", pos);
    
    //  Caso sexoBebe (Atualizacao do sexoBebe)
    if(travas[pos] == 7){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        fwrite(&(temp->sexoBebe), sizeof(char), 1, f);
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.sexoBebe), sizeof(char), 1, f);
    }
    //printf("pos: %d\n", pos);

    //  Caso estadoMae (Atualizacao do estadoMae)
    if(travas[pos] == 8){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        fwrite(&(temp->estadoMae), sizeof(char)*2, 1, f);
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.estadoMae), sizeof(char)*2, 1, f);
    }
    //printf("pos: %d\n", pos);

    //  Caso estadoBebe (Atualizacao do estadoBebe)
    if(travas[pos] == 9){
        //printf("ENTREI AQUI: %d\n", travas[pos]);   //relata qual fwrite foi acessado
        fwrite(&(temp->estadoBebe), sizeof(char)*2, 1, f);
        if(pos < size){
            pos++;
        }
    } else{
        fread(&(r.estadoBebe), sizeof(char)*2, 1, f);
    }
    //printf("pos: %d\n", pos);

    return 1;
}




/*  >> Esta funcao cria o header indice
 *  >> Retorna o ponteiro da alocacao
 */
INDICE_CABECALHO *criaHeaderIndice(){
    INDICE_CABECALHO *i = (INDICE_CABECALHO*)malloc(sizeof(INDICE_CABECALHO));

    //  Setup inicial
    i->status = '0';
    i->noRaiz = -1;
    i->nroNiveis = 0;
    i->proxRRN = 0;
    i->nroChaves = 0;

    return i;
}

/*  >> Esta funcao insere o header 'i' no arquivo 'b'
 *      Se for a primeira insercao de todas, vai inserir lixo tambem
 *      > Indicar 'firstTime' como 1.
 */
void insereHeaderIndice(FILE *b, INDICE_CABECALHO *i, int firstTime){

    //  Escrita padrao
    fseek(b, 0, SEEK_SET);
    fwrite(&(i->status), sizeof(char), 1, b);
    fwrite(&(i->noRaiz), sizeof(int), 1, b);
    fwrite(&(i->nroNiveis), sizeof(int), 1, b);
    fwrite(&(i->proxRRN), sizeof(int), 1, b);
    fwrite(&(i->nroChaves), sizeof(int), 1, b);

    //  Escrita condicional
    if(firstTime){
        completeTrash(b, sizeof(int)*4 + sizeof(char), 72);
    }

    return;
}

/*  >> Esta funcao faz free de 'i'
 */
void destroiHeaderIndice(INDICE_CABECALHO *i){
    //  Free de 'i'
    free(i);
    i = NULL;
    return;
}

/*  >> Esta funcao faz a leitura do header 'i' de um arquivo arvore 'b'
 *  >> Retorna 1, caso esteja instavel
 */
int lerHeaderIndice(FILE *b, INDICE_CABECALHO *i){
    int lixo[60];

    //  Verificacao e leitura de status
    fread(&(i->status), sizeof(char), 1, b);
    if(i->status == '0'){
        return 1;
    }
    fread(&i->noRaiz, sizeof(int), 1, b);
    fread(&i->nroNiveis, sizeof(int), 1, b);
    fread(&i->proxRRN, sizeof(int), 1, b);
    fread(&i->nroChaves, sizeof(int), 1, b);
    fread(&lixo, sizeof(char), 55, b);

    return 0;
}

/*  >> Esta funcao insere uma pagina de disco 'no' no arquivo 'b', no RRN 'RRN'.
 *      'NO_LISTA' se trata de uma estrutura de dados do tipo Lista Ordenada.
 *      Desse modo, a insercao da pagina se molda em torno dessa estrutura.
 */
void inserePagina(FILE *b, NO_LISTA *no, int RRN){
    CHAVE *ch;
    int amount = (ORDEM - 1) - no->N, count, empty = -1;
    int *P = (int*)malloc(sizeof(int) * ORDEM);

    //  Setup para deixar o vetor de P's com -1. Assim, eles sao escritos corretamente quando nao houverem chaves
    for(count = 0; count < ORDEM; count++){
        P[count] = -1;
    }

    //  Coloca ponteiro na posicao correta
    fseek(b, (RRN + 1) * sizeIndex, SEEK_SET);

    //  Escreve informacoes da lista
    fwrite(&(no->nivel), sizeof(int), 1, b);
    fwrite(&(no->N), sizeof(int), 1, b);

    //  Insere o primeiro ponteiro
    P[0] = no->P1;

    //  Insere o resto dos ponteiros P dentro do vetor, junto com a insercao as chaves que existem no arquivo.
    //  removeChave() aloca uma chave na memoria, portanto tem que ser removida no decorrer do loop
    for(count = 1; (ch = removeChave(no, 1)) != NULL; count++){
        fwrite(&(ch->C), sizeof(int), 1, b);
        fwrite(&(ch->PR), sizeof(int), 1, b);
        P[count] = ch->P;

        //  Tira aquela chave da memoria
        destroiChave(ch);
    }

    //  Tira a lista da memoria, agora que seus dados foram extraidos
    destroiLista(no);
    no = NULL;

    //  Escreve chaves caso haja alguma que estava vazia ( determinado por 'amount' -> [amount = (ORDEM - 1) - no->N] )
    for(count = 0; count < amount; count++){
        fwrite(&empty, sizeof(int), 1, b);
        fwrite(&empty, sizeof(int), 1, b);
    }

    //  Escreve os ponteiros inteiros P, usando aquele vetor
    for(count = 0; count < ORDEM; count++){
        fwrite(&P[count], sizeof(int), 1, b);
    }

    //  Fim
    return;
}

/*  >> Esta funcao extrai uma pagina de disco do arquivo 'b', no RRN 'RRN'.
 *      Tem um molde em torno do mesmo que a insercao.
 *  >> Retorna um ponteiro para a lista que a pagina cria.
 */
NO_LISTA *extraiPagina(FILE *b, int RRN){
    NO_LISTA *extract;
    CHAVE *ch;
    int nivel, n, C[ORDEM-1], PR[ORDEM-1], P[ORDEM];

    //  Coloca o ponteiro na posicao correta
    fseek(b, (RRN + 1) * sizeIndex, SEEK_SET);

    //  Le as duas primeiras informacoes do no ( crucial )
    fread(&nivel, sizeof(int), 1, b);
    fread(&n, sizeof(int), 1, b);

    //  Le todas as chaves e guarda em vetores temporarios
    for(int count = 0; count < (ORDEM - 1); count++){
        fread(&C[count], sizeof(int), 1, b);
        fread(&PR[count], sizeof(int), 1, b);
    }

    //  Le todos os ponteiros e guarda num vetor temporario, finalizando as leituras no arquivo
    for(int count = 0; count < ORDEM; count++){
        fread(&P[count], sizeof(int), 1, b);
    }

    //  Cria uma nova lista de chaves
    extract = criaLista(nivel, P[0]);

    //  Insere chaves relevantes ( != -1 , ou o numero de chaves existentes na lista, 'n' )
    for(int count = 0; count < n; count++){
        ch = criaChave(C[count], PR[count], P[count+1]);
        insereChave(extract, ch);
    }

    //  Print de teste, que exibe todas as chaves presentes no no 'extract'
    //printLista(extract);

    //  Fim
    return extract;
}

/*  >> Esta funcao se trata de ser um landing. Extrai um registro do arquivo de registros 'f'
 *      Caso nao exista registros, retorna '0'.
 *      Caso exista, chama buildTree() e usa o indice 'i' e o arquivo arvore 'b'.
 */
int interfaceArvore(FILE *f, FILE *b, INDICE_CABECALHO *i){
    REGISTRO_DADOS r;
    int track;

    //  Le um registro do arquivo 'f' e guarda em 'r'
    //  Usa a opcao 8 do switch, que transfere os dados do arquivo 'f' para o temporario 'r'
    track = filterData(f, 8, 0, &r, i);

    //  Caso o registro exista, realiza o loop
    if(track != 0){
        buildTree(f, b, i, r.idNascimento);
    }

    return(track);
}

/*  >> Esta funcao organiza alguns casos que nao servem para serem tratados recursivamente. Ou seja:
 *      > Inexistencia do noRaiz.
 *      > Percorrer ate um no folha.
 *      > Manter caminho de volta para splits.
 *  >> Depois de tudo isso, faz a chamada da insercao recursiva, que ja faz tratamento de split caso haja algum tipo de overflow.
 */
void buildTree(FILE *f, FILE *b, INDICE_CABECALHO *i, int key){
    NO_LISTA *in;
    STACK *s = criaStack();
    CHAVE *ch = criaChave(key, i->nroChaves, -1);
    int o;

    //  Incrementa o numero de chaves
    i->nroChaves++;

    if(i->noRaiz == -1){

        //  Cria lista, para combinar com os metodos de insercao criados
        in = criaLista(1, -1);
        insereChave(in, ch);

        //  Atualiza o no raiz atual e prepara qual e o RRN do proximo
        i->noRaiz = i->proxRRN;
        i->proxRRN++;

        //  Atualiza nro de niveis, agora que temos um no raiz
        i->nroNiveis++;

        //  Atualiza no arquivo, inserindo a lista criada
        //  A lista ja e destruida nesta insercao, entao nao precisa de free() depois
        inserePagina(b, in, i->noRaiz);

        //  Fim
        return;
    }

    //  Extrai pagina raiz e guarda o local ( RRN ) em 'o'
    in = extraiPagina(b, i->noRaiz);
    o = i->noRaiz;

    //  Enquanto a pagina nao estiver numa folha, continua buscando ate encontrar
    while(in->nivel != 1){
        //  Guarda o caminho feito ate o no correto
        pushStack(s, o);
        //  'o' recebe o RRN da proxima pagina
        o = filhoRRN(in, key);
        //  Refaz a extracao da pagina. Se a nova pagina continuar nao correspondendo, reinicia loop
        in = extraiPagina(b, o);
    }

    //  Agora que foi encontrado o no correto, seguir com a insercao da chave 'ch' em 'in'
    insertRecursive(b, i, in, ch, s, o);

    //  Fim da insercao, nao precisamos mais da stack
    destroiStack(s);
    return;
}

/*  >> Esta funcao recursiva faz a insercao de chaves 'ch' na pagina 'no' da arvore 'b'.
 *      O 'RRN' mantem rastro do RRN atual da insercao, e a stack 's' tem o caminho de volta para fazer os splits necessarios.
 *  >> Como os splits ocorrem de modo consistente com manter uma divisao "mais bem distribuidas o possivel", e ocorrem somente em overflows, tornam essa funcao possivel.
 */
void insertRecursive(FILE *b, INDICE_CABECALHO *i, NO_LISTA *no, CHAVE *ch, STACK *s, int RRN){
    NO_LISTA *new;
    CHAVE *promote;
    int RRN_NOVO, promoteLocale;

    //  Faz uma insercao padrao de uma chave na lista ordenada
    insereChave(no, ch);

    //  Se a lista passar do limite que a ordem impoe, comeca o procedimento de SPLIT
    if(no->N == ORDEM){
        if(ORDEM % 2 == 0){
            promoteLocale = (ORDEM / 2) + 1;
        } else{
            promoteLocale = (ORDEM + 1) / 2;
        }

        //  Removemos a chave que sera promovida
        promote = removeChave(no, promoteLocale);

        //  Criacao do no da esquerda
        new = criaLista(no->nivel, no->P1);
        for(int count = 1; count < promoteLocale; count++){
            insereChave(new, removeChave(no, 1));
        }
        inserePagina(b, new, RRN);

        //  Criacao do no da direita
        new = criaLista(no->nivel, promote->P);
        RRN_NOVO = i->proxRRN;
        promote->P = RRN_NOVO;
        i->proxRRN++;
        for(int count = promoteLocale; count < ORDEM; count++){
            insereChave(new, removeChave(no, 1));
        }
        inserePagina(b, new, RRN_NOVO);

        //  O split vai ser na raiz?
        if(RRN == i->noRaiz){
            //  Se sim

            //  Entao teremos um novo nivel
            i->nroNiveis++;
            new = criaLista(i->nroNiveis, i->noRaiz);

            //  Determinamos o novo RRN para o novo no, e atualizamos o noRaiz
            RRN_NOVO = i->proxRRN;
            i->proxRRN++;
            i->noRaiz = RRN_NOVO;

            //  No novo nivel, estara a chave sendo promovida
            insereChave(new, promote);
            inserePagina(b, new, RRN_NOVO);

        } else{
            //  Se nao
            
            //  Pedimos a stack para sabermos qual e o no anterior
            RRN_NOVO = popStack(s);
            new = extraiPagina(b, RRN_NOVO);

            //  Chamamos nossa funcao novamente, para fazer a insercao dessa chave no no anterior
            insertRecursive(b, i, new, promote, s, RRN_NOVO);

        }
        //  Destruimos a lista auxiliar
        destroiLista(no);

        //  Fim com split
        return;
    }

    //  Insere pagina atualizada com a nova chave
    inserePagina(b, no, RRN);

    //  Fim sem split
    return;
}


/*  >> Esta funcao faz a busca da chave 'busca' no arquivo arvore 'b'.
 *      Caso encontre, acessa a funcao 2 do primeiro trabalho em filterData() e faz a impressao dos dados.
 *  >> Retorna a quantidade de nos acessados. Caso nao encontre, retorna zero.
 */
int searchIndex(FILE *f, FILE *b, INDICE_CABECALHO *i, int busca){
    NO_LISTA *noAtual = extraiPagina(b, i->noRaiz);
    int o = i->noRaiz, desiredPR = 0, pathLength = 0;
    
    //  Enquanto nao encontrar o ultimo no possivel da arvore...
    while(o != -1){
        //  Incrementamos o tracker de comprimento de caminho
        pathLength++;

        //  Se seekEqualKeys() nos devolver...
        if((desiredPR = seekEqualKeys(noAtual, busca)) == -1){
            //  Que nao encontrou uma chave compativel

            //  'o' recebe o RRN de um filho adequado
            o = filhoRRN(noAtual, busca);
            destroiLista(noAtual);

            //  Se 'o' for...
            if(o != -1){
                //  Sinalizado como existente, prosseguimos para o proximo no
                noAtual = extraiPagina(b, o);
            }
            //  Sinalizado como o ultimo no possivel, entao nao encontramos a chave. Sairemos do looping.

        } else{
            //  Que encontrou uma chave compativel, entao imprimimos esse registro
            fseek(f, (desiredPR + 1) * 128, SEEK_SET);
            filterData(f, 2, 0, 0, 0);
            destroiLista(noAtual);

            //  E retornamos o tamanho do caminho feito
            return pathLength;
        }
    }

    //  Nao foi encontrado
    return 0;
}


/*  >> As 4 funcoes abaixo sao parte de um TAD Pilha
 *      criaStack(): Cria a estrutura da pilha. Devolve o ponteiro para ela.
 *      pushStack(): Insere um valor do tipo StackType para dentro da pilha.
 *      popStack(): Obtem o valor que esta no topo da pilha.
 *      destroiStack(): Remove a alocacao da stack na heap.
 */
STACK *criaStack(){
    STACK *s = (STACK*)malloc(sizeof(STACK));
    //  Inicializacoes da stack
    s->topo = NULL;
    s->tamanho = 0;
    return s;
}

void pushStack(STACK *s, StackType content){
    ST_POS *aux = (ST_POS*)malloc(sizeof(ST_POS));

    //Condicoes de erro
    if(aux == NULL){
        printf("Memoria insuficiente.\n");
        return;
    }
    aux->content = content;
    if(s == NULL){
        printf("Stack nao criada.\n");
        return;
    }

    //  Remaneja ponteiros para manter o valor inserido no topo
    aux->prox = s->topo;
    aux->content = content;

    s->topo = aux;
    s->tamanho++;

    return;
}

int popStack(STACK *s){
    ST_POS *aux;
    int value;

    //  Condicoes de erro
    if(s == NULL){
        printf("Stack nao criada.\n");
        return -1;
    }
    aux = s->topo;
    if(aux == NULL){
        //  Pilha vazia
        return -1;
    }

    //  Obtem o valor do topo da stack e reorganiza o topo da stack
    value = aux->content;
    s->topo = aux->prox;

    //  Exclui o no extraido
    free(aux);
    aux = NULL;

    //  Retorna o valor extraido
    return value;
}

void destroiStack(STACK *s){
    ST_POS *aux;

    //  Esvazia a stack
    while(s->topo != NULL){
        aux = s->topo;
        s->topo = aux->prox;
        free(aux);
        aux = NULL;
    }

    //  Exclui a stack
    free(s);
    s = NULL;

    //  Fim
    return;
}


/*  >> As 7 funcoes abaixo sao parte de um TAD Fila Ordenada
 *      criaLista(): Cria a estrutura da lista. Devolve o ponteiro para ela.
 *      criaChave(): Cria um no da lista. Devolve um ponteiro para ela. Recebe como parametros os conteudos do no.
 *      destroiLista(): Destroi a lista criada por completo, incluindo chaves contidas nela.
 *      destroiChave(): Destroi uma chave sem restricoes.
 *      insereChave(): Faz a insercao de uma chave existente 'ch', ordenadamente, na lista 'no'.
 *      removeChave(): Faz a remocao da chave numa posicao especifica 'pos' de uma lista 'no'. Retorna a chave removida sem links.
 *      printLista(): Funcao de debugging. Imprime todas as chaves de uma lista 'no'.
 */
NO_LISTA *criaLista(int nivel, int P1){
    NO_LISTA *new = (NO_LISTA*)malloc(sizeof(NO_LISTA));

    //  Inicializa a lista
    new->nivel = nivel;
    new->N = 0;
    new->P1 = P1;

    new->start = NULL;
    new->end = NULL;

    return new;
}

CHAVE *criaChave(int C, int PR, int P){
    CHAVE *new = (CHAVE*)malloc(sizeof(CHAVE));

    //  Inicializa uma chave padrao
    new->C = C;
    new->PR = PR;
    new->P = P;

    new->next = NULL;
    new->prev = NULL;

    return new;
}

void destroiLista(NO_LISTA *no){
    CHAVE *aux = no->start, *aux2;

    //  Esvazia a lista
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = NULL;
        aux = aux2;
    }

    //  Exclui a lista
    free(no);
    no = NULL;

    return;
}

void destroiChave(CHAVE *ch){
    //  Exclui a chave
    free(ch);
    ch = NULL;

    return;
}

void insereChave(NO_LISTA *no, CHAVE *ch){
    CHAVE *aux = no->start, *aux2;
    int flag = 0;

    //  A lista esta vazia
    if(aux == NULL){
        no->start = ch;
        no->end = ch;
        no->N++;
        return;
    }
    //  Insercao no primeiro ( mas nao e a primeira insercao )
    if(ch->C < aux->C){
        no->start = ch;
        ch->next = aux;
        aux->prev = ch;
        no->N++;
        return;
    }

    //  Loop que posiciona os ponteiros auxiliares nos locais corretos, para que a insercao mantenha a lista ordenada
    while(flag != 1){
        //  A insercao vai ser feita no meio? O ponteiro esta no lugar certo?
        if(ch->C < aux->C){
            //  Sim, entao ordenar os ponteiros para esta configuracao
            aux2 = aux->prev;
            aux->prev = ch;
            ch->prev = aux2;
            ch->next = aux;
            aux2->next = ch;

            flag = 1;

        } else{
            //  Nao. A insercao vai ser feita no final?
            if(aux->next == NULL){
                //  Sim, entao ordenar os ponteiros para esta configuracao
                aux->next = ch;
                ch->prev = aux;
                no->end = ch;
                flag = 1;
            } else{
                //  Nao. Estamos na chave errada. Vamos para a proxima
                aux = aux->next;
            }
        }
    }

    //  Enfim, incrementa o numero de chaves nesta lista
    no->N++;
    return;
}

CHAVE *removeChave(NO_LISTA *no, int pos){
    CHAVE *search, *aux, *aux2;

    //  Casos possiveis de erro
    if(no == NULL || no->start == NULL){
        return NULL;
    } else{
        search = no->start;
    }
    //  O local pedido para a remocao nao existe?
    for(int count = 1; count < pos; count++){
        search = search->next;
        if(search == NULL){
            //  Nao existe
            return NULL;
        }
    }

    //  Existe e o ponteiro esta no local certo. Configurar os ponteiros para nao quebrar a lista
    aux = search->prev;
    if(aux != NULL){
        aux->next = search->next;
    } else{
        // primeiro da lista
        no->start = search->next;
    }
    if(search->next != NULL){
        aux2 = search->next;
        aux2->prev = aux;
    } else{
        no->end = aux;
    }

    //  Remove links da chave que esta sendo entregue
    search->next = NULL;
    search->prev = NULL;

    //  Conta que a chave foi removida
    no->N--;

    return search;
}

void printLista(NO_LISTA *no){
    CHAVE *aux;

    //  Verifica se nao foi entregue algo inexistente
    if(no == NULL){
        return;
    }
    aux = no->start;

    printf("No. de Chaves: %d\n", no->N);

    //  Imprime enquanto nao chegar no fim da lista
    while(aux != NULL){
        printf("%d ", aux->C);
        aux = aux->next;
    }
    if(no->start != NULL){
        printf("\n\n");
    }

    return;
}


/*  >> A seguinte funcao retorna o RRN de um filho compativel com as restricoes. Compara chaves na lista 'no' com o valor 'value'.
 */
int filhoRRN(NO_LISTA *no, int value){
    CHAVE *aux;
    int alvoRRN = -1;

    //  Recebe a primeira chave da lista
    aux = no->start;

    //  Verificamos primeiro se a chave nao e menor que todas da lista
    if(value < aux->C){
        //  Neste caso, entregamos o P da estrutura da lista, nao da chave
        return no->P1;
    }
    //  Looping que procura o local correto da chave e salva em 'alvoRRN'
    while(aux != NULL){
        if(value > aux->C){
            alvoRRN = aux->P;
        }
        aux = aux->next;
    }

    //  Retorna esse local
    return alvoRRN;
}

/*  >> A seguinte funcao busca saber se a chave buscada 'value' esta no no 'no' atual da arvore.
 *      Se nao estiver, envia um sinal '-1', avisando para continuar a busca numa proxima chave.
 */
int seekEqualKeys(NO_LISTA *no, int value){
    CHAVE *aux;

    aux = no->start;

    //  Percorre a lista inteira buscando compatibilidade
    while(aux != NULL){
        if(value == aux->C){
            //  Encontrou
            return aux->PR;
        }
        aux = aux->next;
    }

    //  Nao encontrou
    return -1;
}