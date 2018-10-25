#include<stdio.h>
#include<stdlib.h>
#define PAI(n) ((n-1)/2)
#define FILHOESQ(n) (2*n + 1)
#define FILHODIR(n) (2*n + 2)

void print_heap(float **heap, int tam, int mod){
    int j=1, n=0;
    for(int i=0; i<=tam; i++){
        printf("%f ", heap[i][mod]);
        if(i == 2*n){
            printf("\n");
            n = n+j;
            j = 2*j;
        }
    }
    printf("\n\n");
}
void trocar_vetores(float *v1, float *v2){
    float aux;
    for(int i=0; i<3;i++){
        aux = v1[i];
        v1[i] = v2[i];
        v2[i] = aux;
    }
}

void copiar_vetor(float *v1, float *v2){
    for(int i=0; i<3;i++){
        v1[i] = v2[i];
    }
}

int compara_vetores(float *v1, float *v2){
    for(int i=0;i<3;i++)
        if(v1[i] != v2[i])
            return 0;
    return 1;
}

int folha(int i, int n){
    if(2*i+1 > n-1) return 1;
    return 0;
}

void Subir(float **heap, int tam, int mod){
    if(heap[tam][mod] > heap[PAI(tam)][mod]){
        trocar_vetores(heap[tam], heap[PAI(tam)]);
        if(tam>0)
            Subir(heap, PAI(tam), mod);
    }
    return;
}

void Inserir(float **heap, int *tam, float *novo, int mod){
    float *def = malloc(3*sizeof(float));
    copiar_vetor(def, novo);
    (*tam)++;
    heap[*tam] = def;
    if(*tam>0)
        Subir(heap, *tam, mod);
}

int Buscar(float **heap, int n,float *carro, int tam){
    if(compara_vetores(heap[n], carro)){
        return n;
    }
    if(folha(n, tam)) return -1;
    int a; 
    a = Buscar(heap, FILHOESQ(n), carro, tam);
    if(a != -1) return a;
    a = Buscar(heap, FILHODIR(n), carro, tam);
    if(a != -1) return a;
    return -1;
    
}

int main(){
    int IT, MC, C, P, comando, x, y;
    scanf(" %d%d", &IT, &MC);
    float **heap_a = (float**) malloc(MC*sizeof(float*));
    float **heap_c = (float**) malloc(MC*sizeof(float*));
    float **heap_v = (float**) malloc(MC*sizeof(float*));
    int tam_a=-1, tam_c=-1, tam_v=-1;
    for(int i=0; i<IT; i++){
        scanf(" %d%d", &C, &P);
        for(int j=0; j<C; j++){
            float *novo = malloc(3*sizeof(float));
            scanf(" %f%f%f", &novo[0], &novo[1], &novo[2]);
            Inserir(heap_a, &tam_a, novo, 0);
            //print_heap(heap_a, tam_a, 0);
            Inserir(heap_c, &tam_c, novo, 1);
            Inserir(heap_v, &tam_v, novo, 2);
        }
        //print_heap(heap_v, tam_v, 2);
        for(int j=0; j<P; j++){
            scanf(" %d", &comando);
            if(comando==0){
                x = Buscar(heap_c, 0, heap_a[0], tam_c);
                y = Buscar(heap_v, 0, heap_a[0], tam_v);
                printf("%d %d\n", x, y);
            }
        }
    }
    return 0;
}
