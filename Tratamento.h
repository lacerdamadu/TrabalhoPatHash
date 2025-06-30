#ifndef TRATAMENTO_H
#define TRATAMENTO_H

#include "Registros.h"
#include "Hash.h"
// Função que processa entrada e limpa os arquivos
void tratar_arquivo_para_insercao(const char *caminho, int idDoc, int *Peso, Hash *TabelaHash,int* CompInsercaoHash);
void limpar_linha(char *linha);
int eh_stopword(const char *palavra);




#endif
