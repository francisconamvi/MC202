/* Francisco Namias Vicente
   RA 216028 */

#include<stdio.h>
#include<stdlib.h>
#include "race_game.h"

/*Funcao que ira printar os atributos do carro*/
void print_carro(float *v){
    int i;
    for(i=0;i<2;i++)
        printf("%.2f ", v[i]);
    printf("%.2f\n", v[i]);
}

/*funcao que retorna 1 se no for folha e 0 se nao for*/
int folha(int i, int n){
    if(2*i+1 > n) return 1;
    return 0;
}

/*funcao que retorna 1 se no tiver filho direito*/
int tem_filho_dir(int i, int n){
    if(2*i+2 <= n) return 1;
    return 0;
}

/*funcao para iniciar o heap*/
Heap *criar_heap(int MC, int mod){
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    heap->v = (Carro**) malloc(MC*sizeof(Carro*));
    heap->n = -1;
    heap->MC = MC;
    heap->mod = mod;
    return heap;
}

/*Funcao que ira comparar o carro com o seu "pai" e subir no heap progressivamente*/
void Subir_Heap(Heap *heap, int pos){
    if(pos == 0)
        return; /*Ja ta na raiz, nada a ser feito*/
    if(heap->v[pos]->atri[heap->mod] > heap->v[PAI(pos)]->atri[heap->mod]){ /*se filho for maior que o pai*/
        /*Troca os carros que eles estao apontando*/
        Carro *carro_aux = heap->v[pos];
        heap->v[pos] = heap->v[PAI(pos)];
        heap->v[PAI(pos)] = carro_aux;
        /*Troca as posicoes*/
        int aux = heap->v[PAI(pos)]->pos[heap->mod];
        heap->v[PAI(pos)]->pos[heap->mod] = heap->v[pos]->pos[heap->mod];
        heap->v[pos]->pos[heap->mod] = aux;

        Subir_Heap(heap, PAI(pos)); /*subir o pai no heap, pra verificar se o pai eh maior que o pai do pai*/
    }
    return;
}

/*Funcao que ira comparar o pai com seus filhos e descer no heap se for necessario*/
void Descer_Heap(Heap *heap, int pos){
    if(folha(pos, heap->n)) /*Se estiver na folha, nao ha o que fazer*/
        return;
    if(!tem_filho_dir(pos, heap->n)){ /*se nao tem filho direito*/
        if(heap->v[pos]->atri[heap->mod] < heap->v[FILHOESQ(pos)]->atri[heap->mod]){ /*compara soh com o filho esquerdo, e se pai for menor que o filho*/
            /*troca pai com o filho esquerdo*/
            Carro *carro_aux = heap->v[pos];
            heap->v[pos] = heap->v[FILHOESQ(pos)];
            heap->v[FILHOESQ(pos)] = carro_aux;
            /*Troca as posicoes*/
            int aux = heap->v[FILHOESQ(pos)]->pos[heap->mod];
            heap->v[FILHOESQ(pos)]->pos[heap->mod] = heap->v[pos]->pos[heap->mod];
            heap->v[pos]->pos[heap->mod] = aux;
        }
        return; /*nao eh necessario chamar a funcao recursivamente pois se o pai nao tem filho direito, nao eh possivel descer mais no heap*/
    }
    if(heap->v[FILHOESQ(pos)]->atri[heap->mod] > heap->v[FILHODIR(pos)]->atri[heap->mod]){ /*se filho esquerdo for maior que filho direito*/
        if(heap->v[pos]->atri[heap->mod] < heap->v[FILHOESQ(pos)]->atri[heap->mod]){ /*se pai for menor que o filho esquerdo*/
            /*troca pai com o filho esquerdo*/
            Carro *carro_aux = heap->v[pos];
            heap->v[pos] = heap->v[FILHOESQ(pos)];
            heap->v[FILHOESQ(pos)] = carro_aux;
            /*Troca as posicoes*/
            int aux = heap->v[FILHOESQ(pos)]->pos[heap->mod];
            heap->v[FILHOESQ(pos)]->pos[heap->mod] = heap->v[pos]->pos[heap->mod];
            heap->v[pos]->pos[heap->mod] = aux;
            Descer_Heap(heap, FILHOESQ(pos)); /*Chama a funcao novamente para o filho que foi trocado*/
        }
    }
    else{ /*Se filho direito for maior que o filho esquerdo*/
        if(heap->v[pos]->atri[heap->mod] < heap->v[FILHODIR(pos)]->atri[heap->mod]){ /*Se o pai for menor que o filho direito*/
            /*troca pai com o filho direito*/
            Carro *carro_aux = heap->v[pos];
            heap->v[pos] = heap->v[FILHODIR(pos)];
            heap->v[FILHODIR(pos)] = carro_aux;
            /*Troca as posicoes*/
            int aux = heap->v[FILHODIR(pos)]->pos[heap->mod];
            heap->v[FILHODIR(pos)]->pos[heap->mod] = heap->v[pos]->pos[heap->mod];
            heap->v[pos]->pos[heap->mod] = aux;
            Descer_Heap(heap, FILHODIR(pos)); /*Chama a funcao novamente para o filho que foi trocado*/
        }
    }
    return;
}

/*Funcao que ira inserir carro no heap*/
void Inserir(Heap *heap, Carro *novo){
    heap->n++; /*Aumenta tamanho do heap*/
    heap->v[heap->n] = novo; /*Insere no final*/
    heap->v[heap->n]->pos[heap->mod] = heap->n; /*Informa a posicao*/
    Subir_Heap(heap, heap->n); /*Manda o definitivo fubir no heap*/
}

/*Funcao para remover um carro de uma posicao no heap*/
void Remover(Heap *heap, int pos){
    /*Trocar carro na posicao com o carro no final do heap*/
    Carro *carro_aux = heap->v[pos];
    heap->v[pos] = heap->v[heap->n];
    heap->v[heap->n] = carro_aux;
    /*Troca as posicoes*/
    int aux = heap->v[heap->n]->pos[heap->mod];
    heap->v[heap->n]->pos[heap->mod] = heap->v[pos]->pos[heap->mod];
    heap->v[pos]->pos[heap->mod] = aux;

    (heap->n)--; /*final do heap diminui 1*/
    Descer_Heap(heap, pos); /*manda descer no heap, se possivel*/
    if(pos!=0){
        if(heap->v[pos]->atri[heap->mod] > heap->v[PAI(pos)]->atri[heap->mod]){
            Subir_Heap(heap, pos); /*Se nao der pra descer, sobe*/
        }
    }
}

/*Funcao para dar free nos elementos faltantes do heap*/
void Liberar_Elementos(Heap *heap){
    for(int i=0; i<=heap->n; i++){
        free(heap->v[i]);
    }
    return;
}

/*Funcao para liberar o heap em si*/
void Liberar_Heap(Heap *heap){
    free(heap->v);
    free(heap);
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

    /*Criando 3 heaps, um pra cada modalidade*/
    Heap *heap_a = criar_heap(MC,0);
    Heap *heap_c = criar_heap(MC,1);
    Heap *heap_v = criar_heap(MC,2);

    for(int i=0; i<IT; i++){ /*loop limitado pelo numero de iteracoes*/
        scanf(" %d%d", &C, &P);
        for(int j=0;j<C;j++){ /*loop limitado pelo numero de carros que serao inseridos*/
            Carro *novo = malloc(sizeof(Carro)); /*novo carro que sera adicionado*/
            scanf(" %f%f%f", &(novo->atri[0]), &(novo->atri[1]), &(novo->atri[2]));
            Inserir(heap_a, novo); /*Insere o novo carro no heap_a*/
            Inserir(heap_c, novo); /*Insere o novo carro no heap_c*/
            Inserir(heap_v, novo); /*Insere o novo carro no heap_v*/
        }
        for(int j=0; j<P; j++){ /*loop limitado pelo numero de carros que serão retirados*/
            scanf(" %d", &E);
            if(E==0){ /*Será retirado o carro com a melhor aceleração*/
                print_carro(heap_a->v[0]->atri); /*Imprime os atributos do carro que sera retirado*/
                /*Guarda as posicoes do carro que sera retirado*/
                x = heap_a->v[0]->pos[0];
                y = heap_a->v[0]->pos[1];
                z = heap_a->v[0]->pos[2];
                Remover(heap_a, x); /*Remove o carro na posicao x do heap_a*/
                Remover(heap_c, y); /*Remove o carro na posicao y do heap_c*/
                Remover(heap_v, z); /*Remove o carro na posicao z do heap_v*/
                free(heap_a->v[(heap_a->n)+1]); /*Libera o carro no fim do vetor*/
            }
            else if(E==1){
                print_carro(heap_c->v[0]->atri); /*Imprime os atributos do carro que sera retirado*/
                /*Guarda as posicoes do carro que sera retirado*/
                x = heap_c->v[0]->pos[0];
                y = heap_c->v[0]->pos[1];
                z = heap_c->v[0]->pos[2];
                Remover(heap_a, x); /*Remove o carro na posicao x do heap_a*/
                Remover(heap_c, y); /*Remove o carro na posicao y do heap_c*/
                Remover(heap_v, z); /*Remove o carro na posicao z do heap_v*/
                free(heap_c->v[(heap_c->n)+1]); /*Libera o carro no fim do vetor*/
            }
            else if(E==2){
                print_carro(heap_v->v[0]->atri); /*Imprime os atributos do carro que sera retirado*/
                /*Guarda as posicoes do carro que sera retirado*/
                x = heap_v->v[0]->pos[0];
                y = heap_v->v[0]->pos[1];
                z = heap_v->v[0]->pos[2];
                Remover(heap_a, x); /*Remove o carro na posicao x do heap_a*/
                Remover(heap_c, y); /*Remove o carro na posicao y do heap_c*/
                Remover(heap_v, z); /*Remove o carro na posicao z do heap_v*/
                free(heap_v->v[(heap_v->n)+1]); /*Libera o carro no fim do vetor*/
            }
        }
    }
    Liberar_Elementos(heap_a);
    Liberar_Heap(heap_a);
    Liberar_Heap(heap_c);
    Liberar_Heap(heap_v);
    return 0;
}
