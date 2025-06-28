#ifndef MENU_H
#define MENU_H

#include "Registros.h"
#include "PreHash.h"
#include "Hash.h"
#include "Patricia.h"

#define TamLinha 256

void Menu();

void EntradaDeArquivo(Hash* TabelaHash,int* Peso);

void EntradaDeArquivoPatricia(TipoArvore *raiz);  // Nova função para Patricia

#endif  