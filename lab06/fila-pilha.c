/* Francisco Namias Vicente
 * RA 216028
 * */

#include<stdio.h>
#include<stdlib.h>


typedef struct No_Lista{
    int pos; /*Posicao na Lista*/
    char cpf[12];
    char nome[40];
    struct No_Lista *prox;
}No_Lista;

typedef struct Lista{
    /*Preferi usar um ponteiro tanto pro inicio quanto para o fim para facilitar a insercao no final da lista*/
    No_Lista *inicio;
    No_Lista *fim;
}Lista;

Lista *iniciar_lista(Lista *lista){
    /*Lista com cabeca*/
    No_Lista *cabeca = (No_Lista*) malloc(sizeof(No_Lista));
    cabeca->pos = 0; /*tamanho da lista*/
    cabeca->prox = NULL;
    lista->inicio = cabeca;
    lista->fim = cabeca;
    return lista;
}

/*Inserir na lista*/
Lista *listar(Lista *lista, No_Lista *novo){
    lista->fim->prox = novo;
    novo->prox = NULL;
    lista->fim = novo;
    lista->inicio->pos++;
    return lista;
}

void print_lista(No_Lista *lista){
    if(lista == NULL){
        return;
    }
    printf("%d,%s,%s\n", lista->pos, lista->cpf, lista->nome);
    print_lista(lista->prox);
}

typedef struct No_Fila{
    int num; /*numero da pessoa na lista*/
    struct No_Fila *prox;
}No_Fila;

typedef struct Fila{
    No_Fila *inicio;
    No_Fila *fim;
}Fila;

Fila *iniciar_fila(Fila *fila){
    /*Fila com cabeca*/
    No_Fila *cabeca = (No_Fila*) malloc(sizeof(No_Fila));
    cabeca->num = 0; /*tamanho da fila*/
    cabeca->prox = NULL;
    fila->inicio = cabeca;
    fila->fim = cabeca;
    return fila;
}

/*Funcao para inserir no final fila*/
Fila *enfileirar(Fila *fila, No_Fila *novo){
    fila->fim->prox = novo;
    novo->prox = NULL;
    fila->fim = novo;
    fila->inicio->num++;
    return fila;
}

/*Funcao para remover do inicio da fila*/
Fila *desenfileirar(Fila *fila){
    No_Fila *novo_inicio = fila->inicio->prox->prox;
    free(fila->inicio->prox);
    fila->inicio->prox = novo_inicio;
    fila->inicio->num--;
    if(fila->inicio->num==0)
        fila->fim = fila->inicio;
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

typedef struct No_Pilha{
    int num; /*numero da pessoa na lista*/
    int altura; /*altura na pilha*/
    struct No_Pilha *prox;
}Pilha;

/*funcao para inserir no inicio da pilha*/
Pilha **empilhar(Pilha **pilha, Pilha *novo){
    for(int i=0;i<6;i++){
        if(pilha[i]==NULL){
            novo->prox = pilha[i];
            pilha[i] = novo;
            novo->altura = 1;
            return pilha;
        }
        else if(pilha[i]->altura<5){
            novo->prox = pilha[i];
            novo->altura = ++novo->prox->altura;
            pilha[i] = novo;
            return pilha;
        }
        else
            continue;
    }
    /*Se chegar aqui, pilha cheia, entao nada pode ser feito*/
    return pilha;
}

/*funcao para remover do inicio da pilha*/
Pilha **desempilhar(Pilha **pilha){
    for(int i=5;i>=0;i--){
        if(pilha[i]==NULL)
            continue;
        else{
            Pilha *antigo_topo = pilha[i];
            pilha[i] = pilha[i]->prox;
            free(antigo_topo);
            return pilha;
        }
    }
    /*pilha vazia, nada pode ser feito*/
    return pilha;
}

void print_pilha_solo(Pilha *pilha){
    if(pilha == NULL){
        return;
    }
    else if(pilha->prox == NULL){
        printf("%d,", pilha->num);
        return;
    }
    else{
        print_pilha_solo(pilha->prox);
        printf("%d,", pilha->num);
        return;
    }
}

void print_pilha(Pilha **pilha){
    for(int i=0;i<6;i++){
        printf("[S%d]", i+1);
        print_pilha_solo(pilha[i]);
        printf("\n");
    }
}


int main(){
   
    /*Iniciando a lista, fila e pilha*/
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista = iniciar_lista(lista);

    Fila *fila = (Fila*) malloc(sizeof(Fila));
    fila = iniciar_fila(fila);

    Pilha **pilha = (Pilha**) malloc(6*sizeof(Pilha*));
    for(int i=0;i<6;i++){
        pilha[i] = NULL;
    }
    
    char comando[5], num_str[3], lixo; /*comando sao os QIx, QRx, SRx, P e D, num_str é o numero do comando, ou seja, o x, e lixo foi usado para capturar a virgula*/
    int num, upl; /*num eh o x, em inteiro. upl é a Ultima Posicao da Lista*/
    scanf(" %s", comando); /*Identifica qual o comando*/
    while(comando[0] != 'D'){ /*Se comando = D, o programa acaba*/
        if(comando[0] == 'P'){ /*P deve printar o formato atual da fila e das pilhas*/
            printf("[Q]");
            print_fila(fila->inicio->prox);
            print_pilha(pilha);
        }
        else if(comando[0] == 'Q'){ /*Operação com Fila*/
            num_str[0] = comando[2]; num_str[1] = comando[3];
            num = atoi(num_str);
            if(comando[1] == 'I'){ /*Inserir na fila*/
                upl = lista->inicio->pos; /*Ultima Posicao da Lista antes de entrar no loop*/
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
            else if(comando[1] == 'R'){ /*Remover da Fila*/
                for(int i=1;i<=num;i++){
                    /*Tirar da fila*/
                    int num_pilha = fila->inicio->prox->num;
                    fila = desenfileirar(fila);
                    /*Colocar na pilha*/
                    Pilha *novo_pilha = (Pilha*) malloc(sizeof(Pilha));
                    novo_pilha->num = num_pilha;
                    pilha = empilhar(pilha, novo_pilha);
                }
            }
        }
        else if(comando[0] == 'S'){ /*Operação com a pilha*/
            num_str[0] = comando[2]; num_str[1] = comando[3];
            num = atoi(num_str);
            for(int i=1;i<=num;i++){
                pilha = desempilhar(pilha);
            }
            
        }
        scanf(" %s", comando); /*recebe novo comando*/
    }
    print_lista(lista->inicio->prox); /*ao final, printar a lista*/

    return 0;
}
