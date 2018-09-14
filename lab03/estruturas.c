#include<stdio.h>
#include<stdlib.h>

typedef struct {
    /*struct que armazenara as informações de cada pessoa*/
    char cpf[12];
    char nome[41];
    char email[31];
    int idade;
} Pessoa;

int esqmaior(char n1[12], char n2[12]){
    /*funcao que ira comparar os dois cpfs e dira se o da esquerda e maior*/
    for(int i=0; i<12; i++){
        if(n1[i]>n2[i]) return 1;
        else if (n1[i]<n2[i]) return 0;
    }
    return 1;
}

void ordenar(Pessoa *vetor, int tam){
    /*funcao para ordenar o vetor de pessoas
     * foi usado o algoritmo de Insertion Sort adaptado*/
    int i, j;
    Pessoa aux;
    for(i=1; i<tam; i++){
        aux = vetor[i];
        for(j=i-1; (j>=0) && ((vetor[j].idade>aux.idade) || ((esqmaior(vetor[j].cpf,aux.cpf)) && (vetor[j].idade==aux.idade))); j--)
            vetor[j+1] = vetor[j];
        vetor[j+1]= aux;
    }
}

int main(){
    int fim; /*variavel que indica o fim do vetor*/
    Pessoa *data_base = malloc(1000*sizeof(Pessoa)); /*cria um vetor para armazenar as structs Pessoa*/
    for(int i=0; i<1000; i++){
        scanf(" %[^,],%[^,],%[^,],%d", data_base[i].cpf, data_base[i].nome, data_base[i].email, &data_base[i].idade);
        if(data_base[i].cpf[0]==0){ /*se conteudo do cpf é vazio*/
            fim = i;
            break;
        }
    }
    ordenar(data_base, fim); /*ordena o vetor em ordem crescente de idade e cpf, caso hajam dois com a mesma idade*/
    for(int i=0; i<fim; i++){
        printf("%s, %s, %s, %d \n", data_base[i].cpf, data_base[i].nome, data_base[i].email, data_base[i].idade);
    }
    free(data_base); /*desaloca a memoria*/
    return 0;

}
