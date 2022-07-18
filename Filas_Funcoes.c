#include <stdio.h>
#include <stdlib.h>

//Define o nó
typedef struct fila{
    int n, ini, tam;
    int *vet;
}TF;

//Inicializa a fila vazia
TF* TF_criar(void){
    TF *f = (TF*) malloc(sizeof(TF));
    f->tam = 1;
    f->vet = (int*) malloc(sizeof(int));
    f->n = f->ini = 0;
    return f;
}

//Resto
int incr(int ind, int n){
    return (ind + 1) % n;
}

//Verifica fila vazia
int TF_vazia(TF *f){
    return f->n == 0;
}

//Insere elemento na fila
void TF_inserir(TF *f, int x){
    if(f->n == f->tam){
        int *vet = (int*) malloc(sizeof(int) * f->n * 2);
        int i = f->ini, j = 0;
        while(j < f->n){
            vet[j++] = f->vet[i];
            i = incr(i, f->tam);
        }
        f->ini = 0;
        f->tam *= 2;
        int *aux = f->vet;
        f->vet = vet;
        free(aux);
    }
    int fim = (f->ini + f->n++) % f->tam;
    f->vet[fim] = x;
}

//Retira elemento da fila
int TF_retirar(TF *f){
    if(TF_vazia(f)) exit(1);
    int resp = f->vet[f->ini];
    f->ini = incr(f->ini, f->tam);
    f->n--;
    return resp;
}

//Libera a fila
void TF_liberar(TF *f){
    free(f->vet);
    free(f);
}

//Imprime a fila
void TF_imprimir(TF *f){
    int ind = f->ini, i;
    for(i = 0; i < f->n; i++){
        printf("%d -> %d\n", i + 1, f->vet[ind]);
        ind = incr(ind, f->tam);
    }
}

int main(void){
    
}
