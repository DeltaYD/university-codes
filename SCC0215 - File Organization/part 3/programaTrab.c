
//Nome: Gustavo Akira Hirakawa
//NUSP: 11381768

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFile.h"

int main(void){
    FILE *source, *destiny, *index;
    CABECALHO c;
    INDICE_CABECALHO *i;
    char s[50], d[50], in[50], quit[128], skip[111];
    int o, n = 0, RRN = 0, chave;

    /*  >> Funcoes usadas aqui:
     *          1) trim(): Limpa uma string para remover
     *          excessos, que sao inuteis para a abertura
     *          do arquivo.
     *          2) insereCabecalho(): Insere o cabecalho
     *          gerado na main().
     *          3) completeTrash(): Cria lixo ate o byte
     *          offset 128.
     *          4) lineDSV(): Local de processamento geral
     *          de uma linha inteira do arquivo CSV.
     *          5) binarioNaTela(): Imprime o arquivo
     *          binario gerado na tela.
     *          6) filterData(): Processamento registro/
     *          registro do arquivo binario.
     *          7) buscaCombinada(): Processa uma busca
     *          usando o nome dos campos.
     *          8) insereRegistroBinario(): Faz a insercao
     *          de um registro novo, usando o arquivo binario.
     *     NEW  9) criaHeaderIndice(): Cria o header da arvore
     *          na heap.
     *     NEW 10) insereHeaderIndice(): Escreve o header no
     *          arquivo indicado.
     *     NEW 11) interfaceArvore(): Local de landing para comecar
     *          a geracao da Arvore_B. Em suma, faz tudo.
     *     NEW 12) destroiHeaderIndice(): Tira a memoria alocada.
     *     NEW 13) lerHeaderIndice(): Faz a leitura do header
     *          de um arquivo que ja contenha ele.
     *     NEW 14) searchIndex(): Faz a busca da chave desejada
     *          na arvore. Imprime usando a configuracao dos
     *          trabalhos iniciais. Retorna a quantidade de nos
     *          acessados durante a busca.
     *     NEW 13) buildTree(): Uma das funcoes mais internas do
     *          codigo, usado por interfaceArvore(). Essencialmente,
     *          faz a insercao de novos nos e e recursiva.
     *      
     * 
     *  >> Variaveis:
     *          1) s: Nome do arquivo SOURCE/FONTE
     *          2) d: Nome do arquivo DESTINY/DESTINO
     *          3) quit: String de teste da primeira linha.
     *          Como a primeira linha e de teste, a leitura
     *          sem proposito serve para verificar se o
     *          arquivo 's' possui algum conteudo.
     *          4) o: Refere-se a opcao do usuario de
     *          converter um binario ou ler um.
     *          5) n: Indica a quantidade de operacoes que vao
     *          ser feitas de busca, insercao, remocao ou atua-
     *          lizacao.
     *          6) RRN: Recebe uma entrada que se trata do
     *          RRN onde se encontra a informacao buscada.
     *          7) skip: Usado para substituir um fseek()
     *          do TRABALHO PRATICO 1 por um fread().
     *     NEW  8) in: Nome do arquivo INDEX/ARVORE_B.
     *     NEW  9) i: Cabecalho da arvore B.
     * ESQUECI 10) c: Armazena o cabecalho do arquivo de registros.
     *     NEW 11) chave: Variavel extra para receber o idNascimen-
     *          to de uma chave sendo inserida no arquivo de regis-
     *          tros.
     */

    //  BLOCO 1: Leitura inicial de opcao.
    //      Opcao 1: Escrita de CSV para BINARIO
    //      Opcao 2: Leitura do BINARIO e IMPRIMIR
    //      Opcao 3: Busca combinada
    //      Opcao 4: Busca por RRN
    //      Opcao 5: Remocao de registros
    //      Opcao 6: Insercao de registros
    //      Opcao 7: Atualizacao de registros
    // NEW  Opcao 8: Criar Arvore B
    // NEW  Opcao 9: Recuperacao de dados usando a arvore
    // NEW Opcao 10: Extensao da insercao de registros atualizando a arvore
    scanf("%d", &o);

    //Leitura de inicializações padrão na leitura de binarios.
    if(o > 1){
        scanf("%s", s);
        trim(s);

        //  Abertura do arquivo 's'
        if((source = fopen(s, "rb+")) == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        //  Verifica a estabilidade do arquivo
        fread(&c.status, sizeof(char), 1, source);
        if(c.status == '0'){
            fclose(source);
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        //  Faz a leitura e armazenamento do registro de cabecalho para usos posteriores
        fread(&(c.RRNproxRegistro), sizeof(int), 1, source);
        fread(&(c.numeroRegistrosInseridos), sizeof(int), 1, source);
        fread(&(c.numeroRegistrosRemovidos), sizeof(int), 1, source);
        fread(&(c.numeroRegistrosAtualizados), sizeof(int), 1, source);
        fread(&skip, sizeof(char), 111, source);
    }

    switch(o){
        case 1:
            //  BLOCO 2: Obtencao dos nomes dos arquivos
            scanf("%s", s);
            scanf("%s", d);

            //  BLOCO 3: Limpeza do nome dos arquivos
            trim(s);
            trim(d);

            //  BLOCO 4: Abertura do arquivo 's' e criacao do arquivo 'd'
            if((source = fopen(s, "r")) == NULL){
                printf("Falha no carregamento do arquivo.\n");
                return 0;
            }
            if((destiny = fopen(d, "wb")) == NULL){
                printf("Falha no carregamento do arquivo.\n");
                fclose(source);
                return 0;
            }

            //  BLOCO 5: Inicializacao do cabecalho + Insercao + Preenchimento com lixo ate o byte 128.
            c.status = '0';
            c.RRNproxRegistro = 0;
            c.numeroRegistrosInseridos = 0;
            c.numeroRegistrosRemovidos = 0;
            c.numeroRegistrosAtualizados = 0;
            insereCabecalho(destiny, c);
            completeTrash(destiny, sizeof(int)*4 + sizeof(char), 128);

            //  BLOCO 6: Verificacao se o arquivo esta vazio
            if(fgets(quit, 128, source) != NULL){
                
                //  BLOCO 7: Loop de processamento registro/registro.
                while(lineDSV(source, destiny) != 1){

                    //  BLOCO 8: Atualizacoes do cabecalho
                    c.RRNproxRegistro++;
                    c.numeroRegistrosInseridos++;
                }
            }

            //  BLOCO 9: Finalizacao do arquivo + Fechamento
            c.status = '1';

            fseek(destiny, 0, SEEK_SET);
            insereCabecalho(destiny, c);

            fclose(source);
            fclose(destiny);

            //  BLOCO 10: Impressao do binario gerado na tela
            binarioNaTela(d);
        break;



        case 2:
            n = 0;
            //  BLOCO 2: Comeca a impressao linha/linha
            for(int count = 0; count < c.numeroRegistrosInseridos; count++){
                n = filterData(source, o, 0, 0, 0);
            }
            if(n == 0){
                printf("Registro Inexistente.\n");
            }
            //  BLOCO 3: Fechamento do arquivo
            fclose(source);
        break;



        case 3:
            //  BLOCO 2: Faz a busca usando buscaCombinada(). Avisa se nao encontrar nada.
            if(buscaCombinada(source, c, o) == 0){
                printf("Registro Inexistente.");
            }
            //  BLOCO 3: Fechamento do arquivo
            fclose(source);
        break;



        case 4:
            //  BLOCO 2: Faz a busca usando saltos de RRN.
            scanf("%d", &RRN);
            if(RRN <= c.numeroRegistrosInseridos){
                if(buscaRRN(source, RRN) == 0){
                    printf("Registro Inexistente.");
                }
            } else{
                printf("Registro Inexistente.");
            }
            //  BLOCO 3: Fechamento do arquivo
            fclose(source);
        break;



        case 5:
            //  BLOCO 2: Recebe o numero de remocoes que serao feitas.
            scanf("%d", &n);

            for(int count = 0; count < n; count++){
                //  BLOCO 4: Faz a busca usando buscaCombinada(). Avisa se nao encontrar nada.
                //  Caso tenha encontrado, atualiza o cabecalho c.
                if(!buscaCombinada(source, c, o) == 0){
                    c.numeroRegistrosRemovidos++;
                    c.numeroRegistrosInseridos--;
                }
                //  BLOCO 5: Retorna para o inicio da arquivo para realizar OUTRA busca por parametros.
                fseek(source, 128, SEEK_SET);
            }

            //  BLOCO 6: Retorna ao inicio do arquivo e reinsere o cabecalho, atualizando para estar estavel.
            fseek(source, 0, SEEK_SET);
            c.status = '1';
            insereCabecalho(source, c);

            //  BLOCO 7: Fechamento do arquivo.
            fclose(source);
            binarioNaTela(s);
        break;



        case 6:
            //  BLOCO 2: Atualiza o arquivo para dizer que esta instavel.
            fseek(source, 0, SEEK_SET);
            c.status = '0';
            insereCabecalho(source, c);

            //  BLOCO 3: Salta diretamente para o fim do arquivo.
            fseek(source, 0, SEEK_END);

            //  BLOCO 4: Recebe o numero de insercoes que serao feitas.
            scanf("%d", &n);

            //  BLOCO 5: insere 'n' registros e atualiza o cabecalho na RAM.
            for(int count = 0; count < n; count++){
                insereRegistroBinario(source);
                c.numeroRegistrosInseridos++;
                c.RRNproxRegistro++;
            }

            //  BLOCO 6: Retorna ao inicio do arquivo e reinsere o cabecalho, atualizando para estar estavel.
            c.status = '1';
            fseek(source, 0, SEEK_SET);
            insereCabecalho(source, c);

            //  BLOCO 7: Fechamento do arquivo.
            fclose(source);
            binarioNaTela(s);
        break;



        case 7:
            //  BLOCO 2: Atualiza o arquivo para dizer que esta instavel.
            c.status = '0';
            fseek(source, 0, SEEK_SET);
            insereCabecalho(source, c);
            fread(&skip, sizeof(char), 111, source);

            //  BLOCO 4: Recebe o numero de insercoes que serao feitas.
            scanf("%d", &n);

            for(int count = 0; count < n; count++){
                //  BLOCO 5: Recebe o RRN exato de onde a atualizacao deve ocorrer e salta para la.
                scanf("%d", &RRN);
                skipToRRN(source, RRN);
                
                //  BLOCO 6: Processamento do registrador e atualizacao do cabecalho.
                if(buscaCombinada(source, c, o)){
                    c.numeroRegistrosAtualizados++;
                }
            }
            //  BLOCO 7: Retorna ao inicio do arquivo e reinsere o cabecalho, atualizando para estar estavel.
            fseek(source, 0, SEEK_SET);
            c.status = '1';
            insereCabecalho(source, c);

            //  BLOCO 8: Fechamento do arquivo.
            fclose(source);
            binarioNaTela(s);
        break;



        case 8:
            //  Recebe o nome do arquivo de index, onde vai ser escrito
            scanf("%s", d);
            trim(d);

            //  Abertura do arquivo 'd'
            if((destiny = fopen(d, "wb+")) == NULL){
                printf("Falha no processamento do arquivo.\n");
                fclose(source);
                return 0;
            }

            //  Cria o cabecalho da arvore b
            i = criaHeaderIndice();
            insereHeaderIndice(destiny, i, 1);

            //  Looping principal, que cria uma chave diferente para cada no.
            for(int count = 0; count < c.numeroRegistrosInseridos; count++){
                n = interfaceArvore(source, destiny, i);
            }

            //  Reinsere o cabecalho com status estavel
            i->status = '1';
            fseek(destiny, 0, SEEK_SET);
            insereHeaderIndice(destiny, i, 0);
            destroiHeaderIndice(i);

            //  Fechamento dos arquivos e uso do binarioNaTela()
            fclose(source);
            fclose(destiny);
            binarioNaTela(d);

        break;
        
        case 9:
            //  Recebe o nome do arquivo index, que vai ser lido
            scanf("%s", in);
            trim(in);

            //  Abertura do arquivo 'in'
            if((index = fopen(in, "rb")) == NULL){
                printf("Falha no processamento do arquivo.\n");
                fclose(source);
                return 0;
            }

            //  Faz a leitura do header
            i = criaHeaderIndice();
            if(lerHeaderIndice(index, i)){
                printf("Falha no processamento do arquivo.\n");
                fclose(index);
                fclose(source);
                return 0;
            }

            //  Verifica se o tipo de chave esta correto
            scanf("%s", d);
            if(strcmp(d, "idNascimento") != 0){
                printf("Falha no processamento do arquivo.\n");
                fclose(index);
                fclose(source);
                return 0;
            }

            //  Obtem o 'RRN' (na verdade, obtem a chave que esta buscando)
            scanf("%d", &RRN);

            //  Chama a funcao de looping de busca. Retorna, em 'n', a quantidade de nos acessados
            if((n = searchIndex(source, index, i, RRN)) != 0){
                printf("Quantidade de paginas da arvore-B acessadas: %d\n", n);
            } else{
                printf("Registro inexistente.\n");
            }
            
            //  Finalizacao dos processos
            destroiHeaderIndice(i);
            fclose(source);
            fclose(index);
        break;

        case 10:
            //  Recebe o nome do arquivo index, que vai ser processado
            scanf("%s", in);
            trim(in);

            //  Abertura do arquivo 'in'
            if((index = fopen(in, "rb+")) == NULL){
                printf("Falha no processamento do arquivo.\n");
                return 0;
            }

            //  Faz a leitura do header
            i = criaHeaderIndice();
            if(lerHeaderIndice(index, i)){
                printf("Falha no processamento do arquivo.\n");
                fclose(index);
                fclose(source);
                return 0;
            }

            //  Atualiza ambos os cabecalhos para dizer que estao instaveis
            fseek(source, 0, SEEK_SET);
            c.status = '0';
            insereCabecalho(source, c);
            i->status = '0';
            insereHeaderIndice(index, i, 0);

            //  Salta o arquivo de registros para o fim para a insercao
            fseek(source, 0, SEEK_END);

            //  Recebe o numero de insercoes que vao ser feitas
            scanf("%d", &n);

            //  Faz o mesmo procedimento de insercao que a funcao 6, mas agora atualiza a arvore
            for(int count = 0; count < n; count++){
                chave = insereRegistroBinario(source);
                c.numeroRegistrosInseridos++;
                c.RRNproxRegistro++;
                buildTree(source, index, i, chave);
            }

            //  Atualiza os arquivos para estavel
            c.status = '1';
            fseek(source, 0, SEEK_SET);
            insereCabecalho(source, c);
            i->status = '1';
            insereHeaderIndice(index, i, 0);

            //  Finalizacao
            fclose(source);
            fclose(index);
            binarioNaTela(in);
        break;
    }

    return 0;
}