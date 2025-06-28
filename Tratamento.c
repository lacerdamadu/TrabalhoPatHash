#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tratamento.h"
#include "PreHash.h"
#include "Hash.h"

// Remove pontuação, números, transforma em minúsculas
void limpar_linha(char *linha) {
    int i = 0, j = 0;
    while (linha[i]) {
        if (isalpha(linha[i])) {
            linha[j++] = tolower(linha[i]);
        } else {
            linha[j++] = ' ';
        }
        i++;
    }
    linha[j] = '\0';
}

// Stopwords simples
const char *stopwords[] = {
    "the", "is", "at", "which", "on", "a", "an", "and", "or", "for", "of", "in", "to",
    "with", "this", "that", "these", "those", "be", "been", "was", "were", "it", "its",
    "but", "by", "from", "not", "are", "as", "if", "so", "then", "than", "do", "does",
    "did", "has", "have", "had", "also", "we", "you", "he", "she", "they", "them",
    "can", "will", "would", "could", "should", "about", "up", "down", "out", "into"
};
int num_stopwords = sizeof(stopwords) / sizeof(stopwords[0]);

int eh_stopword(const char *palavra) {
    for (int i = 0; i < num_stopwords; i++) {
        if (strcmp(palavra, stopwords[i]) == 0) return 1;
    }
    return 0;
}

void tratar_arquivo_para_insercao(const char *caminho, int idDoc, int *Peso, Hash *TabelaHash) {
    FILE *fp = fopen(caminho, "r");
    if (!fp) {
        printf("Erro ao abrir %s\n", caminho);
        return;
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        limpar_linha(linha);

        char *palavra = strtok(linha, " ");
        while (palavra != NULL) {
            if (!eh_stopword(palavra) && strlen(palavra) > 1) {
                Registro RG;
                SetRegistro(&RG, idDoc, palavra);
                EnsereTabelaHash(TabelaHash, Peso, RG, 2000, 701); // usa Aux1 e Aux2 fixos
            }
            palavra = strtok(NULL, " ");
        }
    }
    fclose(fp);
}
