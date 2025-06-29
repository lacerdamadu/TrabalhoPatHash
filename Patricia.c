//Ratos Moinhados + Ziviani adaptado
// Ana Clara - 5896
// Maria Eduarda - 5920
// Rafael Resende - 589*
// Pedro Miranda - 4***
#include <ctype.h>
#include "Patricia.h"
#include "Tratamento.h"


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
//mudei umass coisass
void ImprimeOrd(TipoArvore t) {
    if(!t) return;
    
    if(!EExterno(t)) {
        ImprimeOrd(t->NO.NInterno.Esq);
        ImprimeOrd(t->NO.NInterno.Dir);
    } else {
        // Imprime a palavra
        printf("%s - ", t->NO.NExterno.Chave);
        
        // Imprime todos os documentos
        Apontador p = t->NO.NExterno.IdInvDaPalavra.pPrimeiro->pProx;
        while(p != NULL) {
            printf("<%d,%d>", p->Item.Quantidade, p->Item.IdDoc);
            p = p->pProx;
        }
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
//alterei a função de busca para achar melhor o índice invertido, a anterior não era usada como sua estrutura queria
//então optei por alterá-la pra corresponder a necessidade
void Pesquisa(Palavra k, TipoArvore t) {
    if(!t) {
        printf("Palavra não encontrada\n");
        return;
    }

    // Normaliza a palavra de busca
    char busca_normalizada[D];
    strcpy(busca_normalizada, k);
    limpar_linha(busca_normalizada);

    while(!EExterno(t)) {
        if(busca_normalizada[t->NO.NInterno.Index-1] < t->NO.NInterno.Referencia)
            t = t->NO.NInterno.Esq;
        else
            t = t->NO.NInterno.Dir;
    }

    if(strcmp(busca_normalizada, t->NO.NExterno.Chave) == 0) {
        printf("%s - ", t->NO.NExterno.Chave);
        LImprime(&t->NO.NExterno.IdInvDaPalavra);
    } else {
        printf("Palavra não encontrada\n");
    }
}

TipoArvore InsereEntre(Palavra k, TipoArvore *t, int i, int IdDoc){ 
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) { /*Se o nó for externo ou se i for menor que o índicie do nó interno*/
        p = CriaNoExt(k, IdDoc);/* cria um novo no externo */

        if(!(EExterno(*t))){ /*Tratamento para caso o nó não seja externo*/
            if (k[i-1] < (*t)->NO.NInterno.Referencia){ 
                return (CriaNoInt(i, t, &p, k[i-1]));
            } else { 
                return (CriaNoInt(i, &p, t, k[i-1]));
            }
        } 
        
        /*Se ele não for externo usamos a própria chave do nó pra comparar com a palavra a ser inserida*/
        if (k[i-1] >= (*t)->NO.NExterno.Chave[i-1]){ 
            return (CriaNoInt(i, t, &p, k[i-1]));
        } else { 
            return (CriaNoInt(i, &p, t, (*t)->NO.NExterno.Chave[i-1]));
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
        while (!EExterno(p)) {     /*Equanto não for externo, vamos procurando por um*/
            if (k[p->NO.NInterno.Index-1] >= p->NO.NInterno.Referencia){ /*se a posição indice do nó interno da palavra a ser inserida for maior ou igual ao indice vamos procurar pela direita*/
                p = p->NO.NInterno.Dir;
            } else { /*Caso contrário procuramos pela esquerda*/
                p = p->NO.NInterno.Esq;
            }
        }

        /* acha o primeiro caracter diferente */
        i = 1;
        while (((i <= D) && (k[i-1] == p->NO.NExterno.Chave[i-1])) && (k[i-1] != '\0')) i++; /*Enquanto i não ultrapassar o tamanho máximo da palavra, as posições de k e da palavra do nó externo forem iguais e a string não tiver acabado, continuamos mudando de posição*/    

        if (i > D || (k[i-1] == '\0')) { /*Condições que indicam que a palavra é repetida*/
            LInsere(&p->NO.NExterno.IdInvDaPalavra, IdDoc);
            return (*t); 
        } else {
            return (InsereEntre(k, t, i, IdDoc));
        }
    }
}
//função nova pra ver se funciona isso no menu sem duplicar palavra
TipoArvore BuscaPatricia(TipoArvore t, const char *k) {
    if (!t) return NULL;

    char normalizada[D];
    strncpy(normalizada, k, D-1);
    normalizada[D-1] = '\0';
    
    for(int i = 0; normalizada[i]; i++) {
        normalizada[i] = tolower(normalizada[i]);
        if(!isalpha(normalizada[i])) normalizada[i] = '\0';
    }

    while (!EExterno(t)) {
        if (normalizada[t->NO.NInterno.Index-1] < t->NO.NInterno.Referencia)
            t = t->NO.NInterno.Esq;
        else
            t = t->NO.NInterno.Dir;
    }

    char atual_normalizada[D];
    strncpy(atual_normalizada, t->NO.NExterno.Chave, D-1);
    atual_normalizada[D-1] = '\0';
    
    // Normalização da palavra armazenada
    for(int i = 0; atual_normalizada[i]; i++) {
        atual_normalizada[i] = tolower(atual_normalizada[i]);
        if(!isalpha(atual_normalizada[i])) atual_normalizada[i] = '\0';
    }

    return (strcmp(normalizada, atual_normalizada) == 0) ? t : NULL;
}