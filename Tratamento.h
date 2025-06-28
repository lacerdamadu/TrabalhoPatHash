#ifndef TRATAMENTO_H
#define TRATAMENTO_H

#include "Registros.h"
#include "Hash.h"

// Função que processa entrada.txt e limpa os arquivos listados
void tratar_arquivo_para_insercao(const char *caminho, int idDoc, int *Peso, Hash *TabelaHash);

#endif
