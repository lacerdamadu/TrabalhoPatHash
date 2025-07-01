//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "PreHash.h"

void SetZHash(ZHash* CelulaZ){
    CelulaZ->PrimeiraZHash = (CelulaZHash*) malloc(sizeof(CelulaZHash));
    CelulaZ->UltimaZHash = CelulaZ->PrimeiraZHash;
    CelulaZ->PrimeiraZHash->ProxZHash = NULL;
    CelulaZ->PrimeiraZHash->RegistroHash.Quantidade = -1;
}

int VerificaSeVaziaZHash(ZHash* CelulaZ){
    return(CelulaZ->PrimeiraZHash->RegistroHash.Quantidade == -1);
}

void ImprimeZHash(ZHash* CelulaZ){
    if (VerificaSeVaziaZHash(CelulaZ))
        printf("ZHash Vazia\n");
    else{
        CelulaZHash* CelulaZAux;
        CelulaZAux = CelulaZ->PrimeiraZHash;
        while (CelulaZAux != NULL){
            ImprimeRegistro(CelulaZAux->RegistroHash);
            CelulaZAux = CelulaZAux->ProxZHash;
        }
    }
}

int PesquisaZHash(ZHash* CelulaZ, Registro RG){
    if (VerificaSeVaziaZHash(CelulaZ))
        return 0;
    else{
        CelulaZHash* CelulaZAux;
        CelulaZAux = CelulaZ->PrimeiraZHash;
        while (CelulaZAux != NULL){
            if ((strcmp(CelulaZAux->RegistroHash.Palavra,RG.Palavra) == 0) && CelulaZAux->RegistroHash.Documento == RG.Documento)
                return 1;
            CelulaZAux = CelulaZAux->ProxZHash;
        }
        return 0;
    }
}

int PesquisaPalavraZHash(ZHash* CelulaZ, Registro RG){
    if (VerificaSeVaziaZHash(CelulaZ))
        return 0;
    else{
        CelulaZHash* CelulaZAux;
        CelulaZAux = CelulaZ->PrimeiraZHash;
        while (CelulaZAux != NULL){
            if ((strcmp(CelulaZAux->RegistroHash.Palavra,RG.Palavra) == 0))
                return 1;
            CelulaZAux = CelulaZAux->ProxZHash;
        }
        return 0;
    }
}


void EnsereZHash(ZHash* CelulaZ, Registro RG){
    if (VerificaSeVaziaZHash(CelulaZ)){
        CelulaZ->PrimeiraZHash->RegistroHash = RG;
        //CelulaZ->PrimeiraZHash->RegistroHash.Quantidade = 1;
        return;
    }
    else{

        CelulaZHash* CelulaZAux;
        CelulaZAux = CelulaZ->PrimeiraZHash;
        while (CelulaZAux != NULL){
            if ((strcmp(CelulaZAux->RegistroHash.Palavra,RG.Palavra) == 0) && CelulaZAux->RegistroHash.Documento == RG.Documento){
                CelulaZAux->RegistroHash.Quantidade += 1;
                return;
            }
            CelulaZAux = CelulaZAux->ProxZHash;
        }
    }
    
    CelulaZ->UltimaZHash->ProxZHash = (CelulaZHash*)malloc(sizeof(CelulaZHash));
    CelulaZ->UltimaZHash = CelulaZ->UltimaZHash->ProxZHash;
    CelulaZ->UltimaZHash->RegistroHash = RG;
    CelulaZ->UltimaZHash->ProxZHash = NULL;
    return;
}

int QuantidadePalavrasZHash(ZHash* CelulaZ){
    int Quantidade = 0;
    if (VerificaSeVaziaZHash(CelulaZ))
        return Quantidade;
    else{
        CelulaZHash* CelulaZAux;
        CelulaZAux = CelulaZ->PrimeiraZHash;
        while (CelulaZAux != NULL){
            Quantidade += 1;
            CelulaZAux = CelulaZAux->ProxZHash;
        }
        return Quantidade;
    }
}