#include<stdio.h>
#include<stdlib.h>
#define PAI(n) (n/2)

void trocar_vetores(float *v1, float *v2){
    int aux;
    for(int i=0; i<3;i++){
        aux = v1[i];
        v1[i] = v2[i];
        v2[i] = aux;
    }
}

void Subir(float **heap, int tam, int mod){
    if(heap[tam][mod] > heap[PAI(tam)][mod]){
        trocar_vetores(heap[tam], heap[PAI(tam)]);
        Subir(heap, PAI(tam), mod);
    }
    return;
}

void Inserir(float **heap, int *tam, float novo[], int mod){
    heap[*tam] = novo;
    (*tam)++;
    Subir(heap, *tam, mod);
}

int main(){
    int IT, MC, C, P;
    scanf(" %d%d", &IT, &MC);
    float **heap_a = (float**) malloc(MC*sizeof(float*));
    float **heap_c = (float**) malloc(MC*sizeof(float*));
    float **heap_v = (float**) malloc(MC*sizeof(float*));
    int tam_a=0, tam_c=0, tam_v=0;
    for(int i=0; i<IT; i++){
        scanf(" %d%d", &C, &P);
        for(int j=0; j<C; j++){
            float *novo = (float*) malloc(3*sizeof(float));
            scanf(" %f%f%f", &novo[0], &novo[1], &novo[2]);
            Inserir(heap_a, &tam_a, novo, 0);
        }
        for(int j=0; j<P; j++){
            break;
        }
    }
}
