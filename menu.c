#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "tratamento.h"
#include "Registros.h"
#include "PreHash.h"
#include "Hash.h"
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

for (int i = 1; i <= N; i++) {
    char caminho[TamLinha];
    strcpy(caminho,"PastaArquivos/");

    char ArquivosLinha[TamLinha];
    fgets(ArquivosLinha, sizeof(ArquivosLinha), ArquivoEntrada); // Pega o nome do arquivo

    ArquivosLinha[strcspn(ArquivosLinha, "\n")] = '\0'; // Remove \n

    strcat(caminho, ArquivosLinha); // Monta o caminho completo

    // Trata e insere na hash
    tratar_arquivo_para_insercao(caminho, i, Peso, TabelaHash);
}


    fclose(ArquivoEntrada);//fecha o arquivo de Entrada
    return;
}