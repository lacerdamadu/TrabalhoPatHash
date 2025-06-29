//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 589*
// Pedro Miranda - 4912
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