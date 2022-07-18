#include <stdio.h>
#include <stdlib.h>

//Define o nó
typedef struct lde{
    int chave;
    struct lde *prox, *ant;
}TLDE;

//Cria a lista vazia
TLDE* TLDE_inicializar(void){
    return NULL;
}

//Cria nó da lista
TLDE* TLDE_criar_no(int chave){
  TLDE *novo = (TLDE*)malloc(sizeof(TLDE));
  novo->chave = chave;
  novo->prox = NULL;
  novo->ant = NULL;

  return novo;
}

//Insere elemento no início
TLDE* TLDE_ins_ini(TLDE *l, int chave){
    TLDE *novo = (TLDE*) malloc(sizeof(TLDE));
    novo->chave = chave;
    novo->prox = l;
    novo->ant = NULL;
    if(l) l->ant = novo;
    return novo;
}

//Insere elemento no final
TLDE* TLDE_ins_fim(TLDE *l, int chave){
    TLDE *p = l, *novo = (TLDE*) malloc(sizeof(TLDE));
    novo->chave = chave;
    if(!p){
        novo->prox = NULL;
        novo->ant = NULL;
        l = novo;
    }
    else{
        while(p->prox){
            p = p->prox;
        }
        p->prox = novo;
        novo->prox = NULL;
        novo->ant = NULL;
    }
    return l;
}

//Imprime a lista
void TLDE_imprimir(TLDE *l){
    while(l){
        printf("%d\n",l->chave);
        l = l->prox;
    }
}

//Imprime a versão reversa da lista
void TLDE_imprimir_rev(TLDE *l){
    TLDE *p = l; 
    if (p){
        while (p->prox){
            p = p->prox;   
        }
        while (p){
            printf("%d\n",p->chave);
            p = p->ant;
        }
    }
}

//Busca a primeira vez de x
TLDE* TLDE_buscar(TLDE *l,int chave){
    TLDE *resp = l;
    while((resp) && (resp->chave != chave)){
        resp = resp->prox;
    }
    return resp;
}

//Liberação da Lista
void TLDE_liberar(TLDE *l){
    TLDE *p = l, *q;
    while(p){
        q = p;
        p = p->prox;
        free(q);
    }
}

//Retira a primeira vez de x
TLDE* TLDE_retirar(TLDE *l, int chave){
    TLDE *p = TLDE_buscar(l, chave);
    if(!p) return l;
    if(p == l) l = l->prox;
    else p->ant->prox = p->prox;
    if(p->prox) p->prox->ant = p->ant;
    free(p);
    return l;
}

//Insere antes de um nó
TLDE* TLDE_ins_antes(TLDE *no, TLDE *novo){
    novo->prox = no;
    if (no->ant){
        no->ant->prox = novo;
    }
    novo->ant = no->ant;   
    no->ant = novo;

    return novo;
    
}

//Insere após um nó
TLDE* TLDE_ins_apos(TLDE *no, TLDE *novo){
    novo->prox = no->prox;
    novo->ant = no;
    if (no->prox){
        no->prox->ant = novo;
    }
    no->prox = novo;

    return novo;
}

//Inserção ordenada de x
TLDE* TLDE_ins_ord(TLDE *l, int chave){
  TLDE *novo = (TLDE*)malloc(sizeof(TLDE));//criar o novo nó
  novo->chave = chave;

  if (!l){//Insercao em lista vazia
      novo->prox = NULL;
      novo->ant = NULL;
      return novo;
  }
  else if (l->chave > chave){//Insercao no inicio
      novo->prox = l;
      novo->ant = NULL;
      l->ant = novo;
      return novo;
  }
  else{
      TLDE *ant = l; //Busca o ponto de insercao a partir do segundo nó
      while ((ant->prox) && (ant->prox->chave <= chave)){
          ant = ant->prox;
      }

      TLDE_ins_apos(ant,novo);
  }
  return l;
}

//Copia a lista
TLDE* TLDE_copiar(TLDE *l){
    if (!l) return NULL;

    // Criar a cabeça da lista e guarda no último inserido (ult)
    TLDE *ult, *nova_l = ult = TLDE_criar_no(l->chave);

    // Percorre a lista original a partir do próximo elemento
    TLDE *p = l->prox;
    while (p){
        TLDE_ins_apos(ult,TLDE_criar_no(p->chave));
        ult  = ult->prox;
        p = p->prox;
    }

    return nova_l;
}

int main(void){
    
}
