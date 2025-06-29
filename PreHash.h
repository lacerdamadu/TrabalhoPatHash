#ifndef PREHASH_H
#define PREHASH_H

#include "Registros.h"

typedef struct CELULAZHASH{
    short PosicaoZ;
    Registro RegistroHash;
    struct CELULAZHASH* ProxZHash;
} CelulaZHash;

typedef struct {
    CelulaZHash* PrimeiraZHash;
    CelulaZHash* UltimaZHash;  
}ZHash;

void SetZHash(ZHash* CelulaZ);
int VerificaSeVaziaZHash(ZHash* CelulaZ);
void ImprimeZHash(ZHash* CelulaZ);
int PesquisaZHash(ZHash* CelulaZ, Registro RG);
int PesquisaPalavraZHash(ZHash* CelulaZ, Registro RG);
int QuantidadePalavrasZHash(ZHash* CelulaZ);

void EnsereZHash(ZHash* CelulaZ, Registro RG,int* CompInsercaoHash);

#endif