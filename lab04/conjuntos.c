#include<stdio.h>

typedef struct Lista{
    int num;
    struct Lista *proximo;
} Lista;

void Insere(int num, int nconj){
    Lista *conj;
    Lista *paux=conj;
    if(nconj==1) conj = conj1;
    else conj = conj2;
    
    if(conj==NULL)
        conj->proximo = num;
    else if(num < paux->num){
        
    }


}

int main(){
    char comando;
    int num, conj;
    Lista *conj1 = NULL;
    Lista *conj2 = NULL;
    scanf("%c", &comando);
    if(comando=='i'){
        scanf(" %d%d", num, conj);
        Insere(num, conj);
    }
    else if(comando=='p'){ 
        scanf(" %d%d", num, conj);
        Pertence(num, conj);
    }
    
    return 1;
}
