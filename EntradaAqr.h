//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912
#ifndef ENTRADAAQR_H
#define ENTRADAAQR_H

#define TamLin 256

typedef struct {
    Palavra NomedoArqEntrada;
    Palavra* Arquivo;
    int Quantidade;
    int* QuantPalavrasDistintas;
} NomeEntradas;

#define TamLinha 256

#include "Patricia.h"
#include "Hash.h"

void EntradaArquivos(TipoArvore *raiz, Hash* TabelaHash, int* Peso, int TamaHash, NomeEntradas* Armazenamento);
void InicializaNomeEntradas(NomeEntradas* nomeentradas, int N);
void EntradaDeArquivo(NomeEntradas* nomeentradas);

#endif