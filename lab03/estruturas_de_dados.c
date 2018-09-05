#include<stdio.h>
#include<string.h>

typedef struct {
    long int cpf;
    char nome[41];
    char email[31];
    int idade;
} Pessoa;

Pessoa recolher_dados(FILE *arq_l){ 
    Pessoa pessoa;
    fscanf(arq_l, "%ld", &pessoa.cpf);
    fscanf(arq_l, "%s", pessoa.nome);
    while(pessoa.nome[0] == ',') fscanf(arq_l, "%s", pessoa.nome);
    fscanf(arq_l, "%s", pessoa.email);
    fscanf(arq_l, "%d", &pessoa.idade);

    return pessoa;
}

int main(){
    FILE *arq_l = fopen("read.txt", "r");
    Pessoa data_base[10];
    for(int i=0; i<10; i++){
        data_base[i] = recolher_dados(arq_l);
        printf("%d %ld\n", i, data_base[i].cpf);
        printf("%d %s\n", i, data_base[i].nome);
        printf("%d %s\n", i, data_base[i].email);
        printf("%d %d\n", i, data_base[i].idade);
    }

    return 0;
}
