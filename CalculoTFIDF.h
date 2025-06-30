#define CALCULOTFIDF_H_
#ifndef CALCULOTFIDF_H_

#include "EntradaPatricia.h"
#include "Patricia.h"

//Funções para cálculo de relevância utilizando Patrícia
int CalculaOcorrencia(TipoArvore t, int i, Palavra k);
int CalculaNumDocs(TipoArvore t, Palavra k);
int CalculaPeso(int NumOcorrenciasi, int NumDocs, int NumTotalArq);
void CalculaRelevancia(TipoArvore t, int NumTermosDistintos, Palavra k[], int *VetorRelevanciaDocs[], int NumeroDeTermosDistintos[]);


#endif