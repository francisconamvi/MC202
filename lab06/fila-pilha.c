#include<stdio.h>
#include<stdlib.h>

typedef struct No_Lista{
    int pos;
    char cpf[12];
    char nome[40];
    struct No_Lista *prox;
}No_Lista;

typedef struct Lista{
    No_Lista *inicio;
    No_Lista *fim;
}Lista;

Lista *iniciar_lista(Lista *lista){
    No_Lista *cabeca = (No_Lista*) malloc(sizeof(No_Lista));
    cabeca->pos = 0; /*tamanho da lista*/
    cabeca->prox = NULL;
    lista->inicio = cabeca;
    lista->fim = cabeca;
    return lista;
}

Lista *listar(Lista *lista, No_Lista *novo){
    lista->fim->prox = novo;
    novo->prox = NULL;
    lista->fim = novo;
    lista->inicio->pos++;
    return lista;
}

typedef struct No_Fila{
    int info;
    struct No_Fila *prox;
}No_Fila;

typedef struct Fila{
    No_Fila *inicio;
    No_Fila *fim;
}Fila;




int main(){
    
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista = iniciar_lista(lista);

    char comando[5], num_str[3], lixo;
    int num;
    scanf(" %s", comando);
    while(comando[0] != 'D'){
        if(comando[0] == 'Q' && comando[1] == 'I'){
            num_str[0] = comando[2]; num_str[1] = comando[3];
            num = atoi(num_str);
            for(int i=1;i<=num;i++){
                No_Lista *novo = (No_Lista*) malloc(sizeof(No_Lista));
                novo->pos = i;
                scanf(" %[^,]", novo->cpf);
                scanf(" %c", &lixo); /*Pular a virgula*/
                scanf(" %[^\n]", novo->nome);
                lista = listar(lista, novo);
            }
        }
        scanf(" %s", comando);

    }
    return 0;
}
