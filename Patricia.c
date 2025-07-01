//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 5891
// Pedro Miranda - 4912

#include <stdlib.h>

#include "Patricia.h"

TipoArvore ProcuraExterno(TipoArvore p, Palavra k){
    while (!EExterno(p)) {     /*Equanto não for externo, vamos procurando por um*/
        if (k[p->NO.NInterno.Index-1] >= p->NO.NInterno.Referencia){ /*se a posição indice do nó interno da palavra a ser inserida for maior ou igual ao indice vamos procurar pela direita*/
            p = p->NO.NInterno.Dir;
        } else { /*Caso contrário procuramos pela esquerda*/
            p = p->NO.NInterno.Esq;
        }
    }  

    return p;
}

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
        printf("externo - chave %s\n", t->NO.NExterno.Chave);
        LImprime(&t->NO.NExterno.IdInvDaPalavra);
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
        printf("%s - ", t->NO.NExterno.Chave);
        LImprime(&t->NO.NExterno.IdInvDaPalavra);
        printf("\n");
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

TipoArvore CriaNoExt(Palavra k, int IdDoc){ 
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo; 
    strcpy(p->NO.NExterno.Chave, k); 
    FLVazia(&p->NO.NExterno.IdInvDaPalavra);
    LInsere(&p->NO.NExterno.IdInvDaPalavra, IdDoc);
    return p;
}  

void Pesquisa(Palavra k, TipoArvore t){ 
    if (EExterno(t)){ /*Se chegamos em um nó externo, ou ele é a palavra que estamos procurando ou ele não existe na árvore*/
        if (strcmp(k, t->NO.NExterno.Chave) == 0){ 
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


int PesquisaBin(Palavra k, TipoArvore t){ 
    if(t == NULL){
        return 0;
    }
    if (EExterno(t)){ /*Se chegamos em um nó externo, ou ele é a palavra que estamos procurando ou ele não existe na árvore*/
        if (strcmp(k, t->NO.NExterno.Chave) == 0){ 
            return 1;
        } else { 
            return 0;
        }  
    }
    if (k[t->NO.NInterno.Index-1] < t->NO.NInterno.Referencia){ /*Vai cair aqui se estivermos em um nó interno. Para esse caso, se a posição Index-1 (que é o índicie armazenado no nó interno) da palavra for menor que a referência do nó interno, vamos procurar no filho a esquerda desse nó*/
        PesquisaBin(k, t->NO.NInterno.Esq);
    } else { /*Caso contrário, procuraremos no filho à direita*/
        PesquisaBin(k, t->NO.NInterno.Dir);
    }
} 

TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i, int IdDoc){ 
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) { /*Se o nó for externo ou se i for menor que o índicie do nó interno*/
        p = CriaNoExt(k, IdDoc);/* cria um novo no externo */
        TipoArvore aux;

        if(!(EExterno(*t))){ /*Tratamento para caso o nó não seja externo*/
            aux = ProcuraExterno(*t, k); //Caso o nó nao seja externo, ele procura o externo que foi usado para comparar 
        } else {
            aux = *t;
        }
        
        /*Se ele não for externo usamos a própria chave do nó pra comparar com a palavra a ser inserida*/
        if (k[i-1] >= aux->NO.NExterno.Chave[i-1]){ 
            return (CriaNoInt(i, t, &p, k[i-1]));
        } else { 
            return (CriaNoInt(i, &p, t, aux->NO.NExterno.Chave[i-1]));
        }
    } 
    else { /*Caso seja um nó interno que não atende a condição de cima*/
        if (k[(*t)->NO.NInterno.Index-1] >= (*t)->NO.NInterno.Referencia){
            (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i, IdDoc);
        } else {
            (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i, IdDoc);
        }
        return (*t);
  }
}

TipoArvore Insere(Palavra k, TipoArvore *t, int IdDoc){ 
    TipoArvore p;
    int i;
    if (*t == NULL) { /*Caso não tenha nada*/
        return (CriaNoExt(k,IdDoc));
    } else { 
        p = *t;
        
        p = ProcuraExterno(p, k);

        /* acha o primeiro caracter diferente */
        i = 1;
        while (((i <= D) && (k[i-1] == p->NO.NExterno.Chave[i-1])) && (k[i-1] != '\0')) i++; /*Enquanto i não ultrapassar o tamanho máximo da palavra, as posições de k e da palavra do nó externo forem iguais e a string não tiver acabado, continuamos mudando de posição*/ 
        

        if ((k[i-1] == '\0') && (p->NO.NExterno.Chave[i-1] == '\0')) { /*Condições que indicam que a palavra é repetida*/
            LInsere(&p->NO.NExterno.IdInvDaPalavra, IdDoc);
            return (*t); 
        } else {
            return (InsereEntre(k, t, i, IdDoc));
        }
    }
}