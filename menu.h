#ifndef MENU_H
#define MENU_H

#include "Registros.h"
#include "PreHash.h"
#include "Hash.h"
#include "Patricia.h"

#define TamLinha 256
typedef struct {
    int Quantidade;
    char** Arquivo;
} NomeEntradas;

void InicializaNomeEntradas(NomeEntradas* nomeentradas, int N );
void EntradaDeArquivo(NomeEntradas* nomeentradas);

void LerArquivos(NomeEntradas* nomeentrada,TipoArvore* raiz,Hash* Celulas,int* Peso,int ElemetentosArmazenados,int TamHASH,int* CompInsercaoHash);

typedef struct TipoPatNo* TipoArvore;

void Menu();


void EntradaDeArquivo(NomeEntradas* nomeentradas);

void EntradaDeArquivoPatricia(TipoArvore *raiz);  // Nova função para Patricia

#endif  