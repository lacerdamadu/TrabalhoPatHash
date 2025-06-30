#ifndef CALCULOTFIDF_H_
#define CALCULOTFIDF_H_

#include "EntradaPatricia.h"
#include "Patricia.h"

typedef struct{
    int indice;
    double relevancia;
}Calculo;

//Funções para cálculo de relevância utilizando Patrícia
int CalculaOcorrencia(TipoArvore t, int i, Palavra k);
int CalculaNumDocs(TipoArvore t, Palavra k);
int CalculaPeso(int NumOcorrenciasi, int NumDocs, int NumTotalArq);
void CalculaRelevancia(TipoArvore t, Palavra *k, Calculo *VetorRelevancias, int NumeroDeTermosDistintos[]);

#endif