#include<stdio.h>

typedef struct Lista{
    int num;
    struct Lista *proximo;
} Lista;

void Insere(int num, Lista **conj, Lista **aux){ 
    Lista *temp = NULL;
    temp.num = num;
    *aux = *conj;
    
    if(*conj==NULL){
        *conj = num;
        *temp->proximo = NULL;
        *aux = temp;
        return;
    }
    else if(temp.num < (*aux).num && (*aux)->proximo == NULL){
        *aux; //isso nao faz nada
    }
}

int main(){
    char comando;
    int num, conj;
    Lista *conj1 = NULL;
    Lista *conj2 = NULL;
    Lista *aux;
    scanf("%c", &comando);
    if(comando=='i'){
        scanf(" %d%d", num, conj);
        if(conj==1)
            Insere(num, &conj1, &aux);
        else
            Insere(num, &conj2, &aux);
    }
    /*else if(comando=='p'){ 
        scanf(" %d%d", num, conj);
        Pertence(num, conj);
    }*/
    
    return 0;
}
