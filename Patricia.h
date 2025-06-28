//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 589*
// Pedro Miranda - 4***

#ifndef PATRICIA_H
#define PATRICIA_H

#include "IdInvertidoPat.h"
#include <stdio.h>
#include <stdlib.h> 
#include <sys/time.h>
#include <string.h>
#define D 50   /*tamanho máximo da palavra*/
typedef char Palavra[D]; 
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

typedef enum {
    Interno, Externo
} TipoNo;

typedef struct TipoPatNo* TipoArvore; 

typedef struct TipoPatNo {
    TipoNo nt;
    union {
        struct {
            char Referencia;
            TipoIndexAmp Index;
            TipoArvore Esq, Dir;
        } NInterno;
        struct {
            Palavra Chave;
            TLista IdInvDaPalavra;
        } NExterno;   
    } NO;
} TipoPatNo;



short EExterno(TipoArvore p); //Verifica se o nó é externo

/*Criação de nós*/
TipoArvore CriaNoInt(int i, TipoArvore *Esq,  TipoArvore *Dir, char Ref); 
TipoArvore CriaNoExt(Palavra k, int IdDoc);

void Pesquisa(Palavra k, TipoArvore t);

/*Inserção*/
TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i, int IdDoc);
TipoArvore Insere(Palavra k, TipoArvore *t, int IdDoc); 

/*Impressão*/
void Imprimepat(TipoArvore t); //Imprime mostrando os índicies e referências dos nós internos
void ImprimeOrd(TipoArvore t); //Imprime os elementos da Patrícia em ordem

#endif 