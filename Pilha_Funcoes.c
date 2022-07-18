#include<stdio.h>
#include<stdlib.h>

//Define o nó
typedef struct pilha{
    int topo, n;
    int *vet;
}TP;

//Cria pilha vazia
TP* TP_criar(void){
    TP *p = (TP*) malloc(sizeof(TP));
    p->topo = 0;
    p->n = 10;
    p->vet = (int*) malloc(sizeof(int) * p->n);
    return p;
}

//Verifica pilha vazia
int TP_vazia(TP *p){
    return p->topo == 0;
}

//Insere elemento na pilha
void TP_push(TP *p, int x){
    if(p->topo == p->n){
        p->n *= 2;
        p->vet = realloc(p->vet, p->n * sizeof(int));
    }
    p->vet[p->topo++] = x;
}

//Remove elemento da pilha
int TP_pop(TP *p){
    if(TP_vazia(p)) exit(1);
    p->topo--;
    return p->vet[p->topo];
}

//Libera pilha
void TP_liberar(TP *p){
    free(p->vet);
    free(p);
}

//Imprime a pilha
void TP_imprimir(TP *p){
    if(TP_vazia(p)) exit(1);
    int i = 0;
    while(i < p->topo){
        printf("%d\n", p->vet[i]);
        i++;
    }
}

int main(void){
    
}
