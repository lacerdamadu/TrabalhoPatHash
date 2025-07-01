//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912

#ifndef HASH_H
#define HASH_H

#define TamHash 11

#include "Registros.h"
#include "PreHash.h"

typedef struct CELULAHASH{
    short Posicao;
    ZHash CelulaZ;
    struct CELULAHASH* ProxCel;
}CelulaHash;

typedef struct {
    CelulaHash* PriPosicao; 
    CelulaHash* UltPosicao;
}Hash;



void SetCelulaHash(Hash* Celula);
int VerificaCelulaVaziaHash(Hash* Celula);
int EnsereCelulaHash(Hash* Celula,Registro RG);
void ImprimeCelulaHash(Hash* Celula);
int CalculaFatorCargaCelula(Hash* Celula);
int PesquisaCelulaHash(Hash* Celula,char* Palavra);
int QuantidadePalavrasCelulaHash(Hash* Celula);


void SetPesos(int* Peso);
void SetTabelaHash(Hash* Celulas,int Tam);
void TabelaHashImprime(Hash* Celulas,int Tam);
int CodificaRegistroHash(int* Peso,char* Palavra);
int FatorCargaHash(double ElemetentosArmazenados,double TamHASH);
int PesquisaTabelaHash(Hash* Celulas,int* Peso,char* Palavra,int TamHASH);
void EnsereTabelaHash(Hash* Celulas,int* Peso,Registro RG,int ElemetentosArmazenados,int TamHASH);
int TabelaHashQuantPalavras(Hash* Celulas,int TamHASH);

int CompararPalavas(const void *a,const void *b);
int CompararDocumento(const void *a, const void *b);

void TabelaHashInvertido(Hash* Celulas,int TamHASH);
void PesquisaIndiceInvertidoHash(Hash* Tabela, int* Peso, char* Palavra, int TamHASH);

#endif  