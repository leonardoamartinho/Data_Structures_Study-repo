#include <stdio.h>
#include <stdlib.h>
#define TAM 9
#define C1 1
#define C2 2

//Define o aluno
typedef struct aluno{
    int mat;
    float cr;
}TA;

//Define a tabela
typedef TA* Hash[TAM];

//Função Hash
int hash(int mat, int n){
    return mat % n;
}

//Cria um aluno
TA *aloca(int mat, float cr){
    TA *novo = (TA*) malloc(sizeof(TA));
    novo->mat = mat;
    novo->cr = cr;
    return novo;
}

//Inicializa a tabela vazia
void inicializa(Hash tab, int n){
    int i;
    for(i = 0; i < n; i++) tab[i] = NULL;
}

//Libera a tabela
void libera(Hash tab, int n){
    int i;
    for(i = 0; i < n; i++) free(tab[i]);
}

//Imprime a tabela
void imprime(Hash tab, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d: ", i);
        if(tab[i]) printf("%d\t%.1f\n", tab[i]->mat, tab[i]->cr);
        else printf("NULL\n");
    }
}

//Tentativa Linear
int tent_linear(int mat, int n, int pos){
    return (hash(mat,n) + pos) % n;
}

//Tentativa Quadrática
int tent_quad(int mat, int n, int pos){
    return (hash(mat,n) + C1 * pos + C2 * (pos*pos)) % n;
}

//Dispersão Dupla
int disp_dupla(int mat, int n, int pos){
    return (hash(mat,n) + pos * hash(mat,n)) % n;
}

//Busca elemento na tabela
TA* busca(Hash tab, int n, int mat){
    int i=0;
    while(i<n){
        int h=tent_linear(mat,n,i++);
        if((tab[h]) && (tab[h]->mat == mat)) return tab[h];
        if(i==n) return NULL;
    }
}
//Insere elemento na tabela
void insere(Hash tab, int n, int mat, float cr){
    int i = 0, achou = 0, primPosLivre, h;
    while(i < n){
        h = tent_linear(mat, n, i++);
        if(tab[h]){
            if(tab[h]->mat == mat){
                tab[h]->cr = cr;
                return;
            }
        }
        else if (!achou){
            achou = i;
            primPosLivre = h;
        }
        if(i == n) break;
    }
    tab[primPosLivre] = aloca(mat,cr);
}

//Remove elemento da tabela
float retira(Hash tab, int n, int mat){
    float cr = -1;
    int i = 0, h;
    while(i < n){
        h = tent_linear(mat, n, i++);
        if(tab[h]){
            if(tab[h]->mat == mat){
                cr = tab[h]->cr;
                free(tab[h]);
                tab[h] = NULL;
                return cr;
            }
        }
        if(i == n) return cr;
    }
}

/*Questão 02
0: 10
1: 28
2: 19
3: 20
4: 12
5: 5
6: 15
7: 33
8: 17

pos = 0;
(hash(mat,n) + pos) % n
*/

//Main
int main(void){
    /**/
    Hash TED;
    inicializa(TED,TAM);
    insere(TED,TAM,5,1);
    insere(TED,TAM,28,1);
    insere(TED,TAM,19,1);
    insere(TED,TAM,15,1);
    insere(TED,TAM,20,1);
    insere(TED,TAM,33,1);
    insere(TED,TAM,12,1);
    insere(TED,TAM,17,1);
    insere(TED,TAM,10,1);
    imprime(TED,TAM);
    libera(TED,TAM);
    TA* guga = busca(TED,20,TAM);
    printf("\n%d\n",guga->mat);
    return 0;
}