/* Francisco Namias Vicente
   RA 216028 */

#ifndef lab07_h
#define lab07_h

/***DEFINES***/
#define PAI(n) ((n-1)/2)
#define FILHOESQ(n) (2*n + 1)
#define FILHODIR(n) (2*n + 2)

/***STRUCTS***/
typedef struct Carro{
    float atri[3];
    int pos[3];
}Carro;

typedef struct Heap{
    Carro **v;
    int n, MC, mod;
}Heap;

/***FUNCOES***/
void print_carro(float *v);
int folha(int i, int n);
int tem_filho_dir(int i, int n);
Heap *criar_heap(int MC, int mod);
void Subir_Heap(Heap *heap, int pos);
void Descer_Heap(Heap *heap, int pos);
void Inserir(Heap *heap, Carro *novo);
void Remover(Heap *heap, int pos);
void Liberar_Elementos(Heap *heap);
void Liberar_Heap(Heap *heap);

#endif
