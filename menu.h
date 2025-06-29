#ifndef MENU_H
#define MENU_H

#include "Registros.h"
#include "PreHash.h"
#include "Hash.h"


#define TamLinha 256

typedef struct TipoPatNo* TipoArvore;
void Menu();


void EntradaDeArquivo(Hash* TabelaHash,int* Peso,int* CompInsercaoHash);

void EntradaDeArquivoPatricia(TipoArvore *raiz);  // Nova função para Patricia

#endif  