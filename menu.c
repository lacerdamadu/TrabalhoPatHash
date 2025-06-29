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

#define Aux1 2000
#define Aux2 701

void EntradaDeArquivo(Hash* TabelaHash, int* Peso,int* CompInsercaoHash);

void Menu(){
    int Peso[TamPalavra];
    SetPesos(Peso);    
    Hash TabelaHah[TamHash];
    SetTabelaHash(TabelaHah, TamHash);
    int CompPesquisaHash, CompInsercaoHash;
    TipoArvore ArvorePatricia = NULL;

    int estruturaEscolhida = 0;
    printf("===== ESCOLHA A ESTRUTURA =====\n");
    printf("1 - Usar Hash\n");
    printf("2 - Usar Patricia\n");
    printf("Escolha: ");
    scanf("%d", &estruturaEscolhida);


    if (estruturaEscolhida == 1) {
        printf("\n--- Usando estrutura HASH ---\n");
        EntradaDeArquivo(TabelaHah, Peso, &CompInsercaoHash);
        TabelaHashImprime(TabelaHah, TamHash);
        TabelaHashInvertido(TabelaHah, TamHash);
    } else if (estruturaEscolhida == 2) {
        printf("\n--- Usando estrutura PATRICIA ---\n");
        EntradaDeArquivoPatricia(&ArvorePatricia);
        ImprimeOrd(ArvorePatricia);
    } else {
        printf("Opção inválida. Encerrando programa.\n");
        return;
    }

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
        PesquisaIndiceInvertidoHash(TabelaHah, Peso, termo, TamHash, &CompPesquisaHash);
        printf("Quantidade de comp pesquisa Hash %d\n",CompPesquisaHash);
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

void EntradaDeArquivo(Hash* TabelaHash,int* Peso,int* CompInsercaoHash){
    char DocEntrada[30];
    *CompInsercaoHash = 0;
    printf("Digite o Documento de entrada:");
    if(fgets(DocEntrada,sizeof(DocEntrada),stdin) == NULL){
        printf("erro em abrir o arquivo %s",DocEntrada);
        return;
    }
    DocEntrada[strcspn(DocEntrada,"\n")] = '\0';

    FILE *ArquivoEntrada = fopen(DocEntrada,"r");

    if (ArquivoEntrada == NULL){
        perror("Erro em abrir o arquivo");
        return;
    }

    char NChar[TamPalavra];
    int N;
    fgets(NChar,sizeof(NChar),ArquivoEntrada);
    N = atoi(NChar);

    for (int i = 1; i <= N; i++) {
        char caminho[TamLinha];
        strcpy(caminho,"PastaArquivos/");

        char ArquivosLinha[TamLinha];
        fgets(ArquivosLinha, sizeof(ArquivosLinha), ArquivoEntrada);
        ArquivosLinha[strcspn(ArquivosLinha, "\n")] = '\0';

        strcat(caminho, ArquivosLinha);
        tratar_arquivo_para_insercao(caminho, i, Peso, TabelaHash,CompInsercaoHash);
    }

    fclose(ArquivoEntrada);
    printf("Comparaçoes Inser hash %d\n",*CompInsercaoHash);
    return;
}
