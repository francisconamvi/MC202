/* Francisco Namias Vicente
 * 216028 */

#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    char nome[21];
    struct No *prox;
    struct No *ant;

}No;

/*FUNCAO QUE IRA PRINTAR CADA NOME DA RODA*/
void printl(No *lista, No *inicial, int sentido){
    printf("%s\n", lista->nome);
    if(sentido){
        if(lista->prox->nome != inicial->nome)
            printl(lista->prox, inicial, sentido);
    }
    else if(!sentido){
        if(lista->ant->nome != inicial->nome)
            printl(lista->ant, inicial, sentido);
    }
}

/*FUNCAO QUE IRA INSERIR AS PESSOAS INICIAIS*/
No *Insere_Inicial(No *novo, No *lista){
    if(lista==NULL){ /*Lista Vazia*/
        novo->prox = novo;
        novo->ant = novo;
        return novo;
    }
    else if(lista->prox == lista){ /*Lista com um elemento*/
        lista->prox = novo;
        novo->prox = lista;
        novo->ant = lista;
        lista->ant = novo;
        return lista;
    }
    else{ /*Lista com mais de um elemento*/
        novo->ant = lista->ant; 
        novo->prox = lista;
        lista->ant->prox = novo;
        lista->ant = novo;
        return lista;
    }

}

/*FUNCAO QUE INSERE NOVA PESSOA NA RODA*/
No *Insere(int N, No *novo, No *lista, int sentido){
    for(int i=1; i<N; i++){
        if(sentido)
            lista = lista->prox;
        else if(!sentido)
            lista = lista->ant;
    }
    novo->ant = lista->ant; 
    novo->prox = lista;
    lista->ant->prox = novo;
    lista->ant = novo;
    return novo;
}

/*FUNCAO QUE REMOVE PESSOA DA RODA*/
No *Remove(int N, No *lista, int sentido){ 
    for(int i=1; i<N; i++){
        if(sentido)
            lista = lista->prox;
        else if(!sentido)
            lista = lista->ant;
    }
    No *kamikaze = lista;
    No *retorno;
    if(sentido){
        retorno = lista->prox;
    }
    else{
        retorno = lista->ant;
    }
    lista->ant->prox = lista->prox;
    lista->prox->ant = lista->ant;
    free(kamikaze);
    return retorno;
}

/*FUNCAO QUE IMPRIME O NOME DA PESSOA NA POSICAO INDICADA*/
No *Imprime(int N, No *lista, int sentido){
    for(int i=1; i<N; i++){
        if(sentido)
            lista = lista->prox;
        else if(!sentido)
            lista = lista->ant;
    }
    printf("%s\n", lista->nome);
    return lista;

}

/*FUNCAO QUE FAZ A TROCA ENTRE DUAS PESSOAS*/
No *troca(No *inicio, char nome1[], char nome2[]){
    No *aux1 = inicio;
    while(!compara_str(aux1->nome, nome1)){
        aux1 = aux1->prox;
    }
    No *aux2 = inicio;
    while(!compara_str(aux2->nome, nome2)){
        aux2 = aux2->prox;
    }
    char nome_aux[21];
    copiar_str(aux1->nome, nome_aux);
    copiar_str(aux2->nome, aux1->nome);
    copiar_str(nome_aux, aux2->nome);
    
    return inicio;

}

/*FUNCOES PARA MANIPULACAO DE STRINGS*/
int compara_str(char str1[], char str2[]){
    for(int i=0; i<21; i++){
        if(str1[i]=='\0' && str2[i]=='\0')
            return 1;
        if(str1[i] != str2[i])
            return 0;
    }
    return 1;
}

void copiar_str(char str1[], char str2[]){
    for(int i=0;i<21;i++){
        str2[i] = str1[i];
    }
}

/*FUNCAO MAIN*/
int main(){
    No *lista = NULL;
    char nome_aux[21], nome1[21], nome2[21];
    while(1){
        No *novo = (No*) malloc(sizeof(No));
        scanf(" %s", nome_aux);
        for(int i=0; i<21; i++){
            novo->nome[i] = nome_aux[i];
        }
        if(nome_aux[0]<'A' || nome_aux[0]>'Z')
            break;
        lista = Insere_Inicial(novo, lista);     
    }

    char comando = nome_aux[0];
    char sinal, comando_str[21];
    int sentido = 1; /*sentido = 1 HORARIO | sentido = 0 ANTI-HORARIO*/
    printl(lista, lista, sentido);
    printf("\n");
    
    while(comando != 's'){
        if(comando == 't'){
            scanf(" %s%s", nome1, nome2);
            lista = troca(lista, nome1, nome2);
        }
        else if(comando == 'm'){
            sentido = !sentido;
            scanf(" %s", comando_str);
        }
        else if(comando < 58 && comando > 47){
            scanf(" %c", &sinal);
            if(sinal=='+'){
                No *novo = (No*) malloc(sizeof(No));
                scanf(" %s", nome_aux);
                for(int i=0; i<21; i++){
                    novo->nome[i] = nome_aux[i];
                }
                lista = Insere(comando-48, novo, lista, sentido);
            }
            else if(sinal=='-'){
                lista = Remove(comando-48, lista, sentido);
            }
            else if(sinal=='!'){
                lista = Imprime(comando-48, lista, sentido);
            }

        }
        
        printl(lista, lista, sentido);
        printf("\n");
        scanf(" %s", comando_str);
        comando = comando_str[0];
    }
    printl(lista, lista, sentido);
    printf("\n");

    return 0;
}
