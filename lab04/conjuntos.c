#include<stdio.h>
#include<stdlib.h>


typedef struct No{
    int num;
    struct No *prox;
} No;

void imprimir_lista(No *lista) {
    if (lista != NULL && lista->prox!=NULL) {
        printf("%d,", lista->num);
        imprimir_lista(lista->prox);
    }
    else if (lista != NULL && lista->prox==NULL) {
        printf("%d", lista->num);
        imprimir_lista(lista->prox);
    }
}

void imprimir_conjunto(No *conj) {
    printf("{");
    imprimir_lista(conj);
    printf("}\n");
}

No *posicao_aux(No *aux, No *novo){
    if (aux->prox != NULL){
        if (aux->prox->num < novo->num)
            return posicao_aux(aux->prox, novo);
    }
    else
        return aux;
    return aux;
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
            return novo;
        }
        aux = posicao_aux(aux, novo); /*acha o local onde será inserida a variavel, recursivamente*/
        novo->prox = aux->prox;
        aux->prox = novo;
        return conj;
    }
}

void Pertence(int num, No *aux){
    if(aux==NULL){
        printf("NÃO\n");
        return;
    }
    else if(aux->num == num){
        printf("SIM\n");
        return;
    }
    else{
        Pertence(num, aux->prox);
    }
}

int pertence_bool(int num, No *aux){
    if(aux==NULL){
        return 0;
    }
    else if(aux->num == num){
        return 1;
    }
    else{
        return pertence_bool(num, aux->prox);
    }
    return 0;
}

No *Remove(int num, No *conj, No *aux){
    if(aux==conj && aux->num == num){ /*Numero esta na primeira posição*/
        return conj->prox;
    }
    else if(aux->prox->num == num){
        No *aux2 = aux->prox;
        free(aux->prox);
        aux->prox = aux2->prox;
        return conj;
    }
    else{
        return(Remove(num, conj, aux->prox));
    }
}

No *Uniao(No *conj1, No *conj2, No *aux){
    if(aux==NULL){
        return conj1;
    }
    else if(!(pertence_bool(aux->num, conj1))) {
        No *aux2 = NULL;
        No *novo = (No*) malloc(sizeof(No));
        *novo = *aux;
        conj1 = Insere(novo, conj1, aux2);
    }
    return(Uniao(conj1, conj2, aux->prox));
}

No *Interseccao(No *inter, No *conj1, No *conj2, No *aux){
    if(aux==NULL){
        return inter;
    }
    else{
        if(pertence_bool(aux->num, conj2)){
            No *copia = (No*) malloc(sizeof(No));
            *copia = *aux;
            No *aux2 = inter;
            inter = Insere(copia, inter, aux2);
        }
        return Interseccao(inter, conj1, conj2, aux->prox);
    }
    return inter;
}

No *Subtracao(No *conj1, No *conj2, No *aux){
    if(aux==NULL){
        return conj1;
    }
    else{
        if(pertence_bool(aux->num, conj2)){
            No *aux2 = conj1;
            conj1 = Remove(aux->num, conj1, aux2);
        }
        return Subtracao(conj1, conj2, aux->prox);
    }
}


int main(){
    char comando;
    int num, conj;
    No *conj1 = NULL;
    No *conj2 = NULL;
    No *aux = conj1;
    scanf(" %c", &comando);
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
        else if(comando=='p'){
            scanf(" %d%d", &num, &conj);
            if(conj==1)
                Pertence(num, conj1);
            else
                Pertence(num, conj2);
        }
        else if(comando=='r'){
            scanf(" %d%d", &num, &conj);
            if(conj==1){
                aux = conj1;
                conj1 = Remove(num, conj1, aux);
            }
            else{
                aux = conj2;
                conj2 = Remove(num, conj2, aux);
            }
        }
        else if(comando=='u'){
            aux = conj2;
            conj1 = Uniao(conj1, conj2, aux);
        }
        else if(comando=='x'){
            No *inter = NULL;
            aux = conj1;
            conj1 = Interseccao(inter, conj1, conj2, aux);
        }
        else if(comando=='b'){
            aux = conj1;
            conj1 = Subtracao(conj1, conj2, aux);
        }

        imprimir_conjunto(conj1);
        imprimir_conjunto(conj2);
        scanf(" %c", &comando);
    }

    return 0;
}
