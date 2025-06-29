#include "IdInvertidopat.h"

void FLVazia(TLista* pLista){
    pLista->pPrimeiro = (Apontador) malloc(sizeof(IdInvertido));
    pLista->pUltimo = pLista->pPrimeiro;
    pLista->pPrimeiro->pProx = NULL;
}

int LEhVazia(TLista* pLista){
    return (pLista->pPrimeiro == pLista->pUltimo);
}

void LInsere(TLista *lista, int IdDoc) {
    // Verifica se já existe o documento
    Apontador atual = lista->pPrimeiro->pProx;
    while(atual != NULL) {
        if(atual->Item.IdDoc == IdDoc) {
            atual->Item.Quantidade++;
            return;
        }
        atual = atual->pProx;
    }
    
    // Se não existir, insere novo
    Apontador novo = (Apontador)malloc(sizeof(IdInvertido));
    novo->Item.IdDoc = IdDoc;
    novo->Item.Quantidade = 1;
    novo->pProx = NULL;
    
    if(LEhVazia(lista)) {
        lista->pPrimeiro->pProx = novo;
    } else {
        lista->pUltimo->pProx = novo;
    }
    lista->pUltimo = novo;
}

void CresceQuantidade(TLista *pLista, int IdDoc){
    IdInvertido* pAux;
    pAux = pLista->pPrimeiro->pProx;

    while(pAux->pProx != NULL && pAux->pProx->Item.IdDoc != IdDoc){
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
int LDocumentoExiste(TLista *lista, int IdDoc) {
    Apontador p = lista->pPrimeiro->pProx;
    while(p != NULL) {
        if(p->Item.IdDoc == IdDoc) return 1;
        p = p->pProx;
    }
    return 0;
}