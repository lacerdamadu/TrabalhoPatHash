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

#define Aux1 2000
#define Aux2 701

void Menu(){
    int Peso[TamPalavra];
    SetPesos(Peso);    
    Hash TabelaHah[TamHash];
    SetTabelaHash(TabelaHah, TamHash);
    TipoArvore ArvorePatricia = NULL;

    int escolha = -1;
    while(escolha != 0){
        printf("Bem-vinde ao sistema utilizado para o Estudo comparativo entre Árvore PATRICIA e Tabela HASH como estruturas para implementar arquivo invertido");
        printf("Escolha uma das seguintes opções:\n");
        printf("(1) Receber o arquivo de entrada com os textos a serem indexados;\n"
            "(2) Construir os índices invertidos, a partir dos textos de entrada, usando os TADs PATRICIA e HASH;\n"
            "(3) Imprimir os índices invertidos, contendo as palavras em ordem alfabética, uma por linha, com suas respectivas listas de ocorrências;\n"
            "(4) Realizar buscas por um ou mais termo(s) de busca, nos índices construídos, individualmente, apresentando os arquivos ordenados por relevância, também individualmente para cada TAD.\n");
        scanf("%d", &escolha);
        //Inicializando a leitura de arquivo e inserção na Tabela Hash
        // EntradaDeArquivo(TabelaHah, Peso); 
        // 
        //Inicializando a leitura de arquivo e inserção na Arvore Patricia
       
        EntradaArquivos(&ArvorePatricia, TabelaHah, Peso, TamHash);
        ImprimeOrd(ArvorePatricia);
        TabelaHashInvertido(TabelaHah, TamHash);


        int desejaPesquisar = 0;
        printf("\nDeseja realizar uma busca?\n");
        printf("1 - Buscar na Hash\n");
        printf("2 - Buscar na Patricia\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &desejaPesquisar);
        getchar();

        if (desejaPesquisar == 1) {
            char termo[TamPalavra];
            printf("\nDigite uma palavra para buscar na Hash: ");
            fgets(termo, sizeof(termo), stdin);
            termo[strcspn(termo, "\n")] = '\0';
            PesquisaIndiceInvertidoHash(TabelaHah, Peso, termo, TamHash);
    ;
        } else if (desejaPesquisar == 2) {
            char termo[TamPalavra];
            printf("\nDigite uma palavra para buscar na Patricia: ");
            fgets(termo, sizeof(termo), stdin);
            termo[strcspn(termo, "\n")] = '\0';
            Pesquisa(termo, ArvorePatricia);
        } else {
            printf("Saindo sem buscar.\n");
        }
    }
}