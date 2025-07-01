//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Registros.h"

void ImprimeRegistro(Registro RG){
    printf("%s - <%d,%d>\n",RG.Palavra,RG.Quantidade,RG.Documento);
}

void SetRegistro(Registro* RG,int Doc,char* Palavra){
    (*RG).Quantidade = 1;
    (*RG).Documento = Doc;
    strcpy((*RG).Palavra,Palavra);
}

