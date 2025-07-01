//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912

#include <stdio.h>
#include <math.h>
#include "Patricia.h"
#include "IdInvertidoPat.h"
#include "CalculoTFIDF.h"
#include "Hash.h"
#include "PreHash.h"

int CalculaOcorrencia(TipoArvore t, int i, Palavra k){//Calcula o número de ocorrências de uma palavra em um documento
    IdInvertido* pAux;
    pAux = t->NO.NExterno.IdInvDaPalavra.pPrimeiro->pProx;
    if (EExterno(t)){ /*Se chegamos em um nó externo, ou ele é a palavra que estamos procurando ou ele não existe na árvore*/
        if (strcmp(k, t->NO.NExterno.Chave) == 0){ 
            while(pAux->pProx != NULL && pAux->Item.IdDoc != i){
                pAux = pAux->pProx;
            }
            if(pAux->Item.IdDoc == i){
                return pAux->Item.Quantidade;
            }
            else{
                return 0;
            }
        } else { 
            return 0;
        }
        return;   
    }
    if (k[t->NO.NInterno.Index-1] < t->NO.NInterno.Referencia){ /*Vai cair aqui se estivermos em um nó interno. Para esse caso, se a posição Index-1 (que é o índicie armazenado no nó interno) da palavra for menor que a referência do nó interno, vamos procurar no filho a esquerda desse nó*/
        Pesquisa(k, t->NO.NInterno.Esq);
    } else { /*Caso contrário, procuraremos no filho à direita*/
        Pesquisa(k, t->NO.NInterno.Dir);
    }
}
int CalculaNumDocs(TipoArvore t, Palavra k){
    int contador = 0;
    IdInvertido* pAux;
    
    if (EExterno(t)){ /*Se chegamos em um nó externo, ou ele é a palavra que estamos procurando ou ele não existe na árvore*/
        if (strcmp(k, t->NO.NExterno.Chave) == 0){
            pAux = t->NO.NExterno.IdInvDaPalavra.pPrimeiro; 
            while(pAux->pProx != NULL){
                contador++;
                pAux = pAux->pProx;
            }
            return contador;
        } else { 
            return 0;
        }
        return;   
    }
    if (k[t->NO.NInterno.Index-1] < t->NO.NInterno.Referencia){ /*Vai cair aqui se estivermos em um nó interno. Para esse caso, se a posição Index-1 (que é o índicie armazenado no nó interno) da palavra for menor que a referência do nó interno, vamos procurar no filho a esquerda desse nó*/
        Pesquisa(k, t->NO.NInterno.Esq);
    } else { /*Caso contrário, procuraremos no filho à direita*/
        Pesquisa(k, t->NO.NInterno.Dir);
    }
}
int CalculaPeso(int NumOcorrenciasi, int NumDocs, int NumTotalArq){
    /* NumDocs -> Número de documentos que contem aquele termo, NumOcorrenciasi -> Número de ocorrencias do termo no doc i,
    NumTotalArq -> O número total de arquivos*/
    int a = 0, Peso = 0;
    if(NumOcorrenciasi > 0){
        a = log10(NumTotalArq)/ log10(2); //Fórmula de mudança de base: log2(x) = log10(x) / log10(2)
        Peso =  NumOcorrenciasi * (a/NumDocs); 
    }
    return 0;
}

void CalculaRelevancia(TipoArvore t, Palavra *k, CalculoTFIDF *VetorRelevancias, int NumeroDeTermosDistintos[]){
    size_t tamanho = sizeof(k) / sizeof(k[0]);
    size_t NumeroDeDocs = sizeof(VetorRelevancias) / sizeof(VetorRelevancias[0]); //Calcula o número de documentos no total
    int somatorio = 0;
    for(int j=0; j<NumeroDeDocs; j++){
        for(int i=0; i<tamanho; i++){
            int Oc = CalculaOcorrencia(t, j+1, k[i]);
            int NumDocs = CalculaNumDocs(t, k[i]);
            somatorio += CalculaPeso(Oc, NumDocs, NumeroDeDocs);
        }
        VetorRelevancias[j].relevancia = somatorio/NumeroDeTermosDistintos[j];
    }
}

int CalculaOcorrenciaHash(Hash* Celulas, int *Peso, char *Palavra, int TamHASH, int idDoc){
    int Posicao = CodificaRegistroHash(Peso,Palavra) %  TamHash;
    for (int i = 0; i < TamHASH; i++){
        if (PesquisaCelulaHash(&Celulas[i],Palavra));{
            CelulaHash* CelulaAux;
            CelulaAux = Celulas->PriPosicao->ProxCel;
            while (CelulaAux != NULL){
                if (strcmp(CelulaAux->CelulaZ.PrimeiraZHash->RegistroHash.Palavra,Palavra) == 0){
                    CelulaZHash* CelulaZAuX2;
                    CelulaZAuX2 = CelulaAux->CelulaZ.PrimeiraZHash;
                    while (CelulaZAuX2 != NULL){
                        if(CelulaZAuX2->RegistroHash.Documento == idDoc){
                            return CelulaZAuX2->RegistroHash.Quantidade;
                        }
                        CelulaZAuX2 = CelulaZAuX2->ProxZHash;
                    }
                }  
                CelulaAux = CelulaAux->ProxCel;
            }
            
        }
    }
    return 0;
}

int CalculaNumDocsHash(Hash* Celulas, int *Peso, char *Palavra, int TamHASH){
    int Posicao = CodificaRegistroHash(Peso,Palavra) %  TamHash;
    for (int i = 0; i < TamHASH; i++){
        if (PesquisaCelulaHash(&Celulas[i],Palavra));{
            CelulaHash* CelulaAux;
            CelulaAux = Celulas->PriPosicao->ProxCel;
            while (CelulaAux != NULL){
                if (strcmp(CelulaAux->CelulaZ.PrimeiraZHash->RegistroHash.Palavra,Palavra) == 0){
                        return QuantidadePalavrasZHash(&CelulaAux->CelulaZ);
                    }
                }  
                CelulaAux = CelulaAux->ProxCel;
            }
            
        }
    return 0;
}

void CalculaRelevanciaHash(Hash *Celulas, Palavra *k, CalculoTFIDF *VetorRelevancias, int NumeroDeTermosDistintos[], int *Peso, char *Palavra, int TamHASH ){
    size_t tamanho = sizeof(k) / sizeof(k[0]);
    size_t NumeroDeDocs = sizeof(VetorRelevancias) / sizeof(VetorRelevancias[0]); //Calcula o número de documentos no total
    int somatorio = 0;
    for(int j=0; j<NumeroDeDocs; j++){
        for(int i=0; i<tamanho; i++){
            int Oc = CalculaOcorrenciaHash(Celulas, Peso, Palavra, TamHASH, j+1);
            int NumDocs = CalculaNumDocsHash(Celulas, Peso, Palavra, TamHASH);
            somatorio += CalculaPeso(Oc, NumDocs, NumeroDeDocs);
        }
        VetorRelevancias[j].relevancia = somatorio/NumeroDeTermosDistintos[j];
    }
}