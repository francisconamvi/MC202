#include<stdio.h>
#include<stdlib.h>
#define PAI(n) ((n-1)/2)
#define FILHOESQ(n) (2*n + 1)
#define FILHODIR(n) (2*n + 2)
#define RAIZ 0

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

void print_vetor(float *v){
    for(int i=0;i<3;i++){
        printf("%.2f ", v[i]);
    }
    printf("\n");
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
    for(int i=0; i<3;i++)
        v1[i] = v2[i];
}

int compara_vetores(float *v1, float *v2){
    for(int i=0;i<3;i++)
        if(v1[i] != v2[i])
            return 0;
    return 1;
}

void zerar_vetor(float *v1){
    for(int i=0;i<3;i++){
        v1[i] = 0.0;
    }
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

void Arrumar(float **heap, int tam, int pos, int mod){
    if(folha(pos, tam))
        return;
    if(heap[FILHOESQ(pos)][mod] > heap[FILHODIR(pos)][mod]){
        trocar_vetores(heap[pos], heap[FILHOESQ(pos)]);
        Arrumar(heap, tam, FILHOESQ(pos), mod);
    }
    else{
        trocar_vetores(heap[pos], heap[FILHODIR(pos)]);
        Arrumar(heap, tam, FILHODIR(pos), mod);

    }
}

void Remover(float **heap, int *tam, int pos, int mod){
    //free(heap[pos]);
    zerar_vetor(heap[pos]); /*Pra mostrar que ta vazio*/
    Arrumar(heap, *tam, pos, mod);
}

int Buscar(float **heap, int tam, float *carro, int n){
    if(tam==-1) return -1;
    if(compara_vetores(heap[n], carro)){
        return n;
    }
    if(folha(n, tam)) return -1;
    int a;
    a = Buscar(heap, tam, carro, FILHOESQ(n));
    if(a != -1) return a;
    a = Buscar(heap, tam, carro, FILHODIR(n));
    if(a != -1) return a;
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
    float vetor_nulo[3];
    zerar_vetor(vetor_nulo);
    scanf(" %d%d", &IT, &MC);

    /*Criando os 3 heaps, um pra cada modalidade*/
    float **heap_a = (float**) malloc(MC*sizeof(float*)); /*Heap aceleracao*/
    float **heap_c = (float**) malloc(MC*sizeof(float*)); /*Heap controle*/
    float **heap_v = (float**) malloc(MC*sizeof(float*)); /*Heap velocidade*/
    int tam_a=-1, tam_c=-1, tam_v=-1; /*Todas os heaps comecam com tamanho -1, pois estao vazios*/
    for(int i=0; i<IT; i++){
        scanf(" %d%d", &C, &P);
        for(int j=0; j<C; j++){
            float *novo = malloc(3*sizeof(float)); /*novo carro que sera adicionado*/
            scanf(" %f%f%f", &novo[0], &novo[1], &novo[2]);
            /*Inserindo novo em cada um dos heaps e atualizando o tamanho do heap*/
            x = Buscar(heap_a, tam_a, vetor_nulo, RAIZ);
            y = Buscar(heap_c, tam_c, vetor_nulo, RAIZ);
            z = Buscar(heap_v, tam_v, vetor_nulo, RAIZ);
            if(x==-1) Inserir(heap_a, &tam_a, novo, 0);
            else{
                --x;
                Inserir(heap_a, &x, novo, 0);
            }
            if(y==-1) Inserir(heap_c, &tam_c, novo, 1);
            else{
                --y;
                Inserir(heap_c, &y, novo, 0);
            }
            if(z==-1) Inserir(heap_v, &tam_v, novo, 2);
            else{
                --z;
                Inserir(heap_v, &z, novo, 0);
            }
            free(novo);
        }
        /*
        print_heap(heap_a, tam_a, 0);
        print_heap(heap_c, tam_c, 1);
        print_heap(heap_v, tam_v, 2);
        printf("===========================================================================\n");
        */n
        for(int j=0; j<P; j++){
            scanf(" %d", &E);
            if(E==0){ /*foi escolhido carro com a melhor aceleracao*/
                print_vetor(heap_a[0]);
                /*Nao eh preciso buscar esse carro no heap_a pois ele esta na raiz*/
                x = Buscar(heap_c, tam_c, heap_a[0], RAIZ); /*Buscando no heap_c o elemento que esta na raiz do heap_a*/
                y = Buscar(heap_v, tam_v, heap_a[0], RAIZ); /*Buscando no heap_v o elemento que esta na raiz do heap_a*/
                Remover(heap_a, &tam_a, RAIZ, 0); /*Remover a raiz do heap_a*/
                Remover(heap_c, &tam_c, x, 1); /*Remover o mesmo elemento, mas do heap_c*/
                Remover(heap_v, &tam_v, y, 2); /*Remover o mesmo elemento, mas do heap_v*/
            }


            else if(E==1){ /*foi escolhido o carro com o melhor controle*/
                print_vetor(heap_c[0]);
                /*Nao eh preciso buscar esse carro no heap_c pois ele esta na raiz*/
                x = Buscar(heap_a, tam_a, heap_c[0], RAIZ); /*Buscando no heap_a o elemento que esta na raiz do heap_c*/
                y = Buscar(heap_v, tam_v, heap_c[0], RAIZ); /*Buscando no heap_v o elemento que esta na raiz do heap_c*/
                Remover(heap_c, &tam_c, RAIZ, 1); /*Remover a raiz do heap_c*/
                Remover(heap_a, &tam_a, x, 0); /*Remover o mesmo elemento, mas do heap_a*/
                Remover(heap_v, &tam_v, y, 2); /*Remover o mesmo elemento, mas do heap_v*/
            }
            else if(E==2){ /*foi escolhido o carro com a melhor velocidade*/
                print_vetor(heap_v[0]);
                /*Nao eh preciso buscar esse carro no heap_v pois ele esta na raiz*/
                x = Buscar(heap_a, tam_a, heap_v[0], RAIZ); /*Buscando no heap_a o elemento que esta na raiz do heap_v*/
                y = Buscar(heap_c, tam_c, heap_v[0], RAIZ); /*Buscando no heap_c o elemento que esta na raiz do heap_v*/
                Remover(heap_v, &tam_v, RAIZ, 2); /*Remover a raiz do heap_v*/
                Remover(heap_a, &tam_a, x, 0); /*Remover o mesmo elemento, mas do heap_c*/
                Remover(heap_c, &tam_c, y, 1); /*Remover o mesmo elemento, mas do heap_v*/
            }
            /*
            print_heap(heap_a, tam_a, 0);
            print_heap(heap_c, tam_c, 1);
            print_heap(heap_v, tam_v, 2);
            printf("===========================================================================\n");
            */
        }
    }
    return 0;
}
//print_heap(heap_a, tam_a, 0);
//print_heap(heap_c, tam_c, 1);
//print_heap(heap_v, tam_v, 2);
//printf("%d %d\n", x, y);
