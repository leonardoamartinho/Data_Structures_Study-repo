#include <stdio.h>
#include <stdlib.h>

//Define o nó
typedef struct lse{
    int chave;
    struct lse *prox;
}TLSE;

//Cria a lista vazia
TLSE* TLSE_inicializa(void){
    return NULL;
}

//Verifica lista vazia
int TLSE_vazia(TLSE *l){
    return l == NULL;
}

//Insere elemento no início
TLSE* TLSE_ins_ini(TLSE *l, int chave){
    TLSE *novo = (TLSE*) malloc(sizeof(TLSE));
    novo->chave = chave;
    novo->prox = l;
    return novo;
}


//Imprime a lista
void TLSE_imprimir(TLSE* l){
    while(l){
        printf("%d\n", l->chave);
        l = l->prox;
    }
}

//Busca primeira vez de x
TLSE* TLSE_buscar(TLSE *l,int x){
    if (TLSE_vazia(l)) return NULL;
    TLSE *resp = l;
    while((resp) && (resp->chave != x)) resp = resp->prox;
    return resp;
}

//Liberação da lista
void TLSE_liberar(TLSE *l){
    TLSE *p = l, *q;
    while(p){
        q = p;
        p = p->prox;
        free(q);
    }
}

//Retira a primeira vez de x
TLSE* TLSE_retirar(TLSE *l, int chave){
    if(TLSE_vazia(l)) return NULL;
    TLSE *ant = NULL, *p = l;

    while((p) && (p->chave != chave)){
        ant = p;
        p = p->prox;
    }
    if(!ant) l = l->prox;
    else ant->prox = p->prox;

    free(p);
    return l;
}

//Inserção ordenada de x
TLSE* TLSE_ins_ord(TLSE *l, int chave){
    TLSE *p = l, *ant = NULL;
    TLSE *novo = (TLSE*) malloc(sizeof(TLSE));
    novo->chave = chave;

    while((p) && (p->chave < chave)){
        ant = p;
        p = p->prox;
    }
    if(!ant){
        novo->prox = l;
        return novo;
    }
    else{
        novo->prox = ant->prox;
        ant->prox = novo;
        return l;
    }
}

//Inserção no final da lista
TLSE* TLSE_ins_final(TLSE *l, int chave){
    TLSE *p = l, *ant = NULL;
    TLSE *novo = (TLSE*) malloc(sizeof(TLSE));
    novo->chave = chave;

    while(p){
        ant = p;
        p = p->prox;
    }
    if(!ant){
        novo->prox = l;
        return novo;
    }
    else{
        novo->prox = ant->prox;
        ant->prox = novo;
        return l;
    }
}

/* ------------------------------- Versões Recursivas ------------------------------- */

//Imprime a lista
void TLSE_imp_rec(TLSE *l){
    if(l){
        printf("%d\n", l->chave);
        TLSE_imp_rec(l->prox);
    }
}

//Imprime a lista invertida
void TLSE_imp_rec_rev(TLSE *l){
    if(l){
        TLSE_imp_rec_rev(l->prox);
        printf("%d\n", l->chave);
    }
}

//Busca primeira vez de x
TLSE* TLSE_buscar_rec(TLSE *l, int chave){
    if((!l) || (l->chave == chave)) return l;
    return TLSE_buscar_rec(l->prox, chave);
}

//Liberação da lista
void TLSE_liberar_rec(TLSE *l){
    if(l){
        TLSE_liberar_rec(l->prox);
        free(l);
    }
}

//Retira a primeira vez de x
TLSE* TLSE_retirar_rec(TLSE *l, int chave){
    if(!l) return l;
    if(l->chave == chave){
        TLSE *p = l;
        l = l->prox;
        free(p);
    }
    else{
        l->prox = TLSE_retirar_rec(l->prox, chave);
        return l;
    }
}

//Inserção ordenada de x
TLSE* TLSE_ins_ord_rec(TLSE *l, int chave){
    if((!l) || (l->chave >= chave)){
        TLSE *novo = (TLSE*) malloc(sizeof(TLSE));
        novo->chave = chave;
        novo->prox = l;
        return novo;
    }

    l->prox = TLSE_ins_ord_rec(l->prox, chave);
    return l;
}

int main(void){
    
}