#include<stdio.h>
#include<stdlib.h>

typedef struct {
    /*struct que armazenara as informações de cada pessoa*/
    long int cpf;
    char nome[41];
    char email[31];
    int idade;
} Pessoa;

int contar_linhas(FILE *arq){
    /*funcao que conta as linhas do arquivo, que usa o \n para contar*/
    char aux;
    int i = 0;
    while(fscanf(arq, "%c", &aux)!=EOF)
        if (aux == '\n') i++;
    return i;
}

Pessoa recolher_dados(FILE *arq_l){ 
    /*funcao que ira recolher os dados do arquivo de entrada e criar uma struct para cada pessoa
     * a qual será adicionada no vetor postariormente*/
    Pessoa pessoa;
    fscanf(arq_l, "%ld", &pessoa.cpf);
    for(int i=0; i<41; i++){
        fscanf(arq_l, "%c", &pessoa.nome[i]);
        if(pessoa.nome[i] == ',' && i!=0){
            pessoa.nome[i+1] = '\0';
            break;
        }
    }
    
    for(int i=0; i<31; i++){
        fscanf(arq_l, "%c", &pessoa.email[i]);
        if(pessoa.email[i] == ',' && i!=0){
            pessoa.nome[i+1] = '\0';
            break;
        }
    }
    
    fscanf(arq_l, "%d", &pessoa.idade);
    return pessoa;
}


void ordenar(Pessoa *vetor, int tam){
    /*funcao para ordenar o vetor de pessoas
     * foi usado o algoritmo de Insertion Sort adaptado*/
    int i, j;
    Pessoa aux;
    for(i=1; i<tam; i++){
        aux = vetor[i];
        for(j=i-1; (j>=0) && ((vetor[j].idade>aux.idade) || ((vetor[j].cpf>aux.cpf) && (vetor[j].idade==aux.idade))); j--)
            vetor[j+1] = vetor[j];
        vetor[j+1]= aux;
    }
}


int main(){
    FILE *arq_l = fopen("read.txt", "r"); /*declarando e abrindo arquivo para a leitura*/
    int linhas = contar_linhas(arq_l); /*guarda numa variavel o numero de linhas do arquivo de leitura*/
    rewind(arq_l); /*abre novamente o arquivo de leitura*/
    Pessoa *data_base = malloc(linhas*sizeof(Pessoa)); /*cria um vetor para armazenar as structs Pessoa*/
    for(int i=0; i<linhas; i++)
        data_base[i] = recolher_dados(arq_l); /*guarda em cada espaço do vetor os dados das pessoas*/

    
    fclose(arq_l); /*como o arquivo de entrada já foi guardado no vetor, pode ser fechado*/
    ordenar(data_base, linhas); /*ordena o vetor em ordem crescente de idade e cpf, caso hajam dois com a mesma idade*/

    FILE *arq_w = fopen("write.txt", "w"); /*declara e abre o arquivo onde será escrito o vetor de maneira ordenada*/
    for(int i=0; i<linhas; i++){
        fprintf(arq_w, "%ld", data_base[i].cpf);
        for(int j=0; j<41; j++){
            if (data_base[i].nome[j] == ',' && j!=0) break;
            fprintf(arq_w, "%c", data_base[i].nome[j]);
        }
        fprintf(arq_w, ",");
        for(int j=0; j<31; j++){
            if (data_base[i].email[j] == ',' && j!=0) break;
            fprintf(arq_w, "%c", data_base[i].email[j]);
        }
        fprintf(arq_w, ",");
        fprintf(arq_w, "%d \n", data_base[i].idade);
    }
    fclose(arq_w);
    free(data_base);

    return 0;
}
