/* Francisco Namias Vicente
 * 216028 */

#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    char nome[21];
    struct No *prox;
    struct No *ant;

}No;

void zerar_nome(char nome[]){
    int i;
    for(i=0; i<20; i++){
        nome[i] = 0;
    }
    nome[i] = 0;
}

void printl(No *lista, No *inicial){
    printf("%s\n", lista->nome);
    if(lista->prox->nome != inicial->nome)
        printl(lista->prox, inicial);
}

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

int compara_str(char str1[], char str2[]){
    for(int i=0; i<21; i++){
        if(str1[i]=='\0' && str2[i]=='\0')
            return 1;
        if(str1[i] != str2[i])
            return 0;
    }
    return 1;
}

void copiar_str(char str1[], char **str2){
    for(int i=0;i<21;i++){
        *str2[i] = str1[i];
    }
}

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
    copiar_str(aux1->nome, &(nome_aux));
    printf("%s\n", nome_aux);
    
    return inicio;

}

int main(){
    No *lista = NULL;
    char nome_aux[21], nome1[21], nome2[21];
    while(1){
        No *novo = (No*) malloc(sizeof(No));
        scanf(" %s", nome_aux);
        for(int i=0; i<21; i++){
            novo->nome[i] = nome_aux[i];
            if(nome_aux[i+1]=='\0')
                break;
        }
        if(nome_aux[0]<'A' || nome_aux[0]>'Z')
            break;
        lista = Insere_Inicial(novo, lista);     
    }
    printl(lista, lista);
    printf("\n");
    
    if(nome_aux[0] == 's'){
        return 0;
    }
    if(nome_aux[0] == 't'){
        scanf(" %s%s", nome1, nome2);
        lista = troca(lista, nome1, nome2);
    }
    printl(lista,lista);

    return 0;
}
