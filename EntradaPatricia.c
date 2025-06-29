#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tratamento.h"
#include "Patricia.h"
#include "Registros.h"

void EntradaDeArquivoPatricia(TipoArvore *raiz) {
    char DocEntrada[256];
    printf("Documento de entrada: ");
    if(!fgets(DocEntrada, sizeof(DocEntrada), stdin)) return;  // Parêntese corrigido aqui
    DocEntrada[strcspn(DocEntrada, "\n")] = '\0';

    FILE *Arq = fopen(DocEntrada, "r");
    if(!Arq) { 
        perror("Erro ao abrir arquivo de entrada"); 
        return; 
    }

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

        char linha[1024];
    while(fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        
        // Processamento robusto da linha
        char *palavra = strtok(linha, " ");
        while(palavra != NULL) {
            // Normalização completa
            char palavra_norm[D];
            strncpy(palavra_norm, palavra, D-1);
            palavra_norm[D-1] = '\0';
            
            // Filtro rigoroso
            int j = 0;
            for(int i = 0; palavra[i]; i++) {
                if(isalpha(palavra[i])) {
                    palavra_norm[j++] = tolower(palavra[i]);
                }
            }
            palavra_norm[j] = '\0';

            if(strlen(palavra_norm) > 1 && !eh_stopword(palavra_norm)) {
                TipoArvore no = BuscaPatricia(*raiz, palavra_norm);
                if(no) {
                    // Atualização segura da lista
                    Apontador p = no->NO.NExterno.IdInvDaPalavra.pPrimeiro->pProx;
                    int encontrado = 0;
                    while(p != NULL) {
                        if(p->Item.IdDoc == i) {
                            p->Item.Quantidade++;
                            encontrado = 1;
                            break;
                        }
                        p = p->pProx;
                    }
                    if(!encontrado) {
                        LInsere(&no->NO.NExterno.IdInvDaPalavra, i);
                    }
                } else {
                    // Inserção limpa
                    *raiz = Insere(palavra_norm, raiz, i);
                }
            }
            palavra = strtok(NULL, " ");
        }
    }
        fclose(fp);
    }
    fclose(Arq);
}