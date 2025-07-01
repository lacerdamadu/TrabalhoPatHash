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

void EntradaArquivos(TipoArvore *raiz, Hash* TabelaHash, int* Peso, int TamaHash) {

    char DocEntrada[256];
    printf("Documento de entrada: ");

    scanf("%s", DocEntrada);
    
   
    
    DocEntrada[strcspn(DocEntrada, "\n")] = '\0';

    FILE *Arq = fopen(DocEntrada, "r");

    if(!Arq) { 
        perror("Erro ao abrir arquivo de entrada"); return; }

    int num_arquivos;
    if(fscanf(Arq, "%d\n", &num_arquivos) != 1) {
        fclose(Arq);
        return;
    }



    for(int i = 1; i <= num_arquivos; i++) {
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
                    Registro RG;
                    SetRegistro(&RG,i,palavra);
                    EnsereTabelaHash(TabelaHash, Peso, RG, 2000, 701); // usa Aux1 e Aux2 fixos
                    *raiz = Insere(palavra, raiz, i);
                }
                palavra = strtok(NULL, " "); // Próxima palavra
            }
        }
        fclose(fp);
        
    }
    fclose(Arq);
}