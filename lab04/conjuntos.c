#include<stdio.h>
#include<stdlib.h>


typedef struct No{
    int num;
    struct No *prox;
} No;

void imprimir_lista(No *lista) {
    if (lista != NULL) {
        printf("%d ", lista->num);
        imprimir_lista(lista->prox);
    }
}

No *Insere(No *novo, No *conj, No *aux){
    if(conj==NULL){ /*se lista for vazia*/
        conj = novo;
        novo->prox = NULL;
        return conj;
    }
    else{
        aux = conj;
        if(aux->num > novo->num){ /*se elemento ja estiver na cabeça da lista*/
            novo->prox = aux;
            conj = novo;
            return conj;
        }
        while(aux->prox!=NULL)
            if (aux->prox->num < novo->num)
                aux = aux->prox;
            else break;
        if(aux->prox != NULL){
            novo->prox = aux->prox;
            aux->prox = novo;
        }
        else{
            aux->prox = novo;
            novo->prox = NULL;
        }
        return conj;
    }
}

int main(){
    char comando;
    int num, conj;
    No *conj1 = NULL;
    No *conj2 = NULL;
    No *aux = conj1;
    scanf("%c", &comando);
    while(comando != 's'){
        if(comando=='i'){
            scanf(" %d%d", &num, &conj);
            No *novo = (No*) malloc(sizeof(No));
            novo->num = num;
            if(conj==1)
                conj1 = Insere(novo, conj1, aux);
            else
                conj2 = Insere(novo, conj2, aux);
        }
        scanf("%c", &comando);
    }
    imprimir_lista(conj1);
    printf("\n");
    imprimir_lista(conj2);
    printf("\n");
    /*else if(comando=='p'){ 
        scanf(" %d%d", num, conj);
        Pertence(num, conj);
    }*/
    
    return 0;
}
