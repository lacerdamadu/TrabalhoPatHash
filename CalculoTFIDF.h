#ifndef CALCULOTFIDF_H_
#define CALCULOTFIDF_H_

#include "Hash.h"
#include "PreHash.h"
#include "EntradaAqr.h"
#include "Patricia.h"

typedef struct CalculoTFIDF{
    int indice;
    double relevancia;
} CalculoTFIDF;

//Funções para cálculo de relevância utilizando Patrícia
int CalculaOcorrencia(TipoArvore t, int i, Palavra k);
int CalculaNumDocs(TipoArvore t, Palavra k);
int CalculaPeso(int NumOcorrenciasi, int NumDocs, int NumTotalArq); // Utilizada para os dois
void CalculaRelevancia(TipoArvore t, Palavra *k, CalculoTFIDF *VetorRelevancias, int NumeroDeTermosDistintos[]);
//Funções para cálculo de relevância utilizando a Tabela Hash
int CalculaOcorrenciaHash(Hash* Celulas, int *Peso, char *Palavra, int TamHASH, int idDoc);
int CalculaNumDocsHash(Hash* Celulas, int *Peso, char *Palavra, int TamHASH);
void CalculaRelevanciaHash(Hash *Celulas, Palavra *k, CalculoTFIDF *VetorRelevancias, int NumeroDeTermosDistintos[], int *Peso, char *Palavra, int TamHASH );


#endif