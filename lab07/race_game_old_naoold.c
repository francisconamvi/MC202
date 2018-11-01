/* Francisco Namias Vicente
   RA 216028 */

#include<stdio.h>
#include<stdlib.h>
//#include "race_game.h"

#define PAI(n) ((n-1)/2)
#define FILHOESQ(n) (2*n + 1)
#define FILHODIR(n) (2*n + 2)
#define RAIZ 0



/*Funcao que printa o carro que será retirado*/
void print_carro(float **v){
    int i;
    for(i=0;i<2;i++)
        printf("%.2f ", v[0][i]);
    printf("%.2f\n", v[0][i]);
}

/*Copia os valores de um carro*/
void copiar_carro(float **v1, float **v2){
    for(int i=0; i<3;i++)
        v1[0][i] = v2[0][i];
}

/*funcao para trocar os valores entre carros*/
void trocar_carros(float **v1, float **v2){
    float aux;
    for(int i=0; i<3;i++){
        aux = v1[0][i];
        v1[0][i] = v2[0][i];
        v2[0][i] = aux;
    }
}

/*Funcao que retorna se a posicao no heap é uma folha*/
int folha(int i, int n){
    if(2*i+1 > n) return 1;
    return 0;
}

/*funcao que retorna se a posicao no heap tem filho direito*/
int tem_filho_dir(int i, int n){
    if(2*i+2 <= n) return 1;
    return 0;
}

/*Funcao que ira comparar o carro com o seu "pai" e subir no heap progressivamente*/
int Subir_Heap(float ***heap, int pos, int mod){
    if(pos == 0)
        return 0; /*Ja ta na raiz, nada a ser feito*/
    if(heap[pos][0][mod] > heap[PAI(pos)][0][mod]){ /*se filho for maior que o pai*/
        trocar_carros(heap[pos], heap[PAI(pos)]); /*trocar o filho com o pai*/
        return Subir_Heap(heap, PAI(pos), mod); /*subir o pai no heap, pra verificar se o pai eh maior que o pai do pai*/
    }
    return pos;
}

/*Funcao que ira comparar o pai com seus filhos e descer no heap se for necessario*/
void Descer_Heap(float **heap, int pos, int tam, int mod){
    if(folha(pos, tam)) /*Se estiver na folha, nao ha o que fazer*/
        return;
    if(!tem_filho_dir(pos, tam)){ /*se nao tem filho direito*/
        if(heap[pos][mod] < heap[FILHOESQ(pos)][mod]){ /*compara soh com o filho esquerdo, e se pai for menor que o filho*/
            trocar_carros(heap[pos],heap[FILHOESQ(pos)]); /*troca pai com o filho esquerdo*/
        }
        return; /*nao eh necessario chamar a funcao recursivamente pois se o pai nao tem filho direito, nao eh possivel descer mais no heap*/
    }
    if(heap[FILHOESQ(pos)][mod] > heap[FILHODIR(pos)][mod]){ /*se filho esquerdo for maior que filho direito*/
        if(heap[pos][mod] < heap[FILHOESQ(pos)][mod]){ /*se pai for menor que o filho esquerdo*/
            trocar_carros(heap[pos], heap[FILHOESQ(pos)]); /*troca pai com o filho esquerdo*/
            Descer_Heap(heap, FILHOESQ(pos), tam, mod); /*Chama a funcao novamente para o filho que foi trocado*/
        }
    }
    else{ /*Se filho direito for maior que o filho esquerdo*/
        if(heap[pos][mod] < heap[FILHODIR(pos)][mod]){ /*Se o pai for menor que o filho direito*/
            trocar_carros(heap[pos], heap[FILHODIR(pos)]); /*troca o pai com o filho direito*/
            Descer_Heap(heap, FILHODIR(pos), tam, mod); /*Chama a funcao novamente para o filho que foi trocado*/
        }
    }
    return;
}

/*Funcao que ira inserir carro no heap*/
void Inserir(float ***heap1, float ***heap2, float ***heap3, int *tam1, int *tam2, int *tam3, float **novo){
    float **def1 = malloc(2*sizeof(float*)); /*aloca carro definitivo que sera colocado no heap*/
    def1[0] = malloc(3*sizeof(float));
    def1[1] = malloc(3*sizeof(float));
    float **def2 = malloc(2*sizeof(float*)); /*aloca carro definitivo que sera colocado no heap*/
    def2[0] = malloc(3*sizeof(float));
    def2[1] = malloc(3*sizeof(float));
    float **def1 = malloc(2*sizeof(float*)); /*aloca carro definitivo que sera colocado no heap*/
    def3[0] = malloc(3*sizeof(float));
    def3[1] = malloc(3*sizeof(float));
    copiar_carro(def1, novo); /*copia novo para o definitivo*/
    copiar_carro(def2, novo); /*copia novo para o definitivo*/
    copiar_carro(def3, novo); /*copia novo para o definitivo*/
    (*tam1)++; /*Aumenta tamanho do heap*/
    (*tam2)++; /*Aumenta tamanho do heap*/
    (*tam3)++; /*Aumenta tamanho do heap*/
    heap1[*tam1] = def1; /*Insere no final*/
    heap2[*tam2] = def2; /*Insere no final*/
    heap3[*tam3] = def3; /*Insere no final*/
    int x = Subir_Heap(heap1, *tam1, 0); /*Manda o definitivo subir no heap*/
    int y = Subir_Heap(heap2, *tam2, 1); /*Manda o definitivo subir no heap*/
    int z = Subir_Heap(heap2, *tam3, 3); /*Manda o definitivo subir no heap*/
}

/*Funcao para remover um carro de uma posicao no heap*/
void Remover(float **heap, int *tam, int pos, int mod){
    trocar_carros(heap[pos], heap[*tam]); /*troca o carro que deve ser removido com o carro no final do heap*/
    free(heap[*tam]); /*remove o carro, que estava no final do heap*/
    (*tam)--; /*diminui o tamanho do final do heap*/
    if(pos<=*tam){
        Descer_Heap(heap, pos, *tam, mod); /*Manda o carro descer no heap, caso der pra descer*/
        Subir_Heap(heap, pos, mod); /*também temos que verificar se é possivel fazer o carro subir no heap*/
    }
}

/*Buscar um carro no heap*/
int Buscar(float **heap, int tam, float *carro, int pos, int mod){
    if(carros_iguais(heap[pos], carro)) /*Se carros forem iguais*/
        return pos; /*retorna a posicao*/
    if(folha(pos,tam)) /*Se for uma folha*/
        return -1; /*retorna -1, pois nao foi achado naquele ramo*/
    if(carro[mod] < heap[pos][mod]){ /*Se o carro procurado for menor do que o carro analisado: (importante para poupar tempo e nao ir ate o final de um ramo)*/
        int a;
        a = Buscar(heap, tam, carro, FILHOESQ(pos), mod); /*Bosca no ramo esquerdo*/
        if(a!=-1) return a; /*Se achou, retorna a posicao achada*/
        if(tem_filho_dir(pos, tam)) /*Se nao achou, busca no ramo direito*/
            return Buscar(heap, tam, carro, FILHODIR(pos), mod); /*retorna a posicao achada no ramo direito*/
    }
    return -1; /*Se nao achou, retorna -1*/
}

/*Funcao para dar free nos elementos faltantes do heap*/
void Liberar_Heap(float **heap, int max){
    for(int i=0; i<=max; i++){
        free(heap[i]);
    }
    free(heap);
    return;
}

int main(){
    int IT, MC, C, P, E, x, y, z;
    /*  IT = Numero de Iteracoes
     *  MC = Maximo de Carros
     *  C = Numero de Carros Inseridos na Iteracao
     *  P = Carros Escolhidos a cada Iteracao
     *  E = Modalidade de Carro Escolhida
     *  x,y,z = posicao do Carro que foi escolhido nos heaps
     * */

     scanf(" %d%d", &IT, &MC);

     /*Criando os 3 heaps, um pra cada modalidade*/
     float ***heap_a = (float***) malloc(MC*sizeof(float**)); /*Heap aceleracao*/
     float ***heap_c = (float***) malloc(MC*sizeof(float**)); /*Heap controle*/
     float ***heap_v = (float***) malloc(MC*sizeof(float**)); /*Heap velocidade*/
     int tam_a=-1, tam_c=-1, tam_v=-1; /*Todas os heaps comecam com tamanho -1, pois estao vazios*/
     for(int i=0; i<IT; i++){ /*loop limitado pelo numero de iteracoes*/
         scanf(" %d%d", &C, &P);
         for(int j=0;j<C;j++){ /*loop limitado pelo numero de carros que serao inseridos*/
             float **novo = malloc(2*sizeof(float*)); /*novo carro que sera adicionado*/
             novo[0] = malloc(3*sizeof(float)); /*atributos do carro*/
             novo[1] = malloc(3*sizeof(float)); /*posicao nos heaps*/
             scanf(" %f%f%f", &novo[0][0], &novo[0][1], &novo[0][2]);
             Inserir(heap_a, heap_c, heap_v, &tam_a, &tam_c, &tam_v, novo); /*Insere o novo carro no heap_a*/
             free(novo); /*Free no novo carro pois ele nao sera mais usado*/
         }
         for(int j=0; j<P; j++){ /*loop limitado pelo numero de carros que serão retirados*/
             scanf(" %d", &E);
             if(E==0){ /*Será retirado o carro com a melhor aceleração*/
                 print_carro(heap_a[0]);
                 x = RAIZ; /*Nao eh preciso buscar esse carro no heap_a pois ele esta na raiz*/
                 y = Buscar(heap_c, tam_c, heap_a[0], RAIZ, 1); /*Buscando no heap_c o elemento que esta na raiz do heap_a*/
                 z = Buscar(heap_v, tam_v, heap_a[0], RAIZ, 2); /*Buscando no heap_v o elemento que esta na raiz do heap_a*/
                 Remover(heap_a, &tam_a, x, 0); /*Remover a raiz do heap_a*/
                 Remover(heap_c, &tam_c, y, 1); /*Remover o mesmo elemento, mas do heap_c*/
                 Remover(heap_v, &tam_v, z, 2); /*Remover o mesmo elemento, mas do heap_v*/
             }
             else if(E==1){ /*Será retirado o carro com o melhor controle*/
                 print_carro(heap_c[0]);
                 x = Buscar(heap_a, tam_a, heap_c[0], RAIZ, 0); /*Buscando no heap_c o elemento que esta na raiz do heap_a*/
                 y = RAIZ; /*Nao eh preciso buscar esse carro no heap_a pois ele esta na raiz*/
                 z = Buscar(heap_v, tam_v, heap_c[0], RAIZ, 2); /*Buscando no heap_v o elemento que esta na raiz do heap_a*/
                 Remover(heap_a, &tam_a, x, 0); /*Remover a raiz do heap_a*/
                 Remover(heap_c, &tam_c, y, 1); /*Remover o mesmo elemento, mas do heap_c*/
                 Remover(heap_v, &tam_v, z, 2); /*Remover o mesmo elemento, mas do heap_v*/
             }
             else if(E==2){ /*Será retirado o carro com a melhor velocidade*/
                 print_carro(heap_v[0]);
                 x = Buscar(heap_a, tam_a, heap_v[0], RAIZ, 0); /*Buscando no heap_c o elemento que esta na raiz do heap_a*/
                 y = Buscar(heap_c, tam_c, heap_v[0], RAIZ, 1); /*Buscando no heap_v o elemento que esta na raiz do heap_a*/
                 z = RAIZ; /*Nao eh preciso buscar esse carro no heap_a pois ele esta na raiz*/
                 Remover(heap_a, &tam_a, x, 0); /*Remover a raiz do heap_a*/
                 Remover(heap_c, &tam_c, y, 1); /*Remover o mesmo elemento, mas do heap_c*/
                 Remover(heap_v, &tam_v, z, 2); /*Remover o mesmo elemento, mas do heap_v*/
             }
         }
     }
     Liberar_Heap(heap_a, tam_a);
     Liberar_Heap(heap_c, tam_c);
     Liberar_Heap(heap_v, tam_v);
     return 0;
 }
