//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Registros.h"
#include "PreHash.h" 
#include "Hash.h"
#include "Tratamento.h"
#include "Patricia.h"
#include "EntradaAqr.h"
#include "Menu.h"
#include "CalculoTFIDF.h"

#define Aux1 2000
#define Aux2 701

void Menu(){
    int Peso[TamPalavra];
    SetPesos(Peso);    
    Hash TabelaHah[TamHash];
    SetTabelaHash(TabelaHah, TamHash);
    TipoArvore ArvorePatricia = NULL;
    
    int *PalavrasDistintas;

    printf("Bem-vinde ao sistema utilizado para o Estudo comparativo entre Arvore PATRICIA e Tabela HASH como estruturas para implementar arquivo invertido");
    int escolha = -1;
    while(escolha != 0){
        printf("Escolha uma das seguintes opcoes:\n");
        printf("(0) Terminar a execucao do codigo\n"
            "(1) Construir os indices invertidos, a partir dos textos de entrada, usando os TADs PATRICIA e HASH;\n"
            "(2) Imprimir os indices invertidos na Hash;\n"
            "(3) Imprimir os indices invertidos na Patricia\n");

        scanf("%d", &escolha);
        switch (escolha){
            case 0:
                break;
            case 1:
                EntradaArquivos(&ArvorePatricia, TabelaHah, Peso, TamHash);
                break;
            case 2:
                printf("--> Hash\n");
                TabelaHashInvertido(TabelaHah, TamHash);
                break;
            case 3:
                printf("--> Patricia\n");
                ImprimeOrd(ArvorePatricia);
            default:
            break;
        }
    }


}

void RealizarBusca(TipoArvore *ArvorePatricia, Hash *TabelaHash, int *Peso){
    printf("Quantos termos voce deseja pesquisar?\n");
    int NumTermosBusca = 0;
    scanf("%d", &NumTermosBusca);
    Palavra Termos[NumTermosBusca];
    for(int i=0; i<NumTermosBusca; i++){
        printf("%d a palavra:", i);
        scanf("%s", Termos[i]);
    }

}