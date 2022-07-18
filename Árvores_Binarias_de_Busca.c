#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Define o nó da árvore
typedef struct no_arvbin{
    int chave;
    struct no_arvbin *fe;
    struct no_arvbin *fd;
} TArvBin;

// Define o nó da pilha
typedef struct pilha
{
    int topo, n;
    int *vet;
}TP;

// Define o nó da fila
typedef struct fila{
  int n; 
  int ini; 
  int tam; 
  TArvBin **vet; 
}TFila;

//--------------------------------------------------------------------PILHAS--------------------------------------------------------------------//

// Cria pilha vazia
TP *TP_cria(void){
    TP *p = (TP *)malloc(sizeof(TP));
    p->topo = 0;
    p->n = 10;
    p->vet = (int *)malloc(sizeof(int) * p->n);
    return p;
}

// Verifica pilha vazia
int TP_vazia(TP *p){
    return p->topo == 0;
}

// Insere elemento na pilha
void TP_push(TP *p, int x){
    if (p->topo == p->n){
        p->n *= 2;
        p->vet = realloc(p->vet, p->n * sizeof(int));
    }
    p->vet[p->topo++] = x;
}

// Remove elemento da pilha
int TP_pop(TP *p){
    if (TP_vazia(p)) exit(1);
    p->topo--;
    return p->vet[p->topo];
}

// Libera pilha
void TP_libera(TP *p){
    free(p->vet);
    free(p);
}

//--------------------------------------------------------------------FILAS--------------------------------------------------------------------//

// Cria fila vazia
TFila *fila_criar(){
  TFila *f=(TFila*)malloc(sizeof(TFila));
  f->n=0;
  f->ini=0;
  f->tam=10;
  f->vet=(TArvBin**)malloc(f->tam*sizeof(TArvBin)); 
  return f;
}

// Verifica fila vazia
int fila_verificar_vazia(TFila *f){
  return f->n==0;
}

// Insere elemento na fila
TFila *fila_inserir (TFila *f, TArvBin *raiz){
    if(f->n==f->tam){
      printf("Fila cheia!");
      return f;
    }else{
      int fim=(f->ini+f->n++)%f->tam;
      f->vet[fim]=raiz;
      return f;
    }
}

TFila *fila_retirar(TFila *f){
  if (fila_verificar_vazia(f)){
    printf("Impossivel remover: Pilha vazia!");
    return f;
  }else{
    f->ini=(f->ini+1)%f->tam;
    f->n--;
    return f;
  }
}

// Libera fila
TFila *fila_liberar(TFila *f){
    free(f);
    return NULL;
}

//--------------------------------------------------------------------ÁRVORES--------------------------------------------------------------------//

// Cria árvore vazia
TArvBin *arvbin_inicializar(){
    return NULL;
}

// Cria nó da árvore
TArvBin *arvbin_criar_no(int chave, TArvBin *fe, TArvBin *fd){
    TArvBin *no = (TArvBin*)malloc(sizeof(TArvBin));
    no->chave = chave;
    no->fe = fe;
    no->fd = fd;
    return no;
}

// Cria árvore balanceada
TArvBin *arvbin_criar_arv(int *chaves, int ini, int fim){
    if (ini > fim) return NULL;
    else{
        int meio = (ini + fim) / 2;
        TArvBin *no = arvbin_criar_no(chaves[meio], NULL, NULL);
        no->fe = arvbin_criar_arv(chaves, ini, meio - 1);
        no->fd = arvbin_criar_arv(chaves, meio + 1, fim);
        return no;
    }
}

// Insere elemento na árvore de busca
TArvBin *arvbin_inserir(TArvBin *raiz, int chave){
    if(raiz == NULL) raiz = arvbin_criar_no(chave, NULL, NULL);
    else if(chave < raiz->chave) raiz->fe = arvbin_inserir(raiz->fe, chave);
    else if(chave > raiz->chave) raiz->fd = arvbin_inserir(raiz->fd, chave);
    else printf("\nInsercao Invalida!");
    return raiz;
}

// Checa se a árvore está vazia
int arvbin_vazia(TArvBin *raiz){
    return (raiz == NULL);
}

// Desaloca a árvore
TArvBin *arvbin_desalocar(TArvBin *raiz){
    if (!arvbin_vazia(raiz)){
        raiz->fe = arvbin_desalocar(raiz->fe);
        raiz->fd = arvbin_desalocar(raiz->fd);
        free(raiz);
    }
    return NULL;
}

// Busca elemento na árvore binária de busca
TArvBin *arvbin_buscar_balanceada(TArvBin *raiz, int chave){
    while(raiz != NULL){
        if(raiz->chave == chave) return raiz;
        else if(raiz->chave > chave) raiz = raiz->fe;
        else raiz = raiz->fd;
    }
    return NULL;
}

TArvBin *arvbin_buscar_balanceada_rec(TArvBin *raiz, int chave){
    if(raiz == NULL) return NULL;
    else if(raiz->chave == chave) return raiz;
    else if(raiz->chave > chave) return arvbin_buscar_balanceada_rec(raiz->fe, chave);
    else return arvbin_buscar_balanceada_rec(raiz->fd, chave);
}

// Busca o maior elemento da árvore
TArvBin *arvbin_buscar_maior(TArvBin *raiz){
    if(raiz == NULL) return NULL;
    else if(raiz->fd == NULL) return raiz;
    else arvbin_buscar_maior(raiz->fd);
}

// Busca o sucessor de um elemento da árvore
TArvBin *arvbin_buscar_sucessor(TArvBin *raiz, int chave){
    if(arvbin_vazia(raiz)) return NULL;
    TArvBin *no = NULL;
    while(raiz != NULL){
        if(raiz->chave > chave){
            no = raiz;
            raiz = raiz->fe;
        } 
        else raiz = raiz->fd;
    }
    if(!no){
        printf("Nao ha sucessor!\n");
        return NULL;
    }
    return no;
}

// Conta os nós da árvore
int arvbin_conta_nos(TArvBin *raiz){
    if (!raiz) return 0;
    return 1+arvbin_conta_nos(raiz->fe)+arvbin_conta_nos(raiz->fd);
}

// Calcula altura da árvore
int arvbin_altura(TArvBin *raiz){
    int alt1, alt2;
    if (arvbin_vazia(raiz)) return 0;
    else{
        alt1 = arvbin_altura(raiz->fe);
        alt2 = arvbin_altura(raiz->fd);
        if (alt1 > alt2) return alt1 + 1;
        else return alt2 + 1;
    }
}

// Remove elemento da árvore
TArvBin *arvbin_remover(TArvBin *raiz, int chave){
    TArvBin *rmc_pt = NULL, *aux_pt;

    if (raiz==NULL) return NULL;
    else if (chave < raiz->chave) raiz->fe = arvbin_remover(raiz->fe,chave);
    else if (chave > raiz->chave) raiz->fd = arvbin_remover(raiz->fd,chave);

    else /*raiz->chave == chave */
    { 
        if ((raiz->fe == NULL) && (raiz->fd == NULL)) //No folha
        { 
            free(raiz);
            raiz = NULL;
        }
        else if (raiz->fd == NULL) // No com subarvore direita vazia
        {
            aux_pt = raiz;
            raiz = raiz->fe;
            free(aux_pt);
        }
        else if (raiz->fe == NULL) // No com subarvore esquerda vazia
        {
            aux_pt = raiz;
            raiz = raiz->fd;
            free(aux_pt);
        }
        else // No interno com duas subarvores nao vazias
        { 
            rmc_pt = arvbin_buscar_maior(raiz->fe);
            raiz->chave = rmc_pt->chave;
            rmc_pt->chave = chave;
            raiz->fe = arvbin_remover(raiz->fe,chave);
        }
    }
    return raiz;
}

//Remove todos os elementos pares em um intervalo
TArvBin *arvbin_remover_intervalo(TArvBin *raiz, int ini, int fim){
	TArvBin *no = raiz;
	if(!no) return NULL;
	else{
		if(no->fe){
			if(no->fe->chave >= ini) arvbin_remover_intervalo(no->fe,ini,fim);
			else arvbin_remover_intervalo(no->fe->fd,ini,fim);
		}
		if(no->chave >= ini && raiz->chave <= fim && (no->chave % 2 == 0)) no = arvbin_remover(no,no->chave);
		if(no->fd){
			if(no->fd->chave <= fim) arvbin_remover_intervalo(no->fd,ini,fim);
			else arvbin_remover_intervalo(no->fd->fe,ini,fim);
		}
		return no;
	}
}

// Imprime a árvore
void _arvbin_imprimir(TArvBin *raiz, int profundidade, int direita){
    int i;
    if (!arvbin_vazia(raiz)){

        if (direita) printf("------>");
        else for (i = 0; i < profundidade; i++) printf(" |         ");

        printf("(%2d)", raiz->chave);

        _arvbin_imprimir(raiz->fd, profundidade + 1, 1);

        for (i = 0; i < profundidade + 1; i++) printf(" |         ");

        printf("\n");

        for (i = 0; i < profundidade + 1; i++) printf(" |         ");
    
        printf("\n");

        _arvbin_imprimir(raiz->fe, profundidade, 0);
    }
    else{

        if (direita) printf("------>NULL\n");
    
        else{
            for (i = 0; i < profundidade; i++) printf(" |         ");
            printf(" |-------->NULL\n");
        }
    }
}

void arvbin_imprimir(TArvBin *raiz){
    if (!arvbin_vazia(raiz)){
        printf("----------------------------------------------------------------\n");
        _arvbin_imprimir(raiz, 0, 0);
        printf("----------------------------------------------------------------\n");
    }
    else printf("\nArvore Vazia!");
}

//Imprime os nós comuns entre duas árvores
void arvbin_imprimir_comuns(TArvBin *raiz1, TArvBin *raiz2){
    if(raiz1){
        arvbin_imprimir_comuns(raiz1->fe, raiz2);
        if(arvbin_buscar_balanceada(raiz2, raiz1->chave)) printf("\n%d == %d", raiz1->chave, arvbin_buscar_balanceada(raiz2, raiz1->chave)->chave);
        arvbin_imprimir_comuns(raiz1->fd, raiz2);
    }
}     

// Verifica se duas árvores são idênticas
int arvbin_identica(TArvBin *a, TArvBin *b){
    if(!a & !b) return 1;
    if(a && b) return (a->chave == b->chave) && arvbin_identica(a->fe,b->fe) && arvbin_identica(a->fd,b->fd);
    else return 0;
}

// Retorna uma cópia da árvore
TArvBin *arvbin_copiar(TArvBin *raiz){
    if (!raiz) return NULL;
    else{
        TArvBin *copia = arvbin_criar_no(raiz->chave, NULL, NULL);
        copia->fe = arvbin_copiar(raiz->fe);
        copia->fd = arvbin_copiar(raiz->fd);
        return copia;
    }
}

// Une duas árvores em uma 
TArvBin *arvbin_unir(TArvBin *raiz1, TArvBin *raiz2){
    if(!raiz2) return raiz1;
	if(!raiz1) return raiz2;
	if(!raiz1 && !raiz2) return NULL;

    TPilha *p = pilha_criar(100,sizeof(TArvBin*));
    TArvBin *no1 = raiz1, *no2 = raiz2;

    pilha_empilhar(p,&raiz2, sizeof(TArvBin*));

    while (!pilha_verificar_vazia(p)){
        
        pilha_desempilhar(p,&no2,sizeof(TArvBin*));

        arvbin_inserir(no1, no2->chave);

        if (no2->fd) pilha_empilhar(p,&(no2->fd),sizeof(TArvBin*));

        if (no2->fe) pilha_empilhar(p,&(no2->fe),sizeof(TArvBin*));
    }
    return no1;
}

TArvBin *arvbin_unir_rec(TArvBin *raiz1, TArvBin *raiz2){
	TArvBin *novo = raiz1;
	if(!raiz2) return raiz1;
	if(!raiz1) return raiz2;
	if(!raiz1 && !raiz2) return NULL;
	else{
		if(raiz2->fe) novo = arvbin_unir_rec(novo,raiz2->fe);
		if(raiz2) novo = arvbin_inserir(novo,raiz2->chave);
		if(raiz2->fd) novo = arvbin_unir_rec(novo,raiz2->fd);
		return novo; 
	}
}

// Retorna um espelho da árvore
TArvBin *arvbin_espelhar(TArvBin *raiz){
    if (!raiz) return NULL;
    else{
        TArvBin *copia = (TArvBin*) malloc(sizeof(TArvBin*));
        copia->chave = raiz->chave;
        copia->fe = arvbin_espelhar(raiz->fd);
        copia->fd = arvbin_espelhar(raiz->fe);
        return copia;
    }
}

// Verifica se a árvore é cheia
int arvbin_cheia(TArvBin *raiz){
    if(!raiz) return 1;
    int nos = arvbin_conta_nos(raiz), altura = arvbin_altura(raiz), max_nos = 0, p = 1;
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < i; j++) p *= 2;
        max_nos += p;
        p = 1;
    }
    if(nos == max_nos) return 1;
    else return 0;
}

// Verifica se a árvore é completa
int arvbin_completa(TArvBin *raiz){
    if(!raiz) return 1;
    int nos = arvbin_conta_nos(raiz), altura = arvbin_altura(raiz), max_nos = 0, min_nos = 1, p = 1;
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < i; j++) p *= 2;
        max_nos += p;
        if(i < altura - 1) min_nos += p;
        p = 1;
    }
    if(nos == min_nos && (arvbin_altura(raiz->fe) == arvbin_altura(raiz->fd)+2 || arvbin_altura(raiz->fd) == arvbin_altura(raiz->fe)+2)) return 0;
    else if(nos <= max_nos && nos >= min_nos) return 1;
    else return 0;
}

// Verifica se a árvore é simétrica
int arvbin_simetrica(TArvBin *raiz){
    if(arvbin_vazia(raiz)) return 0;
    TArvBin *esq = raiz->fe, *dir = arvbin_espelhar(raiz->fd);
    if(arvbin_identica(esq,dir)) return 1;
    else return 0;
}

// Caminhamento em profundidade (pré-ordem)
void arvbin_profundidade(TArvBin *raiz){
    if (raiz){
        printf("\n%d", raiz->chave);
        arvbin_profundidade(raiz->fe);
        arvbin_profundidade(raiz->fd);
    }
}

void arvbin_pre_ordem_nrc(TArvBin *raiz){
    
    TPilha *p = pilha_criar(100,sizeof(TArvBin*));
    TArvBin *no = raiz;

    pilha_empilhar(p,&no, sizeof(TArvBin*));

    while (!pilha_verificar_vazia(p)){
        
        pilha_desempilhar(p,&no,sizeof(TArvBin*));

        printf("%d ",no->chave);

        if (no->fd) pilha_empilhar(p,&(no->fd),sizeof(TArvBin*));

        if (no->fe) pilha_empilhar(p,&(no->fe),sizeof(TArvBin*));
    }
}

// Caminhamento em ordem-simétrica 
void arvbin_ordem_simetrica(TArvBin *raiz){
    if (raiz){
        arvbin_ordem_simetrica(raiz->fe);
        printf("\n%d", raiz->chave);
        arvbin_ordem_simetrica(raiz->fd);
    }
}

void arvbin_ordem_simetrica_nrc(TArvBin *raiz){
    
    TPilha *p = pilha_criar(100,sizeof(TArvBin*));
    TArvBin *no = raiz;

    //Enquanto houver um nó (raiz de uma subárvore) ou existir algum nó na pilha
    while (no || !pilha_verificar_vazia(p)){
        
        //Empilhar todos os nós a esquerda pois o mais profundo a esquerda deve ser visitado primeiro 
        while (no){
            pilha_empilhar(p,&no,sizeof(TArvBin*));
            no = no->fe;
        }

        //Nesse ponto encontrou-se a um nó sem filhos esquerdos
        //Entao podemos desempilhá-lo e imprimir sua informação
        pilha_desempilhar(p,&no,sizeof(TArvBin*));
        printf("%d ",no->chave);
        //Em seguida, deve-se tratar na proxima iteracao a sua subárvore direita, se existir
        no = no->fd;
    }
}

// Caminhamento em pós-ordem
void arvbin_pos_ordem(TArvBin *raiz){
    if (raiz){
        arvbin_pos_ordem(raiz->fe);
        arvbin_pos_ordem(raiz->fd);
        printf("\n%d", raiz->chave);
    }
}

struct no_info{TArvBin * no;
               int vez;};

void arvbin_pos_ordem_nrc(TArvBin *raiz){
    
    TPilha *p = pilha_criar(100,sizeof(struct no_info));
    TArvBin *no = raiz;
    struct no_info no_info;

    //Enquanto houver um nó (raiz de uma subárvore) ou existir algum nó na pilha
    while (no || !pilha_verificar_vazia(p)){
        
        //Empilhar todos os nós a esquerda pois o mais profundo a esquerda deve ser visitado primeiro
        while (no){
            //No primeiro empilhamento do nó ele deve ser marcado como 1
            no_info.no = no;
            no_info.vez = 1;
            pilha_empilhar(p,&no_info,sizeof(struct no_info));
            no = no->fe;
        }

        //Nesse ponto chegou-se a um nó sem filhos esquerdos 
        
        while (!no && !pilha_verificar_vazia(p)){
            //Remove-se o nó corrente  
            pilha_desempilhar(p,&no_info,sizeof(struct no_info));
            int vez = no_info.vez;
            no = no_info.no;
            //Se ele foi empilhado somente uma vez e houver filhos direitos
            if ((vez == 1)&&(no->fd)){
                //Re-empilhar com rótulo 2
                no_info.no = no;
                no_info.vez = 2;
                pilha_empilhar(p,&no_info,sizeof(struct no_info));
                //Tratar antes sua subárvore direita
                no = no->fd;
                //Como no!=NULL a repeticao termina
            }
            else{
                //Se tiver sido empilhado duas vezes então sua subárvore direita e esquerda já foram tratadas
                //Pode-se então imprimir o nó
                //Observe que no=NULL força o tratamento do nó no topo da pilha e evita o rempilhamento de seus filhos
                //esquerdos
                printf("%d ",no->chave);
                no = NULL;
            }            
        }
    }
}

// Caminhamento em largura
void arvbin_largura_nrc(TArvBin *raiz){
    TFila *f = fila_criar();
    TArvBin *no = raiz;
    f = fila_inserir(f,no);

    while(!fila_verificar_vazia(f)){
        if(no->fe) f = fila_inserir(f,no->fe);
        if(no->fd) f = fila_inserir(f,no->fd);
        printf("%d ",no->chave);
        f = fila_retirar(f);
        no = f->vet[f->ini];
    }
}

//Imprime todos os elementos em um intervalo
void arvbin_imprimir_intervalo(TArvBin *raiz, int ini, int fim){
	if(raiz){
		if(raiz->fe){
			if(raiz->fe->chave >= ini) arvbin_imprimir_intervalo(raiz->fe,ini,fim);
			else arvbin_imprimir_intervalo(raiz->fe->fd,ini,fim);
		}
		if(raiz->chave >= ini && raiz->chave <= fim) printf("%d ", raiz->chave);
		if(raiz->fd){
			if(raiz->fd->chave <= fim) arvbin_imprimir_intervalo(raiz->fd,ini,fim);
			else arvbin_imprimir_intervalo(raiz->fd->fe,ini,fim);
		}
	}
}

//Função Main
int main(void){
    
}