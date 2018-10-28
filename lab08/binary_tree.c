#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    int num;
    struct No *esq, *dir, *pai;
}No;

No *Inserir(No *arv, No *pai, int num){
    No *no = (No*) malloc(sizeof(No));
    if(arv==NULL){
        no->num = num;
        no->esq = NULL;
        no->dir = NULL;
        no->pai = pai;
        return no;
    }
    if(num < arv->num){
        arv->esq = Inserir(arv->esq, arv, num);
        return arv;
    }
    else{
        arv->dir = Inserir(arv->dir, arv, num);
        return arv;
    }
}

void print_in(No *arv){
    if(arv->esq!=NULL){
        print_in(arv->esq);
    }
    else{
        printf("%d")
    }
}

int main(){
    int N, num;
    char OR[3];
    scanf(" %d%s", &N, OR);
    while(N!=0 && OR[0]!='0'){
        No *arv = NULL;
        for(int i=0; i<N; i++){
            scanf(" %d", &num);
            arv = Inserir(arv, NULL, num);
        }
        if(OR[1]=='i'){
            print_in(arv);
        }
        scanf(" %d%s", &N, OR);
    }
    return 0;
}
