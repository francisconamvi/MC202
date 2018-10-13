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

void print_lista(No_Lista *lista){
    if(lista == NULL){
        printf("\n");
        return;
    }
    printf("%d,%s,%s\n", lista->pos, lista->cpf, lista->nome);
    print_lista(lista->prox);
}

typedef struct No_Fila{
    int num;
    struct No_Fila *prox;
}No_Fila;

typedef struct Fila{
    No_Fila *inicio;
    No_Fila *fim;
}Fila;

Fila *iniciar_fila(Fila *fila){
    No_Fila *cabeca = (No_Fila*) malloc(sizeof(No_Fila));
    cabeca->num = 0; /*tamanho da fila*/
    cabeca->prox = NULL;
    fila->inicio = cabeca;
    fila->fim = cabeca;
    return fila;
}

Fila *enfileirar(Fila *fila, No_Fila *novo){
    fila->fim->prox = novo;
    novo->prox = NULL;
    fila->fim = novo;
    fila->inicio->num++;
    return fila;
}

Fila *desenfileirar(Fila *fila){
    No_Fila *novo_inicio = fila->inicio->prox;
    free(fila->inicio);
    fila->inicio = novo_inicio;
    return fila;
}

void print_fila(No_Fila *fila){
    if(fila == NULL){
        printf("\n");
        return;
    }
    printf("%d,", fila->num);
    print_fila(fila->prox);
}


int main(){
    
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista = iniciar_lista(lista);

    Fila *fila = (Fila*) malloc(sizeof(Fila));
    fila = iniciar_fila(fila);

    char comando[5], num_str[3], lixo;
    int num, upl;
    scanf(" %s", comando);
    while(comando[0] != 'D'){
        if(comando[0] == 'P'){
            printf("[Q]");
            print_fila(fila->inicio->prox);
            //print_pilha(pilha);
        }
        else if(comando[0] == 'Q'){
            num_str[0] = comando[2]; num_str[1] = comando[3];
            num = atoi(num_str);
            if(comando[1] == 'I'){
                upl = lista->inicio->pos;
                for(int i=upl+1;i<=upl+num;i++){
                    /*Colocar o nome na lista*/
                    No_Lista *novo_lista = (No_Lista*) malloc(sizeof(No_Lista));
                    novo_lista->pos = i;
                    scanf(" %[^,]", novo_lista->cpf);
                    scanf(" %c", &lixo); /*Pular a virgula*/
                    scanf(" %[^\n]", novo_lista->nome);
                    lista = listar(lista, novo_lista);
                    /*Colocar numero na fila*/
                    No_Fila *novo_fila = (No_Fila*) malloc(sizeof(No_Fila));
                    novo_fila->num = i;
                    fila = enfileirar(fila, novo_fila);
                }
            }
            else if(comando[1] == 'R'){
                for(int i=1;i<=num;i++){
                    /*Tirar da fila*/
                    fila = desenfileirar(fila);
                }
            }
        }
        scanf(" %s", comando);
    }
    print_lista(lista->inicio->prox);

    return 0;
}
