/* Francisco Namias Vicente
   RA 216028 */

#ifndef lab07_h
#define lab07_h

/***DEFINES***/
#define PAI(n) ((n-1)/2)
#define FILHOESQ(n) (2*n + 1)
#define FILHODIR(n) (2*n + 2)
#define RAIZ 0

/***FUNCOES***/
void print_carro(float *v);
void copiar_carro(float *v1, float *v2);
int carros_iguais(float *v1, float *v2);
void trocar_carros(float *v1, float *v2);
int folha(int i, int n);
int tem_filho_dir(int i, int n);
void Subir_Heap(float **heap, int pos, int mod);
void Descer_Heap(float **heap, int pos, int tam, int mod);
void Inserir(float **heap, float *novo, int *tam, int mod);
void Remover(float **heap, int *tam, int pos, int mod);
int Buscar(float **heap, int tam, float *carro, int pos, int mod);
void Liberar_Heap(float **heap, int max);

#endif
