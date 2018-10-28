#include<stdio.h>
#include<stdlib.h>
#define PAI(n) ((n-1)/2)
#define FILHOESQ(n) (2*n + 1)
#define FILHODIR(n) (2*n + 2)
#define RAIZ 0

void print_heap(float **heap, int tam, int mod){
    int j=1, n=0;
    for(int i=0; i<=tam; i++){
        printf("%.2f ", heap[i][mod]);
        if(i == 2*n){
            printf("\n");
            n = n+j;
            j = 2*j;
        }
    }
    printf("\n\n");
}

void print_vetor(float *v){
    for(int i=0;i<3;i++){
        printf("%.2f ", v[i]);
    }
    printf("\n");
}

void copiar_vetor(float *v1, float *v2){
    for(int i=0; i<3;i++)
        v1[i] = v2[i];
}

int iguais(float *v1, float *v2){
    for(int i=0;i<3;i++)
        if(v1[i] != v2[i])
            return 0;
    return 1;
}

void trocar(float *v1, float *v2){
    float aux;
    for(int i=0; i<3;i++){
        aux = v1[i];
        v1[i] = v2[i];
        v2[i] = aux;
    }
}

int folha(int i, int n){
    if(2*i+1 > n) return 1;
    return 0;
}

int tem_filho_dir(int i, int n){
    if(2*i+2 <= n) return 1;
    return 0;
}

void Subir_Heap(float **heap, int pos, int mod){
    if(pos == 0)
        return; /*Ja ta na raiz, nada a ser feito*/
    if(heap[pos][mod] > heap[PAI(pos)][mod]){
        trocar(heap[pos], heap[PAI(pos)]);
        Subir_Heap(heap, PAI(pos), mod);
    }
    return;
}

void Descer_Heap(float **heap, int pos, int tam, int mod){
    if(folha(pos, tam))
        return;
    if(!tem_filho_dir(pos, tam)){
        if(heap[pos][mod] < heap[FILHOESQ(pos)][mod]){
            trocar(heap[pos],heap[FILHOESQ(pos)]);
        }
        return;
    }
    if(heap[FILHOESQ(pos)][mod] > heap[FILHODIR(pos)][mod]){
        if(heap[pos][mod] < heap[FILHOESQ(pos)][mod]){
            trocar(heap[pos], heap[FILHOESQ(pos)]);
            Descer_Heap(heap, FILHOESQ(pos), tam, mod);
        }
    }
    else{
        if(heap[pos][mod] < heap[FILHODIR(pos)][mod]){
            trocar(heap[pos], heap[FILHODIR(pos)]);
            Descer_Heap(heap, FILHODIR(pos), tam, mod);
        }
    }
    return;
}

void Inserir(float **heap, float *novo, int *tam, int mod){
    float *def = malloc(3*sizeof(float));
    copiar_vetor(def, novo);
    (*tam)++; /*Aumenta tamanho do heap*/
    heap[*tam] = def; /*Insere no final*/
    Subir_Heap(heap, *tam, mod);
}

void Remover(float **heap, int *tam, int pos, int mod){
    trocar(heap[pos], heap[*tam]);
    free(heap[*tam]);
    (*tam)--;
    if(pos<=*tam){
        Descer_Heap(heap, pos, *tam, mod);
        Subir_Heap(heap, pos, mod);
    }
}

int Buscar(float **heap, int tam, float *carro, int pos, int mod){
    if(iguais(heap[pos], carro))
        return pos;
    if(folha(pos,tam))
        return -1;
    if(carro[mod] < heap[pos][mod]){
        int a;
        a = Buscar(heap, tam, carro, FILHOESQ(pos), mod);
        if(a!=-1) return a;
        if(tem_filho_dir(pos, tam))
            return Buscar(heap, tam, carro, FILHODIR(pos), mod);
    }
    return -1;
}

int main(){
    int IT, MC, C, P, E, x, y, z;
    /*  IT = Numero de Iteracoes
     *  MC = Maximo de Carros
     *  C = Numero de Carros Inseridos na Iteracao
     *  P = Carros Escolhidos a cada Iteracao
     *  E = Modalidade de Carro Escolhida
     *  x,y,z = posicao do Carro que foi escolhido nos heaps de outra modalidade
     * */

     scanf(" %d%d", &IT, &MC);

     /*Criando os 3 heaps, um pra cada modalidade*/
     float **heap_a = (float**) malloc(MC*sizeof(float*)); /*Heap aceleracao*/
     float **heap_c = (float**) malloc(MC*sizeof(float*)); /*Heap controle*/
     float **heap_v = (float**) malloc(MC*sizeof(float*)); /*Heap velocidade*/
     int tam_a=-1, tam_c=-1, tam_v=-1; /*Todas os heaps comecam com tamanho -1, pois estao vazios*/
     for(int i=0; i<IT; i++){
         printf("=====================ADICIONANDO CARROS========================\n");
         scanf(" %d%d", &C, &P);
         for(int j=0;j<C;j++){
             float *novo = malloc(3*sizeof(float)); /*novo carro que sera adicionado*/
             scanf(" %f%f%f", &novo[0], &novo[1], &novo[2]);
             Inserir(heap_a, novo, &tam_a, 0);
             Inserir(heap_c, novo, &tam_c, 1);
             Inserir(heap_v, novo, &tam_v, 2);
             free(novo);
         }

         printf("Heap_A: \n");
         print_heap(heap_a, tam_a, 0);
         printf("Heap_C: \n");
         print_heap(heap_c, tam_c, 1);
         printf("Heap_V: \n");
         print_heap(heap_v, tam_v, 2);
         printf("=====================RETIRANDO CARROS========================\n");

         for(int j=0; j<P; j++){
             scanf(" %d", &E);
             printf("%d Carro Retirado: \n", E);
             if(E==0){
                 print_vetor(heap_a[0]);
                 /*Nao eh preciso buscar esse carro no heap_a pois ele esta na raiz*/
                 x = RAIZ;
                 y = Buscar(heap_c, tam_c, heap_a[0], RAIZ, 1); /*Buscando no heap_c o elemento que esta na raiz do heap_a*/
                 z = Buscar(heap_v, tam_v, heap_a[0], RAIZ, 2); /*Buscando no heap_v o elemento que esta na raiz do heap_a*/
                 Remover(heap_a, &tam_a, x, 0); /*Remover a raiz do heap_a*/
                 Remover(heap_c, &tam_c, y, 1); /*Remover o mesmo elemento, mas do heap_c*/
                 Remover(heap_v, &tam_v, z, 2); /*Remover o mesmo elemento, mas do heap_v*/
             }
             else if(E==1){
                 print_vetor(heap_c[0]);
                 /*Nao eh preciso buscar esse carro no heap_a pois ele esta na raiz*/
                 x = Buscar(heap_a, tam_a, heap_c[0], RAIZ, 0); /*Buscando no heap_c o elemento que esta na raiz do heap_a*/
                 y = RAIZ;
                 z = Buscar(heap_v, tam_v, heap_c[0], RAIZ, 2); /*Buscando no heap_v o elemento que esta na raiz do heap_a*/
                 Remover(heap_a, &tam_a, x, 0); /*Remover a raiz do heap_a*/
                 Remover(heap_c, &tam_c, y, 1); /*Remover o mesmo elemento, mas do heap_c*/
                 Remover(heap_v, &tam_v, z, 2); /*Remover o mesmo elemento, mas do heap_v*/
             }
             else if(E==2){
                 print_vetor(heap_v[0]);
                 /*Nao eh preciso buscar esse carro no heap_a pois ele esta na raiz*/
                 x = Buscar(heap_a, tam_a, heap_v[0], RAIZ, 0); /*Buscando no heap_c o elemento que esta na raiz do heap_a*/
                 y = Buscar(heap_c, tam_c, heap_v[0], RAIZ, 1); /*Buscando no heap_v o elemento que esta na raiz do heap_a*/
                 z = RAIZ;
                 Remover(heap_a, &tam_a, x, 0); /*Remover a raiz do heap_a*/
                 Remover(heap_c, &tam_c, y, 1); /*Remover o mesmo elemento, mas do heap_c*/
                 Remover(heap_v, &tam_v, z, 2); /*Remover o mesmo elemento, mas do heap_v*/
             }
             printf("Heap_A: \n");
             print_heap(heap_a, tam_a, 0);
             printf("Heap_C: \n");
             print_heap(heap_c, tam_c, 1);
             printf("Heap_V: \n");
             print_heap(heap_v, tam_v, 2);
         }
     }
     return 0;
 }
