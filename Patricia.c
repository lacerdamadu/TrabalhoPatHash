//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 589*
// Pedro Miranda - 4***

#include "Patricia.h"

void Imprimepat(TipoArvore t){
    if(t == NULL){
        return;
    }
    if(!EExterno(t)){
        printf("interno - id %d e ref %c \n", t->NO.NInterno.Index, t->NO.NInterno.Referencia);
        printf("Esquerda:\n");
        Imprimepat(t->NO.NInterno.Esq);
        printf("Direita:\n");
        Imprimepat(t->NO.NInterno.Dir);
    } else {
        printf("externo - chave %s\n", t->NO.Chave);
    }
}

void ImprimeOrd(TipoArvore t){
        if(t == NULL){
        return;
    }
    if(!EExterno(t)){
        ImprimeOrd(t->NO.NInterno.Esq);
        ImprimeOrd(t->NO.NInterno.Dir);
    } else {
        printf("%s\n", t->NO.Chave);
    }
}

short EExterno(TipoArvore p){ //ok
    /* Verifica se p^ e nodo externo */
    return (p->nt == Externo);
}


TipoArvore CriaNoInt(int i, TipoArvore *Esq,  TipoArvore *Dir, char Ref){ 
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno; 
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir; 
    p->NO.NInterno.Index = i; 
    p->NO.NInterno.Referencia = Ref;
    return p;
} 

TipoArvore CriaNoExt(Palavra k){ 
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo; 
    strcpy(p->NO.Chave, k); 
    return p;
}  

void Pesquisa(Palavra k, TipoArvore t){ 
    if (EExterno(t)){ /*Se chegamos em um nó externo, ou ele é a palavra que estamos procurando ou ele não existe na árvore*/
        if (strcmp(k, t->NO.Chave) == 0){ 
            printf("Elemento encontrado\n");
        } else { 
            printf("Elemento nao encontrado\n");
        }
        return;   
    }
    if (k[t->NO.NInterno.Index-1] < t->NO.NInterno.Referencia){ /*Vai cair aqui se estivermos em um nó interno. Para esse caso, se a posição Index-1 (que é o índicie armazenado no nó interno) da palavra for menor que a referência do nó interno, vamos procurar no filho a esquerda desse nó*/
        Pesquisa(k, t->NO.NInterno.Esq);
    } else { /*Caso contrário, procuraremos no filho à direita*/
        Pesquisa(k, t->NO.NInterno.Dir);
    }
} 

TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i){ //acho que ok
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) {
        p = CriaNoExt(k);/* cria um novo no externo */

        if(!(EExterno(*t))){
            if (k[i-1] < (*t)->NO.NInterno.Referencia){ 
                return (CriaNoInt(i, t, &p, k[i-1]));
            } else { 
                return (CriaNoInt(i, &p, t, k[i-1]));
            }
        } 
       
        if (k[i-1] >= (*t)->NO.Chave[i-1]){ 
            return (CriaNoInt(i, t, &p, k[i-1]));
        } else { 
            return (CriaNoInt(i, &p, t, (*t)->NO.Chave[i-1]));
        }
    } 
    else { 
        if (k[(*t)->NO.NInterno.Index-1] >= (*t)->NO.NInterno.Referencia){
            (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i);
        } else {
            (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i);
        }
        return (*t);
  }
}

TipoArvore Insere(Palavra k, TipoArvore *t){ //acho que ok
    TipoArvore p;
    int i;
    if (*t == NULL) {
     
        return (CriaNoExt(k));
    } else { 
        p = *t;
        while (!EExterno(p)) { 
           
            if (k[p->NO.NInterno.Index-1] >= p->NO.NInterno.Referencia){

                p = p->NO.NInterno.Dir;
            } else {
                
                p = p->NO.NInterno.Esq;
            }
        }

        /* acha o primeiro caracter diferente */
        i = 1;
        while (((i <= D) && (k[i-1] == p->NO.Chave[i-1])) && (k[i-1] != '\0')) i++;     

        if (i > D || (k[i-1] == '\0')) { 
            printf("Erro: chave ja esta na arvore\n");  
            return (*t); 
        } else {
            return (InsereEntre(k, t, i));
        }
    }
}

int main(){

    TipoArvore arvteste = NULL;

    int novaspalavras, numpesquisas;

    printf("Quantas palavras gostaria de inserir?\n");
    scanf("%d", &novaspalavras);

    Palavra aux;

    for(int i = 0; i < novaspalavras; i++){
        printf("Digite a palavra %d:\n", i);
        scanf("%s", aux);
        
        arvteste = Insere(aux, &arvteste);
    }

    printf("Quantas palavras gostaria de pesquisar?\n");
    scanf("%d", &numpesquisas);

    for(int i = 0; i < numpesquisas; i++){
        printf("Digite a palavra %d:\n", i);
        scanf("%s", aux);
        Pesquisa(aux, arvteste);
    }

    Imprimepat(arvteste);
    ImprimeOrd(arvteste);

    return 0;
} 
