#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef void* TElem;

typedef struct pilha2{int dim; //tam
                     TElem p; // p é um array implementado como void *p
                     int n; //topo
                     }TPilha;


TPilha *pilha_criar(int dim, size_t tam_elem){
    TPilha * pilha = (TPilha*)malloc(sizeof(TPilha));
    pilha->dim = dim;
    pilha->n=0; //topo
    pilha->p = malloc(pilha->dim*tam_elem);
 
    return pilha;
}

int pilha_verificar_vazia(TPilha *pilha){
    return (pilha->n==0);
}

void pilha_empilhar(TPilha *pilha, TElem e, size_t tam_elem){
    if (pilha->n == pilha->dim){
        pilha->dim *=2;
        pilha->p = (TElem*)realloc(pilha->p, pilha->dim*tam_elem);
    }
    TElem *p = pilha->p; //base da pilha
    int offset = pilha->n*tam_elem; //o que precisamos somar para alcançar o topo
    memcpy(p+offset,e,tam_elem);
    pilha->n++;
}

void pilha_desempilhar(TPilha *pilha, TElem e, size_t tam_elem){
    TElem *p = pilha->p;
    int offset = (pilha->n-1)*(tam_elem);
    memcpy(e,p+offset,tam_elem);
    pilha->n--;
}

TPilha * pilha_liberar(TPilha *pilha){
    free(pilha->p);
    free(pilha);
    return NULL;
}

void pilha_dump(TPilha *pilha, size_t tam_elem, void (*imprimir_elem)(TElem e)){
    printf("conteudo da pilha:");
    for (int i = 0; i<pilha->n;i++){
        TElem * p = (TElem*)(pilha->p);
        imprimir_elem(p+i*tam_elem);
    }
    printf("\n");
}