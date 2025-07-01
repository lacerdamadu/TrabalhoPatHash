//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tratamento.h"

// Remove pontuação, números, transforma em minúsculas
void limpar_linha(char *linha) {
    int i = 0, j = 0;
    while (linha[i]) {
        if(isspace(linha[i])) {  // Mantém espaços
            linha[j++] = ' ';
            i++;
            continue;
        }
        // Passo 1:converter para minúscula
        char c = tolower((unsigned char)linha[i]); 
        
        // Passo 2:remove números e pontuação
        if (isalpha(c)) {
            linha[j++] = c;
        }
        i++;
    }
    linha[j] = '\0';
}

// Stopwords simples, peguei os exemplos da internet
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