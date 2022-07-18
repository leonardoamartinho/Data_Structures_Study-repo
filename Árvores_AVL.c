#include"stdio.h"
#include"stdlib.h"

// Define o nó da árvore
typedef struct no_avl{
    int chave;
    int bal;
    struct no_avl * fe;
    struct no_avl * fd;
}TNoAVL;

// Checa se a árvore é vazia
int avl_vazia(TNoAVL * raiz){
    return raiz == NULL;
}

// Desaloca a árvore
TNoAVL *avl_liberar(TNoAVL *raiz){
    if (!avl_vazia(raiz)){
        raiz->fe = avl_liberar(raiz->fe);
        raiz->fd = avl_liberar(raiz->fd);
        free(raiz);
    }
    return NULL;
}

// Imprime a árvore
void _avl_imprimir(TNoAVL *raiz, int profundidade , int direita){
    int i;
    if (!avl_vazia(raiz)){
            if (direita){
                printf("-------->");
            }
            else{
                for (i=0;i<profundidade;i++){
                    printf("   |            ");
                }
            }
            printf("(%2d %+d)",raiz->chave, raiz->bal);
            _avl_imprimir(raiz->fd,profundidade+1,1);
            for (i=0;i<profundidade+1;i++){
                printf("   |            ");
            }
            printf("\n");
            for (i=0;i<profundidade+1;i++){
                printf("   |            ");
            }
            printf("\n");
            _avl_imprimir(raiz->fe,profundidade,0);
    }
    else{
        if (direita){
            printf("-------->NULL\n");
            }
        else{
            for (i=0;i<profundidade;i++){
                printf("   |            ");
            }
            printf("   |----------->NULL\n");
        }
    }
}

void avl_imprimir(TNoAVL *raiz){
    printf("----------------------------------------------------------------\n");
    _avl_imprimir(raiz,0,0);
    printf("----------------------------------------------------------------\n");
}

// Cria a árvore
TNoAVL *avl_criar(int chave){
    TNoAVL *no = (TNoAVL*) malloc(sizeof(TNoAVL));
    no->chave = chave;
    no->fe = NULL;
    no->fd = NULL;
    no->bal = 0;
    return no;
}

/* Transformacoes de rotacao */

/* Rotacao direita 
    alt(pt->fe)>alt(pt->fd) caso 1
    alt(ptu->fe)>alt(ptu->fd)  caso 1.1 
   
              caso 1             caso 1.1
  
              pt (-1)               pt               ptu (0) 
             /  \                  /  \             /  \
           ptu   T3       ->     ptu   T3  ->     T1    pt (0)
           / \                   / \              |     /  \
         T1   T2               T1   T2            q    T2  T3 
                                |          
                                q
*/

// Rotação direita
TNoAVL * rot_dir(TNoAVL *pt, TNoAVL *ptu){
    pt->fe = ptu->fd;
    ptu->fd = pt;
    return ptu;
}

void bal_rot_dir(TNoAVL *pt,TNoAVL *ptu){
    pt->bal = 0;
    ptu->bal = 0;
}

/* Rotacao direita delecao c (observe pode ser bal(ptu)<=0 e nao somente -1 como na remocao )
    alt(pt->fe)>alt(pt->fd) caso 1
    alt(ptu->fe)>alt(ptu->fd)  caso 1.1 
   
              caso 1             caso 1.1
  
              pt (-1)               pt               ptu (1) 
             /  \                  /                /  \
           ptu   c       ->      ptu        ->     a   pt (-1)
           / \                   / \                   / 
          a   b                 a   b                 b    
                                          
                            

*/

void bal_rot_dir_del(TNoAVL *pt,TNoAVL *ptu){
    if (ptu->bal==0){
        pt->bal = -1;
        ptu->bal = 1;
    }
    else{
        pt->bal = 0;
        ptu->bal = 0;
    }
}

/* Rotacao esq 
   alt(pt->fe)<alt(pt->fd) caso 2
   alt(ptu->fe)<alt(ptu->fd)  caso 2.1 
   

              caso2              caso2.1

              pt (1)                pt                ptz (0) 
             /  \                  /  \              /  \
           T1   ptz       ->      T1  ptz  ->      pt    T3 (0)
                / \                   / \          / \    |
              T2   T3               T2   T3      T1   T2 (q)
                                          |
                                         (q)  
                              
*/

// Rotação esquerda
TNoAVL * rot_esq(TNoAVL *pt, TNoAVL *ptz){
    pt->fd = ptz->fe;
    ptz->fe = pt;
    return ptz;
}

void bal_rot_esq(TNoAVL *pt, TNoAVL *ptz){
    pt->bal = 0;
    ptz->bal = 0;
}

/* Rotacao esq delecao c (observe que bal(ptz)>= 0 e nao somente 1 como na insercao)
   alt(pt->fe)<alt(pt->fd) caso 2
   alt(ptu->fe)<alt(ptu->fd)  caso 2.1 
   

              caso2              caso2.1

              pt (1)                pt                ptz (-1) 
             /  \                     \              /  \
            c   ptz       ->          ptz  ->    (1)pt   b  
                / \                   / \            \    
               a   b                 a   b            a  
                                          
                                          
                              
*/

void bal_rot_esq_del(TNoAVL *pt, TNoAVL *ptz){
    if (ptz->bal==0){
        pt->bal = 1;
        ptz->bal = -1;
    }
    else{
        pt->bal = 0;
        ptz->bal = 0;
    }
}

/* Rotacao direita dupla
    alt(pt->fe)>alt(pt->fd) caso 1
    alt(ptu->fe)<alt(ptu->fd)  caso b 
   



              pt (-1)               pt                      pt                    ptv (0)
             /  \                  /  \                    /  \                  /   \
           ptu   T3       ->     ptu   T3  ->            ptv   T3 (0)   ->     ptu    pt (1)
           / \                   / \                     / \                   / \    / \
         T1   T2               T1  ptv(-1 ou 1))       ptu  T2b              T1  T2a T2b T3
               |                   / \                 / \                        | 
               q                 T2a  T2b            T1  T2a                      q
                                  |   [|]                 | 
                                  q   [q]                 q      

*/

// Rotação direita dupla
TNoAVL * rot_dir_dup(TNoAVL *pt, TNoAVL *ptu){
    TNoAVL *ptv = ptu->fd;
    ptu->fd = ptv->fe;
    ptv->fe = ptu;
    pt->fe = ptv->fd;
    ptv->fd = pt;
    return ptv;
 }

void bal_rot_dir_dup(TNoAVL *pt, TNoAVL *ptu, TNoAVL *ptv){

    if (ptv->bal == -1){
        pt->bal = 1;
    }
    else{
        pt->bal =0;
    }

    if (ptv->bal == 1){
        ptu->bal = -1;
    }
    else{
        ptu->bal = 0;
    }

    ptv->bal = 0;
}

void bal_rot_dir_dup_del(TNoAVL *pt, TNoAVL *ptu, TNoAVL *ptv){

    if (ptv->bal == -1){
        pt->bal = 1;
    }
    else{
        pt->bal =0;
    }

    if (ptv->bal == 1){
        ptu->bal = -1;
    }
    else{
        ptu->bal = 0;
    }

    ptv->bal = 0;
}


/* Rotacao esquerda dupla
    alt(pt->fe)<alt(pt->fd) caso 2
    alt(ptz->fe)>alt(ptz->fd)  caso b 
   



              pt (-1)               pt                    pt                    pty (0)
             /  \                  /  \                  /  \                  /   \
            T1  ptz       ->     T1   ptz     ->       T1   pty (0)   ->     pt(0) ptz (-1)
                / \                   / \                   / \              / \    / \    
              T2   T3    (-1 ou 1)) pty   T3            T2a ptz           T1 T2a T2b T3
              |                     / \                 |   / \               | 
              q                   T2a  T2b              q  T2b  T3            q   
                                   |   [|]                 
                                   q   [q]                      

*/

// Rotação esquerda dupla
TNoAVL *rot_esq_dup(TNoAVL *pt, TNoAVL *ptz){
    TNoAVL *pty = ptz->fe;
    ptz->fe = pty->fd;
    pty->fd = ptz;
    pt->fd = pty->fe;
    pty->fe = pt;
    return pty;
}

void bal_rot_esq_dup(TNoAVL *pt, TNoAVL *ptz, TNoAVL *pty){


    if (pty->bal == 1){
        pt->bal = -1;
    }
    else{
        pt->bal =0;
    }

    if (pty->bal == -1){
        ptz->bal = 1;
    }
    else{
        ptz->bal = 0;
    }
    pty->bal = 0;
}

void bal_rot_esq_dup_del(TNoAVL *pt, TNoAVL *ptz, TNoAVL *pty){


    if (pty->bal == 1){
        pt->bal = -1;
    }
    else{
        pt->bal =0;
    }

    if (pty->bal == -1){
        ptz->bal = 1;
    }
    else{
        ptz->bal = 0;
    }
    pty->bal = 0;
}


//Casos de Inserção
TNoAVL * caso1(TNoAVL *raiz, int *mudouAltura){
    TNoAVL *pt,*ptu,*ptv;

    pt  = raiz;
    ptu = raiz->fe;
    ptv = ptu->fd;

    if (ptu->bal==-1){ /*alt(ptu->fe) > alt(ptu->fd)*/ 
        raiz = rot_dir(pt,ptu);
        bal_rot_dir(pt,ptu);

    }
    else{ /*alt(ptu->fe) > alt(ptu->fd)*/ 
        raiz = rot_dir_dup(pt,ptu);
        bal_rot_dir_dup(pt,ptu,ptv);
    }

    *mudouAltura = 0;

    return raiz;
}


TNoAVL *caso2(TNoAVL *raiz, int *mudouAltura){
    TNoAVL *pt,*ptz,*pty;

    pt = raiz;
    ptz = raiz->fd;
    pty = ptz->fe;

    if (ptz->bal==1){ /*alt(ptz->fd) > alt(ptz->fe) */ 
        raiz = rot_esq(pt,ptz);
        bal_rot_esq(pt,ptz);

    }
    else{ /*alt(ptz->fe) > alt(ptz->fd)*/ 
        raiz = rot_esq_dup(pt,ptz);
        bal_rot_esq_dup(pt,ptz,pty);

    }
    *mudouAltura = 0;

    return raiz;
}

/* Removal cases */


TNoAVL *caso1Del(TNoAVL *raiz, int *mudouAltura){
    TNoAVL *pt,*ptu,*ptv;

    pt  = raiz;
    ptu = raiz->fe;
    ptv = ptu->fd;

    if (ptu->bal<=0){ /*left subtree of u > right subtree of u*/ /*right rotation */
        raiz = rot_dir(pt,ptu);
        bal_rot_dir_del(pt,ptu);

    }
    else{ /*right subtree of u > left subtree of u*/ /*double right rotation */
        raiz = rot_dir_dup(pt,ptu);
        bal_rot_dir_dup_del(pt,ptu,ptv);

    }

    *mudouAltura = 0;

    return raiz;
}


TNoAVL *caso2Del(TNoAVL *raiz, int *mudouAltura){
    TNoAVL *pt,*ptz,*pty;

    pt = raiz;
    ptz = raiz->fd;
    pty = ptz->fe;

    if (ptz->bal>=0){ /*right subtree of z > left subtree of z*/ /*left rotation */
        raiz = rot_esq(pt,ptz);
        bal_rot_esq_del(pt,ptz);

    }
    else{ /*left subtree of z > right subtree of z*/ /*double left rotation */
        raiz = rot_esq_dup(pt,ptz);
        bal_rot_esq_dup_del(pt,ptz,pty);
    }
    *mudouAltura = 0;

    return raiz;
}



//Busca o maior elemento da árvore 
static TNoAVL * busca_filho_mais_a_direita(TNoAVL *raiz){

   if (raiz==NULL) return NULL;

   while (raiz->fd != NULL) raiz = raiz->fd;

   return raiz;
}



// Remove elemento da árvore
TNoAVL *_avl_remover(TNoAVL *raiz, int chave, int *mudouAltura){
    TNoAVL *rmc_pt = NULL, *aux_pt;

    if (raiz==NULL){
        *mudouAltura = 0;
        return NULL;
    }
    else if (chave<raiz->chave){
        raiz->fe = _avl_remover(raiz->fe,chave,mudouAltura);
        if (*mudouAltura){
            switch(raiz->bal){
                case -1: raiz->bal = 0; *mudouAltura = 1;
                break;
                case 0: raiz->bal = 1; *mudouAltura = 0;
                break;
                case 1: raiz = caso2Del(raiz,mudouAltura); *mudouAltura = 1;
                break;
            }
        }
    }
    else if (chave>raiz->chave){
        raiz->fd = _avl_remover(raiz->fd,chave,mudouAltura);
        if (*mudouAltura){
            switch(raiz->bal){
                case 1: raiz->bal = 0; *mudouAltura = 1;
                break;
                case 0: raiz->bal = -1; *mudouAltura = 0;
                break;
                case -1: raiz = caso1Del(raiz,mudouAltura); *mudouAltura = 1;
                break;
            }
        }
    }
    else{/*raiz->chave == chave */
        if ((raiz->fe == NULL)&&(raiz->fd == NULL)){
            free(raiz);
            raiz = NULL;
            *mudouAltura = 1;
        }
        else if (raiz->fd == NULL){
            aux_pt = raiz;
            raiz = raiz->fe;
            free(aux_pt);
            *mudouAltura = 1;
        }
        else if (raiz->fe == NULL){
            aux_pt = raiz;
            raiz = raiz->fd;
            free(aux_pt);
            *mudouAltura = 1;
        }
        else{
            rmc_pt = busca_filho_mais_a_direita(raiz->fe);
            raiz->chave = rmc_pt->chave;
            rmc_pt->chave = chave;
            raiz->fe = _avl_remover(raiz->fe,chave,mudouAltura);
            if (*mudouAltura){
                switch(raiz->bal){
                    case -1: raiz->bal = 0; *mudouAltura = 1;
                    break;
                    case 0: raiz->bal = 1; *mudouAltura = 0;
                    break;
                    case 1: raiz = caso2Del(raiz,mudouAltura); *mudouAltura = 1;
                    break;
                }
            }
        }
    }
    return raiz;
}

TNoAVL *avl_remover(TNoAVL *raiz, int chave){
    int mudouAltura;
    return _avl_remover(raiz,chave,&mudouAltura);
}

// Insere elemento na árvore
TNoAVL *_avl_inserir(TNoAVL *raiz, int chave, int *mudouAltura){

    if (avl_vazia(raiz)){
        raiz = avl_criar(chave);
        *mudouAltura = 1;
    }
    else if(chave==raiz->chave){
        return raiz;
    }
    else if (chave<raiz->chave){
        raiz->fe = _avl_inserir(raiz->fe,chave,mudouAltura);
        if (*mudouAltura){
            switch(raiz->bal){
                case 1: raiz->bal = 0; *mudouAltura = 0; //equilibrou 1 + (-1)
                break;
                case 0: raiz->bal = -1; // 0 + (-1)
                break;
                case -1: raiz = caso1(raiz,mudouAltura); //desbalanceou -1 + (-1)
                break;
            }
        }

    }
    else{
        raiz->fd = _avl_inserir(raiz->fd,chave,mudouAltura);
        if (*mudouAltura){
            switch(raiz->bal){
                case -1: raiz->bal = 0; *mudouAltura = 0; // -1 + (1)
                break;
                case 0: raiz->bal = 1; // 0 + (1)
                break;
                case 1: raiz = caso2(raiz,mudouAltura); //desbalanceou 1 + (1)
                break;
            }
        }
    }
    return raiz;
}

TNoAVL *avl_inserir(TNoAVL *raiz, int chave){
    int mudouAltura;
    return _avl_inserir(raiz,chave,&mudouAltura);
}

// Busca elemento na árvore
TNoAVL *avl_buscar(TNoAVL *raiz, int chave){
    TNoAVL * pt;

    if (avl_vazia(raiz)) pt = NULL;

    else if (raiz->chave == chave) pt = raiz;

    else if (chave < raiz->chave) pt = avl_buscar(raiz->fe,chave);

    else pt = avl_buscar(raiz->fd,chave);

    return pt;
}

int main(void){
    return 0;
}