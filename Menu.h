//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912

#ifndef MENU_H
#define MENU_H

#include "Registros.h"
#include "PreHash.h"
#include "Hash.h"

typedef struct TipoPatNo* TipoArvore;

void Menu();
void RealizarBusca(TipoArvore *ArvorePatricia, Hash *TabelaHash, int *Peso);

#endif  