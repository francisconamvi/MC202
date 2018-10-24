#include<stdio.h>
#include<stdlib.h>
#define PAI(n) (n/2)

typedef struct Carro{
    float atr[3];
}Carro;

void Subir(Carro heap[], int tam){
    if(heap[tam].v > heap[PAI(tam)]){
        Carro aux = heap[tam];
        heap[tam] = heap[PAI(tam)];
        heap[PAI(tam)] = aux;
        Subir(heap, PAI(tam));
    }
}

void Inserir(Carro heap[], int *tam, Carro novo){
    heap[*tam] = novo;
    (*tam)++;
    Subir(heap, *tam);
}

int main(){
    int IT, MC, C, P;
    scanf(" %d%d", &IT, &MC);
    Carro *heap_a = (Carro*) malloc(MC*sizeof(Carro));
    Carro *heap_c = (Carro*) malloc(MC*sizeof(Carro));
    Carro *heap_v = (Carro*) malloc(MC*sizeof(Carro));
    int tam_a=0, tam_c=0, tam_v=0;
    for(int i=0; i<IT; i++){
        scanf(" %d%d", &C, &P);
        for(int j=0; j<C; j++){
            Carro novo;
            scanf(" %f%f%f", &novo.a, &novo.c, &novo.v);
            Inserir(heap_a, &tam_a, novo);
        }
        for(int j=0; j<P; j++){
            break;
        }
    }
}
