/* Francisco Namias Vicente
 * RA 216028
 * */

#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    int num;
    struct No *esq, *dir;
}No;

/*Funcao para inserir*/
No *Inserir(No *arv, int num){
    if(arv==NULL){
        No *no = (No*) malloc(sizeof(No));
        no->num = num;
        no->esq = NULL;
        no->dir = NULL;
        return no;
    }
    if(num < arv->num){ /*Se for menor que a raiz insere na esquerda*/
        arv->esq = Inserir(arv->esq, num);
        return arv;
    }
    else{ /*Se for maior que a raiz insere na direita*/
        arv->dir = Inserir(arv->dir, num);
        return arv;
    }
}

/*Funcao que retorna a altura de uma arvore*/
int altura (No *raiz){
    int h_esq, h_dir;
    if (raiz==NULL)
        return 0;
    else{
        h_esq = altura(raiz->esq);
        h_dir = altura(raiz->dir);
        return 1 + (h_esq > h_dir ? h_esq : h_dir);
    }
}

/*Funcao que retorna o diametro da arvore*/
int Diametro(No *arv){
    if(arv->esq==NULL && arv->dir==NULL){ /*FOLHA*/
        return 0;
    }
    int desq, ddir, dist;
    /* desq = diametro da subarvore esquerda
     * ddir = diametro da subarvore direita
     * distancia = altura da subarvore direita + altura da subarvore esquerda + 1
     * */
    if(arv->esq == NULL)
        desq = 0;
    else
        desq = Diametro(arv->esq);
    if(arv->dir == NULL)
        ddir = 0;
    else
        ddir = Diametro(arv->dir);
    dist = altura(arv->esq)+altura(arv->dir)+1;
    desq = desq > ddir ? desq : ddir;
    desq = desq > dist ? desq : dist;
    return desq;
}

/*Funcao para printar In Ordem*/
void print_in(No *arv){
    if(arv!=NULL){
        print_in(arv->esq);
        printf("%d ", arv->num);
        print_in(arv->dir);
    }
}

/*Funcao para printar Pre Ordem*/
void print_pre(No *arv){
    if(arv!=NULL){
        printf("%d ", arv->num);
        print_pre(arv->esq);
        print_pre(arv->dir);
    }
}

/*Funcao para printar pos ordem*/
void print_pos(No *arv){
    if(arv!=NULL){
        print_pos(arv->esq);
        print_pos(arv->dir);
        printf("%d ", arv->num);
    }
}

/*Liberar a memoria da arvore*/
No *Liberar(No *arv){
    if(arv->esq==NULL && arv->dir==NULL){
        free(arv);
        return NULL;
    }
    if(arv->esq!=NULL){
        arv->esq = Liberar(arv->esq);
    }
    if(arv->dir!=NULL){
        arv->dir = Liberar(arv->dir);
    }
    free(arv);
    return NULL;
}

int main(){
    int N, num, d; 
    /* N = Numero de Nos na Arvore
     * num = numero do no que sera inserido na arvore
     * d = diametro
     * */
    char OR[3]; /*Ordem que a arvore sera percorrida (IN|PRE|POS)*/
    scanf(" %d%s", &N, OR);
    while(N!=0 && OR[0]!='0'){ /*Condicao de Parada*/
        No *arv = NULL;
        for(int i=0; i<N; i++){
            scanf(" %d", &num);
            arv = Inserir(arv, num); /*Inserir No na arvore*/
        }
        d = Diametro(arv); /*Calcula o diametro da arvore*/
        printf("Diametro da arvore binaria: %d\n", d);
        if(OR[1]=='n'){ /*Ordem IN*/
            print_in(arv);
            printf("\n");
        }
        else if(OR[1]=='r'){ /*Ordem PRE*/
            print_pre(arv);
            printf("\n");
        }
        else if(OR[1]=='o'){ /*Ordem POS*/
            print_pos(arv);
            printf("\n");
        }
        arv = Liberar(arv); /*Libera nos da arvore*/
        free(arv);
        scanf(" %d%s", &N, OR);
    }
    return 0;
}
