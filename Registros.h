#ifndef REGISTROS_H
#define REGISTROS_H

#define TamPalavra 100


typedef struct {
    int Quantidade;
    int Documento;
    char Palavra[TamPalavra];
}Registro;

void ImprimeRegistro(Registro RG);
void SetRegistro(Registro* RG,int Documento,char* Palavra);

#endif