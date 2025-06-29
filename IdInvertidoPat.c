#include "IdInvertidopat.h"

void FLVazia(TLista* pLista){
    pLista->pPrimeiro = (Apontador) malloc(sizeof(IdInvertido));
    pLista->pUltimo = pLista->pPrimeiro;
    pLista->pPrimeiro->pProx = NULL;
}

int LEhVazia(TLista* pLista){
    return (pLista->pPrimeiro == pLista->pUltimo);
}

void LInsere(TLista *pLista, int IdDoc){
    if(IdDoc == pLista->pUltimo->Item.IdDoc){
         CresceQuantidade(pLista, IdDoc);
         return;
    }
    pLista->pUltimo->pProx = (Apontador) malloc(sizeof(IdInvertido));
    pLista->pUltimo = pLista->pUltimo->pProx;
    pLista->pUltimo->Item.IdDoc = IdDoc;
    pLista->pUltimo->Item.Quantidade = 1;
    pLista->pUltimo->pProx = NULL;
}

void CresceQuantidade(TLista *pLista, int IdDoc){
    IdInvertido* pAux;
    pAux = pLista->pPrimeiro->pProx;

    while(pAux->pProx != NULL && pAux->Item.IdDoc != IdDoc){
        pAux = pAux->pProx;
    }

    pAux->Item.Quantidade++;
    
}

void LImprime(TLista* pLista){
    Apontador pAux;
    pAux = pLista->pPrimeiro->pProx;
    while (pAux != NULL){
        printf("<%d,%d>\n", pAux->Item.Quantidade, pAux->Item.IdDoc);
        pAux = pAux->pProx; 
    }
}