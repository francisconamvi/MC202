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
    fscanf(arq_l, "%s", pessoa.nome);
    while(pessoa.nome[0] == ',') fscanf(arq_l, "%s", pessoa.nome); /*loop para evitar que o Pessoa.nome seja composto unicamente de uma virgula*/
    fscanf(arq_l, "%s", pessoa.email);
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
    for(int i=0; i<linhas; i++)
        fprintf(arq_w, "%ld, %s %s %d\n", data_base[i].cpf, data_base[i].nome, data_base[i].email, data_base[i].idade); /*gravando dados do vetor no arquivo de saida*/
    fclose(arq_w);

    return 0;
}
