//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 589*
// Pedro Miranda - 4912
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Hash.h"
#include "Registros.h"
#include "PreHash.h"


void SetCelulaHash(Hash* Celula){
    Celula->PriPosicao = (CelulaHash*) malloc(sizeof(CelulaHash));
    Celula->UltPosicao = Celula->PriPosicao;
    Celula->PriPosicao->ProxCel = NULL;
    Celula->PriPosicao->Posicao = -1;
}

int VerificaCelulaVaziaHash(Hash* Celula){
    return(Celula->PriPosicao == Celula->UltPosicao);
}

int EnsereCelulaHash(Hash* Celula,Registro RG){
    if (VerificaCelulaVaziaHash(Celula)){//Caso nao tenha nada na lista encadeada insere na primeira 
        Celula->PriPosicao->ProxCel = (CelulaHash*) malloc(sizeof(CelulaHash));
        Celula->UltPosicao = Celula->PriPosicao->ProxCel;
        SetZHash(&Celula->UltPosicao->CelulaZ); 
        EnsereZHash(&Celula->UltPosicao->CelulaZ,RG);
        Celula->UltPosicao->Posicao = 1;
        Celula->UltPosicao->ProxCel = NULL;
        return 1;
    }
    else{//caso a lista nao esteja vazia verifica se ja tem a mesma palavra e acresenta +1 na quantidade
        CelulaHash* CelulaAux;
        CelulaAux = Celula->PriPosicao->ProxCel; 
        while (CelulaAux != NULL){
            if (PesquisaPalavraZHash(&CelulaAux->CelulaZ,RG)){
                EnsereZHash(&CelulaAux->CelulaZ,RG);
                return 1;
            }
            CelulaAux = CelulaAux->ProxCel;
        }
    }
    //caso chegue aqui nao tem essa palavra na lista ou nao tem no mesmo documento ai coloca no final 
    Celula->UltPosicao->ProxCel = (CelulaHash*) malloc(sizeof(CelulaHash));
    Celula->UltPosicao->ProxCel->Posicao = Celula->UltPosicao->Posicao + 1;
    Celula->UltPosicao = Celula->UltPosicao->ProxCel;
    Celula->UltPosicao->ProxCel = NULL;
    SetZHash(&Celula->UltPosicao->CelulaZ);
    EnsereZHash(&Celula->UltPosicao->CelulaZ,RG);
    return 1;
}

void ImprimeCelulaHash(Hash* Celula){
    if (VerificaCelulaVaziaHash(Celula)){
        printf("Celula vazia\n");
    }
    else{
        CelulaHash* CelulaAux;
        CelulaAux = Celula->PriPosicao->ProxCel;
        while (CelulaAux != NULL){
            printf("  Carga |%d|\n",CelulaAux->Posicao);
            ImprimeZHash(&CelulaAux->CelulaZ);
            CelulaAux = CelulaAux->ProxCel;
        }
        printf("---------------------------------------------------\n");
    }
}

int PesquisaCelulaHash(Hash* Celula,char* Palavra){
    CelulaHash* CelulaAux;
    CelulaAux = Celula->PriPosicao->ProxCel;
    while (CelulaAux != NULL){
        if (strcmp(CelulaAux->CelulaZ.PrimeiraZHash->RegistroHash.Palavra,Palavra) == 0);
            return 1;
        CelulaAux = CelulaAux->ProxCel;
    }
    return 0;
}

int QuantidadePalavrasCelulaHash(Hash* Celula){
    int Quantidade = 0;
    CelulaHash* CelulaAux;
    CelulaAux = Celula->PriPosicao->ProxCel;
    while (CelulaAux != NULL){
        Quantidade += QuantidadePalavrasZHash(&CelulaAux->CelulaZ);
        CelulaAux = CelulaAux->ProxCel;
    }
    return Quantidade;
}



void SetTabelaHash(Hash* Celulas,int Tam){
    for (int i = 0; i < Tam; i++){
        SetCelulaHash(&Celulas[i]);
    }
}

void TabelaHashImprime(Hash* Celulas,int Tam){
    for (int i = 0; i < Tam; i++){
        printf("  Hash [%d]\n",i);
        printf("==================================================\n");
        ImprimeCelulaHash(&Celulas[i]);
        printf("\n");
    }
}

int CodificaRegistroHash(int* Peso,char* Palavra){
    int Valor = 0;
    for (int i = 0; i <= TamPalavra; i++){
        if (Palavra[i] != '\0'){
            Valor += ((int)Palavra[i] * Peso[i]);
        }
        else
            return Valor;   
    }
}

int FatorCargaHash(double ElemetentosArmazenados,double TamHASH){// Calcula o fator de carga que a tabela hash pode ter
    return ((int)ceil(ElemetentosArmazenados/TamHASH));
}

void SetPesos(int* Peso){
    srand( (unsigned) time(NULL));
    for (int i = 0; i < TamPalavra; i++){
        Peso[i] = 1 + (rand() % 100);
    }
}

void EnsereTabelaHash(Hash* Celulas,int* Peso,Registro RG,int ElemetentosArmazenados,int TamHASH){
    int Posicao = CodificaRegistroHash(Peso,RG.Palavra) %  TamHash;
    int FatorDeCarga = FatorCargaHash(ElemetentosArmazenados,TamHASH);
    int PosicaoAux = Posicao;
    do{    
        if(Posicao >= TamHash){//Caso a posicao seja invalida (Maior que o tamanho da hash)
            Posicao = 0;
        }
        if (VerificaCelulaVaziaHash(&Celulas[Posicao])){// Caso nao tenha nada na posicao da tabela hash insere
            EnsereCelulaHash(&Celulas[Posicao],RG);
            return;
        }
        else if (PesquisaCelulaHash(&Celulas[Posicao],RG.Palavra)){// Caso nao esteja vazia a lista verifica se tem o mesmo registro (Palavra e Documento)
            EnsereCelulaHash(&Celulas[Posicao],RG);
            return;
        }
        else if (Celulas[Posicao].UltPosicao->Posicao < FatorDeCarga){// Caso chegue aqui esse registro é novo e tem que verificar se pode colocar na lista(Carga)
            EnsereCelulaHash(&Celulas[Posicao],RG);
            return;
        }
        else if(Posicao <= TamHash){//Nao tem como colocar naquele indice vai para o proximo
            Posicao += 1;
        }
    } while (Posicao != PosicaoAux);
    printf("Tabela Cheia\n");
    printf("Registro - %s -<%d,%d> nao inserido\n",RG.Palavra,RG.Quantidade,RG.Documento);
    return;
}

int PesquisaTabelaHash(Hash* Celulas,int* Peso,char* Palavra,int TamHASH){
    int Posicao = CodificaRegistroHash(Peso,Palavra) %  TamHash;
    for (int i = 0; i < TamHASH; i++){
        if (PesquisaCelulaHash(&Celulas[i],Palavra));{
            printf("%s esta na lista\n",Palavra);
            return 1;
        }
    }
    printf("%s nao esta na lista\n",Palavra);
    return 0;
}

int CompararPalavas(const void *a,const void *b) {
    const Registro *p1 = (const Registro *)a;
    const Registro *p2 = (const Registro *)b;
    return strcmp(p1->Palavra, p2->Palavra);
}

int CompararDocumento(const void *a, const void *b) {
    Registro *itemA = (Registro *)a;
    Registro *itemB = (Registro *)b;
    return (itemA->Documento - itemB->Documento); 
}

int TabelaHashQuantPalavras(Hash* Celulas,int TamHASH){
    int Quantidade = 0;
    for (int i = 0; i < TamHASH; i++){
        Quantidade += QuantidadePalavrasCelulaHash(&Celulas[i]);
    }
    return Quantidade;
}

void TabelaHashInvertido(Hash* Celulas,int TamHASH){
    int Count = TabelaHashQuantPalavras(Celulas,TamHASH);
    Registro RG[Count];
    int posicao = 0;

    for (int i = 0; i < TamHASH; i++){
        if (VerificaCelulaVaziaHash(&Celulas[i])){
            continue;        
        }
        else{
            CelulaHash* CelulaAux;
            CelulaAux = Celulas[i].PriPosicao->ProxCel;
            while (CelulaAux != NULL){
                CelulaZHash* CelulaZAux;
                CelulaZAux = CelulaAux->CelulaZ.PrimeiraZHash;
                while (CelulaZAux != NULL){

                    RG[posicao] = CelulaZAux->RegistroHash;
                    posicao += 1;
                    CelulaZAux = CelulaZAux->ProxZHash;
                }    
                CelulaAux = CelulaAux->ProxCel;
            }    
        }    
    }

    //Esse organiza em ordem alfabetica
    qsort(RG,Count,sizeof(Registro),CompararPalavas);

    int comeco = 0;
    while (comeco < Count){
        int final = comeco + 1;
        while (final < Count && (strcmp(RG[comeco].Palavra,RG[final].Palavra) == 0))
            final++;
        qsort(&RG[comeco],final-comeco,sizeof(Registro),CompararDocumento);
        comeco = final;
    }

    for (int i = 0; i < Count; i++)
        ImprimeRegistro(RG[i]);
}
void PesquisaIndiceInvertidoHash(Hash* Tabela, int* Peso, char* Palavra, int TamHASH) {
    int pos = CodificaRegistroHash(Peso, Palavra) % TamHASH;

    for (int i = 0; i < TamHASH; i++) {
        int idx = (pos + i) % TamHASH;
        CelulaHash* atual = Tabela[idx].PriPosicao->ProxCel;
        while (atual != NULL) {
            if (strcmp(atual->CelulaZ.PrimeiraZHash->RegistroHash.Palavra, Palavra) == 0) {
                CelulaZHash* z = atual->CelulaZ.PrimeiraZHash;
                while (z != NULL) {
                    if (strcmp(z->RegistroHash.Palavra, Palavra) == 0) {
                        ImprimeRegistro(z->RegistroHash);
                    }
                    z = z->ProxZHash;
                }
                return;
            }
            atual = atual->ProxCel;
        }
    }

    printf("Palavra '%s' não encontrada na Hash.\n", Palavra);
}

