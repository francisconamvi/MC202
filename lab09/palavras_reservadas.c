#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAIORPALAVRA 20

typedef struct No{
    char palavra[9];
    int altura;
    struct No *dir, *esq;
}No;

No *criar_no(char palavra[]){ 
    No *novo = (No*) malloc(sizeof(No));
    strcpy(novo->palavra, palavra);
    novo->altura = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void print_in(No *arv){
    if(arv!=NULL){
        print_in(arv->esq);
        printf("%d ", arv->altura);
        print_in(arv->dir);
    }
}

//void zigzag(No *arv, int h){
//    if(h==)
//}

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


int maior(char p1[], char p2[]){
    for(int i=0; i<9; i++){
        if(p1[i]==0 && p2[i]==0) return 0;
        else if(p1[i]==0) return -1;
        else if(p2[i]==0) return 1;
        
        if(p1[i] > p2[i]) return 1;
        else if(p1[i] < p2[i]) return -1;
        else continue;
    }
    return 0;
}

/*Funcoes de rotacao*/
No *rotacao_esq(No *raiz){
    No *nova_raiz = raiz->dir;
    raiz->dir = nova_raiz->esq;
    nova_raiz->esq = raiz;
    return nova_raiz;
}

No *rotacao_dir(No *raiz){
    No *nova_raiz = raiz->esq;
    raiz->esq = nova_raiz->dir;
    nova_raiz->dir = raiz;
    return nova_raiz;
}

No *rotacao_dupla_esq(No *raiz){
    raiz->dir = rotacao_dir(raiz->dir);
    raiz = rotacao_esq(raiz);
    return raiz;
}

No *rotacao_dupla_dir(No *raiz){
    raiz->esq = rotacao_esq(raiz->esq);
    raiz = rotacao_dir(raiz);
    return raiz;
}

No *inserir(char palavra[], No *arv){
    if(arv==NULL){
        No *novo = criar_no(palavra);
        return novo;
    }
    if(maior(palavra, arv->palavra)>0)
        arv->dir = inserir(palavra, arv->dir);
    else if(maior(palavra, arv->palavra)<0)
        arv->esq = inserir(palavra, arv->esq);
    return arv;
}

No *verificar(No *arv){
    if(arv==NULL) return arv;
    
    int Q = altura(arv->dir) - altura(arv->esq);

    if(Q>1){
        int Qr = altura(arv->dir->dir) - altura(arv->dir->esq);
        if(Qr<0)
            arv = rotacao_dupla_esq(arv);
        else
            arv = rotacao_esq(arv);
    }
    else if(Q<-1){
        int Qe = altura(arv->esq->dir) - altura(arv->esq->esq);
        if(Qe>0)
            arv = rotacao_dupla_dir(arv);
        else
            arv = rotacao_dir(arv);
    }

    arv->esq = verificar(arv->esq);
    arv->dir = verificar(arv->dir);
    return arv;


}

int pertence(char *palavra, No *arv){
    if(arv==NULL) return 0;
    if(strcmp(palavra, arv->palavra)==0) return 1;
    if(maior(palavra,arv->palavra)>0)
        return pertence(palavra, arv->dir);
    else
        return pertence(palavra, arv->esq);
}

int att_altura(No **raiz){
    int h_esq, h_dir;
    if ((*raiz)==NULL)
        return 0;
    else{
        h_esq = altura((*raiz)->esq);
        if((*raiz)->esq!=NULL)
            (*raiz)->esq->altura = h_esq;
        h_dir = altura((*raiz)->dir);
        if((*raiz)->dir!=NULL)
            (*raiz)->dir->altura = h_dir;
        (*raiz)->altura = 1 + (h_esq > h_dir ? h_esq : h_dir);
        return (*raiz)->altura;
    }
}

No *criar_arv_proibidas(char lista[32][9]){
    No *arv = NULL;
    for(int i=0; i<32; i++){
        arv = inserir(lista[i], arv);
        arv = verificar(arv);
    }
    return arv;
}


void zerar_palavra(char palavra[]){
    for(int i=0; i<MAIORPALAVRA; i++){
        palavra[i] = 0;
    }
}

int main(){
    char proibidas[32][9] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    No *arv_proibidas = criar_arv_proibidas(proibidas);
    att_altura(&arv_proibidas);
    print_in(arv_proibidas);
    //printf("\n");
    No *arv = NULL;
    int cont=0;
    char *palavra = (char*) malloc(MAIORPALAVRA*sizeof(char));
    char lixo;
    do{
        zerar_palavra(palavra);
        scanf(" %[^#<> {};*():,=-""''%% .+\n]s", palavra);
        scanf("%c", &lixo);
        if(palavra[0]==0){
            cont++;
            if(cont==20) break;
        }
        else cont = 0;
        if(pertence(palavra, arv_proibidas)){
            arv = inserir(palavra, arv);
            arv = verificar(arv);
            //printf("%s\n", palavra);
        }
    }while(1);
    att_altura(&arv);
    //zigzag(arv);
    return 0;
}
