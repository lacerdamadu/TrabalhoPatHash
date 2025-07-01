//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 589*
// Pedro Miranda - 4912

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EntradaAqr.h"
#include "Tratamento.h"
#include "Patricia.h"
#include "Registros.h"
#include "Hash.h"

void EntradaArquivos(TipoArvore *raiz, Hash* TabelaHash, int* Peso, int TamaHash, NomeEntradas* Armazenamento) {

    char DocEntrada[256];
    // printf("Documento de entrada: ");

    // scanf("%s", DocEntrada);
    strcpy(DocEntrada, Armazenamento->Arquivo);

    DocEntrada[strcspn(DocEntrada, "\n")] = '\0';

    FILE *Arq = fopen(DocEntrada, "r");
    if(!Arq) { perror("Erro ao abrir arquivo de entrada"); return; }
   
    int num_arquivos;
    if(fscanf(Arq, "%d\n", &num_arquivos) != 1) {
        fclose(Arq);
        return;
    }


    for(int j = 0; j < Armazenamento->Quantidade; j++){
        Armazenamento->QuantPalavrasDistintas[j] = 0;
    }

    for(int j = 0; j < Armazenamento->Quantidade; j++){
        printf("tem %d palavras no doc %d\n", Armazenamento->QuantPalavrasDistintas[j], j);
    }


    for(int i = 1; i <= Armazenamento->Quantidade; i++) {
        char caminho[256];
        if(!fgets(caminho, sizeof(caminho), Arq)) break;
        caminho[strcspn(caminho, "\n")] = '\0';

        char caminho_completo[512];
        snprintf(caminho_completo, sizeof(caminho_completo), "PastaArquivos/%s", caminho);

        FILE *fp = fopen(caminho_completo, "r");
        if(!fp) {
            printf("Erro ao abrir: %s\n", caminho_completo);
            continue;
        }

        char linha[1024]; // Buffer para linha completa
        while(fgets(linha, sizeof(linha), fp)){
            linha[strcspn(linha, "\n")] = '\0'; // Remove quebra de linha
    
            //Aplica limpeza
            limpar_linha(linha); 
            
            //Divide em palavras por espaço
            char *palavra = strtok(linha, " ");
            while(palavra != NULL) {
                if(strlen(palavra) > 1 && !eh_stopword(palavra)) {
                    if(!(PesquisaBin(palavra, *raiz))){
                        printf("esse n tinha antesss\n");
                        Armazenamento->QuantPalavrasDistintas[i-1]++;
                        printf("agora e %d\n", Armazenamento->QuantPalavrasDistintas[i]);
                    }
                    Registro RG;
                    SetRegistro(&RG,i,palavra);
                    EnsereTabelaHash(TabelaHash, Peso, RG, 2000, 701); // usa Aux1 e Aux2 fixos
                    *raiz = Insere(palavra, raiz, i);
                }
                palavra = strtok(NULL, " "); // Próxima palavra
            }
        }
        fclose(fp);
        for(int j = 0; j < num_arquivos; j++){
            printf("tem %d palavras no doc %d\n", Armazenamento->QuantPalavrasDistintas[j], j);
        }
    }
    fclose(Arq);
}

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

    // fclose(ArquivoEntrada);

}
