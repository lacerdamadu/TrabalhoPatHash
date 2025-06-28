#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Quantidade;
    int IdDoc;
} Informacoes;

typedef struct IdInvertido* Apontador;

typedef struct IdInvertido {
    Informacoes Item;
    struct IdInvertido* pProx; 
} IdInvertido;

typedef struct {
    Apontador pPrimeiro;
    Apontador pUltimo;
} TLista;

void FLVazia(TLista* pLista);
int LEhVazia(TLista* pLista);
void LInsere(TLista *pLista, int IdDoc);
void CresceQuantidade(TLista* pLista, int IdDoc);

// int LRetira(TLista* pLista, Informacoes *pItem);

void LImprime(TLista* pLista);