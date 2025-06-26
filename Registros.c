#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Registros.h"

void ImprimeRegistro(Registro RG){
    printf("      %s - <%d,%d>\n",RG.Palavra,RG.Quantidade,RG.Documento);
}

void SetRegistro(Registro* RG,int Doc,char* Palavra){
    (*RG).Quantidade = 1;
    (*RG).Documento = Doc;
    strcpy((*RG).Palavra,Palavra);
}

// void RecebeArquivo(){
//     FILE *arquivo = fopen("Arquivo1.txt","r");

//     if (arquivo == NULL) {
//         perror("Erro ao abrir o arquivo");
//     }

//     char linha[TamLinha];
//     int doc = 1;
//     // Lê linha por linha
//     while (fgets(linha, sizeof(linha), arquivo)) {
//         // Remove \n se existir
//         linha[strcspn(linha, "\n")] = '\0';

//         // Separa palavras usando espaço como delimitador
//         char *palavra = strtok(linha, " ");
//         while (palavra != NULL) {
//             printf("- %s | %d\n", palavra,doc);
//             doc += 1;
//             palavra = strtok(NULL, " ");
//         }
//     }

//     fclose(arquivo);
// }