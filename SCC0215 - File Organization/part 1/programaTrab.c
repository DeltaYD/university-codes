
//Nome: Gustavo Akira Hirakawa
//NUSP: 11381768

#include <stdio.h>
#include <stdlib.h>
#include "funcoesFile.c"

int main(void){
    FILE *source, *destiny;
    CABECALHO c;
    char s[50], d[50], quit[128];
    int o;

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
     */

    // BLOCO 1: Leitura inicial de opcao.
    // Opcao 1: Escrita de CSV para BINARIO
    // Opcao 2: Leitura do BINARIO e IMPRIMIR
    scanf("%d", &o);
    switch(o){
        case 1:
            // BLOCO 2: Obtencao dos nomes dos arquivos
            scanf("%s", s);
            scanf("%s", d);

            // BLOCO 3: Limpeza do nome dos arquivos
            trim(s);
            trim(d);

            // BLOCO 4: Abertura do arquivo 's' e criacao do arquivo 'd'
            if((source = fopen(s, "r")) == NULL){
                printf("Falha no carregamento do arquivo.\n");
                return 0;
            }
            if((destiny = fopen(d, "wb")) == NULL){
                printf("Falha no carregamento do arquivo.\n");
                fclose(source);
                return 0;
            }

            // BLOCO 5: Inicializacao do cabecalho + Insercao + Preenchimento com lixo ate o byte 128.
            c.status = '0';
            c.RRNproxRegistro = 0;
            c.numeroRegistrosInseridos = 0;
            c.numeroRegistrosRemovidos = 0;
            c.numeroRegistrosAtualizados = 0;
            insereCabecalho(destiny, c);
            completeTrash(destiny, sizeof(int)*4 + sizeof(char), 128);

            // BLOCO 6: Verificacao se o arquivo esta vazio
            if(fgets(quit, 129, source) != NULL){
                
                // BLOCO 7: Loop de processamento registro/registro.
                while(lineDSV(source, destiny) != 1){

                    //BLOCO 8: Atualizacoes do cabecalho
                    c.RRNproxRegistro++;
                    c.numeroRegistrosInseridos++;
                }
            }

            // BLOCO 9: Finalizacao do arquivo + Fechamento
            c.status = '1';
            fseek(destiny, 0, SEEK_SET);
            insereCabecalho(destiny, c);

            fclose(source);
            fclose(destiny);

            // BLOCO 10: Impressao do binario gerado na tela
            binarioNaTela(d);
        break;


        case 2:
            // BLOCO 2: Obtencao do nome do arquivo + Limpeza
            scanf("%s", s);
            trim(s);

            // BLOCO 3: Abertura do arquivo 's'
            if((source = fopen(s, "rb")) == NULL){
                printf("Falha no processamento do arquivo.\n");
                return 0;
            }

            // BLOCO 4: Verifica a estabilidade do arquivo
            fread(&c.status, sizeof(char), 1, source);
            if(c.status == '0'){
                fclose(source);
                printf("Falha no processamento do arquivo.\n");
                return 0;
            }

            // BLOCO 5: Faz a leitura e armazenamento do registro de cabecalho para usos posteriores
            fread(&(c.RRNproxRegistro), sizeof(int), 1, source);
            fread(&(c.numeroRegistrosInseridos), sizeof(int), 1, source);
            fread(&(c.numeroRegistrosRemovidos), sizeof(int), 1, source);
            fread(&(c.numeroRegistrosAtualizados), sizeof(int), 1, source);

            // BLOCO 6: Pula lixo de tamanho fixo (111)
            fseek(source, 111, SEEK_CUR);

            // BLOCO 7: Comeca a impressao linha/linha
            for(int count = 0; count < c.numeroRegistrosInseridos; count++){
                filterData(source);
            }

            // BLOCO 8: Fechamento do arquivo
            fclose(source);
        break;

    }

    //Fim do programa sem erros
    return 0;
}