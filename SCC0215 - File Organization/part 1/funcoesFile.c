
//Nome: Gustavo Akira Hirakawa
//NUSP: 11381768

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesFile.h"

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
    transferData(destiny, r);

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
void transferData(FILE *f, REGISTRO_DADOS r){

    /* >> Esta funcao usa uma funcao principal + fwrite():
                1) completeTrash(): Carrega um arquivo
                com lixo ate determinado byte offset
                referente ao REGISTRO! Nao ao arquivo.
     */

    // BLOCO 1: Escrita do tamanho das strings variaveis
    fwrite(&(r.tamCampoMae), sizeof(int), 1, f);
    fwrite(&(r.tamCampoBebe), sizeof(int), 1, f);

    // BLOCO 2: Escrita das strings variaveis (somente se existirem)
    if(r.tamCampoMae != 0){
        fwrite(&(r.cidadeMae), sizeof(char) * r.tamCampoMae, 1, f);
    }
    if(r.tamCampoBebe != 0){
        fwrite(&(r.cidadeBebe), sizeof(char) * r.tamCampoBebe, 1, f);
    }

    // BLOCO 3: Preenchimento de lixo ate o byte 104, continuando do 105
    completeTrash(f, 8 + r.tamCampoMae + r.tamCampoBebe, 105);

    // BLOCO 4: Escrita dos segmentos de tamanho fixo
    fwrite(&(r.idNascimento), sizeof(int), 1, f);
    fwrite(&(r.idadeMae), sizeof(int), 1, f);
    fwrite(&(r.dataNascimento), sizeof(char) * 10, 1, f);
    fwrite(&(r.sexoBebe), sizeof(char) * 1, 1, f);
    fwrite(&(r.estadoMae), sizeof(char) * 2, 1, f);
    fwrite(&(r.estadoBebe), sizeof(char) * 2, 1, f);

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
 */
void filterData(FILE *f){
    REGISTRO_DADOS r;

    // BLOCO 1: Recebimento do tamanho de campos variaveis
    fread(&(r.tamCampoMae), sizeof(int), 1, f);
    fread(&(r.tamCampoBebe), sizeof(int), 1, f);

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
    fseek(f, 97 - (r.tamCampoBebe + r.tamCampoMae), SEEK_CUR);

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

    // Impressao dos dados obtidos
    printBabyData(r, r.sexoBebe);
    
    return;
}

/* >> Esta funcao usa os parametros obtidos em filterData()
 * para imprimir exatamente o que foi pedido.
 * >> Ela recebe o registro de dados 'r' com as informacoes
 * ja filtradas e simplesmente imprime.
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