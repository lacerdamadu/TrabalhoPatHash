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
    pLista->pUltimo->pProx = (Apontador) malloc(sizeof(IdInvertido));
    pLista->pUltimo = pLista->pUltimo->pProx;
    pLista->pUltimo->Item.IdDoc = IdDoc;
    pLista->pUltimo->Item.Quantidade = 1;
    pLista->pUltimo->pProx = NULL;
}

void CresceQuantidade(TLista *pLista, int IdDoc){
    IdInvertido* pAux;
    pAux = pLista->pPrimeiro->pProx;

    while(pAux != NULL && pAux->Item.IdDoc != IdDoc){
        pAux = pAux->pProx;
    }
    
    pAux->Item.Quantidade++;
}

// void ImprimiLista(Compartimento *lista){
//     Celula* pAux;
//     pAux = lista->primeiro->pProx;
//     while(pAux != NULL){
//     printf("%0.lf %d\n", pAux->rocha.Peso, pAux->rocha.Valor);
//         pAux = pAux->pProx; /* próxima célula */
//     }
// }

// int LRetira(TLista* pLista, Informacoes* pItem){
//     IdInvertido* pAux;
//     if (LEhVazia(pLista))
//     return 0;
//     *pItem = pLista->pPrimeiro->pProx->Item;
//     pAux = pLista->pPrimeiro;
//     pLista->pPrimeiro = pLista->pPrimeiro->pProx;
//     free(pAux);
//     return 1;
// }

void LImprime(TLista* pLista){
    Apontador pAux;
    pAux = pLista->pPrimeiro->pProx;
    while (pAux != NULL){
    printf("<%d,%d>\n", pAux->Item.Quantidade, pAux->Item.IdDoc);
    pAux = pAux->pProx; /* próxima célula */
    }
}