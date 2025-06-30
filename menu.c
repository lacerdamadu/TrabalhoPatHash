#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Registros.h"
#include "PreHash.h" 
#include "Hash.h"
#include "tratamento.h"
#include "Patricia.h"
#include "EntradaPatricia.h"
#include "menu.h"

#define TamLin 1024
#define Aux1 2000
#define Aux2 701

void InicializaNomeEntradas(NomeEntradas* nomeentradas, int N){
    nomeentradas->Quantidade = N;
    nomeentradas->Arquivo = malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++){
        nomeentradas->Arquivo[i] = malloc(50 * sizeof(char));
    }
}

void EntradaDeArquivo(NomeEntradas* nomeentradas){
    char DocEntrada[TamLin];
    printf("Digite o arquivo de entrada: ");
    scanf("%s", DocEntrada);

    FILE *ArquivoEntrada = fopen(DocEntrada, "r");
    if (ArquivoEntrada == NULL){
        perror("Erro ao abrir o arquivo");
        return;
    }

    char NChar[TamPalavra];
    if (fgets(NChar, sizeof(NChar), ArquivoEntrada) == NULL) {
        printf("Erro ao ler o número de entradas\n");
        fclose(ArquivoEntrada);
        return;
    }

    int N = atoi(NChar);
    if (N <= 0) {
        printf("Número inválido de entradas: %d\n", N);
        fclose(ArquivoEntrada);
        return;
    }

    InicializaNomeEntradas(nomeentradas, N);

    int contador = 0;
    char linha[1024];

    while (fgets(linha, sizeof(linha), ArquivoEntrada) && contador < N) {
        linha[strcspn(linha, "\n")] = '\0';

        char *palavra = strtok(linha, " ");
        while (palavra != NULL && contador < N) {
            strncpy(nomeentradas->Arquivo[contador], palavra, TamPalavra - 1);
            nomeentradas->Arquivo[contador][TamPalavra - 1] = '\0';  // garante fim da string
            contador++;
            palavra = strtok(NULL, " ");
        }
    }

    fclose(ArquivoEntrada);
}

void LerArquivos(NomeEntradas* nomeentrada, TipoArvore* raiz,
    Hash* Celulas,int* Peso, int ElemetentosArmazenados, int TamHASH, int* CompInsercaoHash){
    for (int doc = 0; doc < nomeentrada->Quantidade; doc++){
        char LinhaArq[TamLin];
        char Caminho[256];
        strcpy(Caminho,"PastaArquivos/");


        strcat(Caminho,nomeentrada->Arquivo[doc]);

        FILE *Arq = fopen(Caminho,"r");
        if (Arq == NULL){
            perror("Erro ao abrir arquivo de entrada");
            return ;
        }  
        while (fgets(LinhaArq,sizeof(LinhaArq),Arq)){
            LinhaArq[strcspn(LinhaArq,"\n")] = '\0';

            limpar_linha(LinhaArq);

            char* Palavraa = strtok(LinhaArq, " ");

            while (Palavraa != NULL){
                Registro RG;
                SetRegistro(&RG,doc,Palavraa);
                EnsereTabelaHash(Celulas,Peso,RG,Aux1,Aux2,CompInsercaoHash);
                Insere(Palavraa,raiz,doc);

                Palavraa = strtok(NULL, " ");
    
            }
        }
        fclose(Arq);
    }
}

void Menu(){
    int Peso[TamPalavra];
    SetPesos(Peso);    
    Hash TabelaHah[TamHash];
    SetTabelaHash(TabelaHah, TamHash);
    int CompPesquisaHash, CompInsercaoHash;
    TipoArvore ArvorePatricia = NULL;

    NomeEntradas nomoentradas;
    EntradaDeArquivo(&nomoentradas);

    LerArquivos(&nomoentradas,&ArvorePatricia,TabelaHah,Peso,Aux1,Aux2,&CompInsercaoHash);    

    //TabelaHashImprime(TabelaHah,TamHash);
    Imprimepat(ArvorePatricia);
}

