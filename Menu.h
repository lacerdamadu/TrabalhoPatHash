#ifndef MENU_H
#define MENU_H

#include "Registros.h"
#include "PreHash.h"
#include "Hash.h"

typedef struct TipoPatNo* TipoArvore;

void Menu();
void RealizarBusca(TipoArvore *ArvorePatricia, Hash *TabelaHash, int *Peso);

#endif  