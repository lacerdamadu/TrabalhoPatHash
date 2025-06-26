#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"

#define Aux1 2000
#define Aux2 701

void Menu(){
    int Peso[TamPalavra];
    SetPesos(Peso);    
    Hash TabelaHah[TamHash];;
    SetTabelaHash(TabelaHah,TamHash);

    printf("Tamo no processo\n");
    EntradaDeArquivo(TabelaHah,Peso);
    TabelaHashImprime(TabelaHah,TamHash);

    TabelaHashInvertido(TabelaHah,TamHash);
}

void EntradaDeArquivo(Hash* TabelaHash,int* Peso){
    char DocEntrada[30];
    
    // //Para eu nao digitar toda vez para rodar depois descomentar
    // strcpy(DocEntrada,"entrada.txt");

    // Pede o nome do arquivo de entrada
    printf("Digite o Documento de entrada:");
    if(fgets(DocEntrada,sizeof(DocEntrada),stdin) == NULL){
        printf("erro em abrir o arquivo %s",DocEntrada);
        return;
    }

    // Remove o \n do final 
    DocEntrada[strcspn(DocEntrada,"\n")] = '\0';

    //Abre o arquivo digitado
    FILE *ArquivoEntrada = fopen(DocEntrada,"r");

    printf("Documento %s abrido\n",DocEntrada);

    if (ArquivoEntrada == NULL){
        perror("Erro em abrir o arquivo");
        return;
    }

    char NChar[TamPalavra];
    int N;

    //Recebe N e tranforma em inteiro
    fgets(NChar,sizeof(NChar),ArquivoEntrada);
    N = atoi(NChar);

    // Fica repetindo passando por cada documento 
    for (int i = 1; i <= N; i++){
        char caminho[TamLinha];
        strcpy(caminho,"PastaArquivos/"); //Pasta onde vai estar os arquivos do POC

        char ArquivosLinha[TamLinha];
        fgets(ArquivosLinha,sizeof(ArquivosLinha),ArquivoEntrada);// Pega o nome do arquivo 

        ArquivosLinha[strcspn(ArquivosLinha,"\n")] = '\0'; //Retira o "\n" e coloca '\0'

        strcat(caminho,ArquivosLinha);//Junta o caminho e o arquivo criando onde o arquivo esta

        FILE *ArquivoPOC = fopen(caminho,"r");// Abre o arquivo do POC

        if (ArquivoPOC == NULL){
            perror("Erro em o POC");
            return;
        }
        
        char linha[TamLinha];

        while (fgets(linha,sizeof(linha),ArquivoPOC)){// Fica pecorendo o documento ate acabar e quardando a linha do txt
            linha[strcspn(linha,"\n")] ='\0'; // retira o "\n"

            char *palavra = strtok(linha, " ");//Separa a linha por espacos     
            while (palavra != NULL){//pecorre a linha mudando a palavra                 
                Registro RG;    


                /*Aqui é para tratar as palavras, ta na variavel "palavra" RAFAEL(arrombado)*/


                SetRegistro(&RG,i,palavra);

                /*Aqui os registros vao estar prontas para inserir na hash e patricia*/
                /*i e o documento onde a palavra esta*/
                
                EnsereTabelaHash(TabelaHash,Peso,RG,Aux1,Aux2);

                palavra = strtok(NULL," ");
            }
        }
        fclose(ArquivoPOC);//fecha o arquivo do POC
    }
    fclose(ArquivoEntrada);//fecha o arquivo de Entrada
    return;
}