#include <stdio.h>
#include <stdlib.h>

//Define o nó
typedef struct lc{
    int chave;
    struct lc *prox;
}TLC;

//Cria a lista vazia
TLC* TLC_inicializar(void){
    return(NULL);
}

//Verifica lista vazia
int TLC_vazia(TLC *l){
    return l == NULL;
}

//Insere no início da lista
TLC* TLC_ins_ini(TLC *l, int chave){
    TLC *novo = (TLC*) malloc(sizeof(TLC));
    novo->chave = chave;
    if(!l){
        novo->prox = novo;
        return novo;
    }
    if(l->prox = l){
        novo->prox = l;
        l->prox = novo;
        return novo;
    }
    TLC *p = l;
    while(p->prox != l) p = p->prox;
    p->prox = novo;
    novo->prox = l;
    return novo;
}    

//Insere no fim da lista (antes do token)
TLC* TLC_ins_fim(TLC *l, int chave){
    TLC *novo = (TLC*) malloc(sizeof(TLC));
    novo->chave = chave;

    if(!l){
        novo->prox = novo;
        return novo;
    }

    TLC *p = l->prox, *ant = l;
    while(p != l){
        ant = p;
        p = p->prox;
    }
    novo->prox = l;
    ant->prox = novo;
    return l;
}

//Imprime a lista
void TLC_imprimir(TLC *l){
    if(l){
        printf("%d\n", l->chave);
        TLC *p = l->prox;
        while(p != l){
            printf("%d\n", p->chave);
            p = p->prox;
        }
    }
}

//Libera a lista
void TLC_liberar(TLC *l){
    if(l){
        TLC *p = l->prox;
        while(p != l){
            TLC *temp = p;
            p = p->prox;
            free(temp);
        }
        free(l);
    }
}

//Busca a primeira vez de x
TLC* TLC_buscar(TLC *l, int chave){
    if((!l) || (l->chave == chave)) return l;
    TLC *p = l->prox;
    while(p != l){
        if(p->chave == chave) return p;
        p = p->prox;    
    }
    return NULL;
}

//Retira a primeira vez de x
TLC* TLC_retirar(TLC *l, int chave){
    //Caso a lista seja vazia ou se ela for um só nó com a informação
    if((!l) || ((l->prox == l) && (l->chave == chave))){
        if(l) free(l);
        return NULL;
    }
    //Busca pelo elemento a ser retirado
    TLC *p = l->prox, *ant = l;
    while((p != l) && (p->chave != chave)){
        ant = p;
        p = p->prox;
    }
    //Se o elemento não for encontrado
    if((p == l) && (l->chave != chave)) return l;
    //O elemento foi encontrado
    ant->prox = p->prox;
    if(p == l) l = l->prox;
    free(p);
    return l;
}

//Verifica loop
int TLC_verificar_loop(TLC *l){
    if(!l) return 0;
    if(l->prox == l) return 1; 
    TLC *p = l, *v = l;

    while(p){
        while(v != p){
            if(p->prox == v){
                printf("Ha loop");
                return 1;
            }
            else v = v->prox;
        }
        p = p->prox;
        v = l;
    }
    printf("Nao ha loop");
    return 0;
}


/* ------------------------------- Função Main Padrão ------------------------------- */

int main(void){
    
}