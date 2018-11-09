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

int maior(char p1[], char p2[]){
    return 1;
}

No *inserir(char palavra[], No *arv){
    No *novo = criar_no(palavra);
    if(arv==NULL){
        return novo;
    }
    if(maior(palavra, arv->palavra)>0)
        arv->dir = inserir(palavra, arv->dir);
    else if(maior(palavra, arv->palavra)<0)
        arv->esq = inserir(palavra, arv->esq);
    return arv;
}

No *criar_arv_proibidas(char lista[32][9]){
    No *arv = NULL;
    for(int i=0; i<32; i++){
        arv = inserir(lista[i], arv);
    }
    return arv;
}

int reservada(char palavra[MAIORPALAVRA], char lista[32][9]){
    return 1;
}

int main(){
    char proibidas[32][9] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    No *arv_proibidas = criar_arv_proibidas(proibidas);
    No *arv = NULL;
    char palavra[MAIORPALAVRA];
    do{
        scanf("%[^#<> {};*():,=-""''%]", palavra);
        printf("%s", palavra);
        if(reservada(palavra, proibidas)){
            arv = inserir(palavra, arv);
            //verificar(arvore);
        }
    }while(palavra[0]!=EOF);

    return 0;
}
