#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

    printf("Bem-vinde ao sistema utilizado para o Estudo comparativo entre Árvore PATRICIA e Tabela HASH como estruturas para implementar arquivo invertido");
    int escolha = -1;
    while(escolha != 0){
        
        printf("Escolha uma das seguintes opções:\n");
        printf("(0) Terminar a execução do código\n"
            "(1) Receber o arquivo de entrada com os textos a serem indexados;\n"
            "(2) Construir os indices invertidos, a partir dos textos de entrada, usando os TADs PATRICIA e HASH;\n"
            "(3) Imprimir os indices invertidos;\n"
            "(4) Realizar buscas por um ou mais termo(s) de busca\n");

        scanf("%d", &escolha);
        switch (escolha){
            case 0:
                break;
            case 1:
                printf("Não tem nada aqui ainda");
                break;
            case 2:
                EntradaArquivos(&ArvorePatricia, TabelaHah, Peso, TamHash, PalavrasDistintas);
                for(int i = 0; i < 7; i++){
                    printf("palavras distintas em %d: %d\n", i, PalavrasDistintas[i]);
                }
                break;
            case 3:
                ImprimeOrd(ArvorePatricia);
                TabelaHashInvertido(TabelaHah, TamHash);
                break;
            case 4:
                RealizarBusca(&ArvorePatricia, TabelaHah, Peso);
                break;
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
        printf("%da palavra:", &i);
        scanf("%s", Termos[i]);
    }

}