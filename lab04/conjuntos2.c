/* Nome: Francisco Namias Vicente
 * RA: 216028
 * */


#include<stdio.h>
#include<stdlib.h>

/*Struct No que tem como info o num e um ponteiro para o prox elemento da lista*/
typedef struct No{
    int num;
    struct No *prox;
} No;

/*Funcoes para imprimir recursivamente a lista*/
void imprimir_lista(No *lista) {
    if (lista != NULL && lista->prox!=NULL) {
        printf("%d,", lista->num);
        imprimir_lista(lista->prox);
    }
    else if (lista != NULL && lista->prox==NULL) {
        printf("%d", lista->num);
        imprimir_lista(lista->prox);
    }
}

void imprimir_conjunto(No *conj) {
    printf("{");
    imprimir_lista(conj);
    printf("}\n");
}

/*Determina recursivamente a posicao onde o aux deve ficar*/
No *posicao_aux(No *aux, No *novo){
    if (aux->prox != NULL){
        if (aux->prox->num < novo->num)
            return posicao_aux(aux->prox, novo);
    }
    else
        return aux;
    return aux;
}

/*Funcao booleana que diz se num está em algum no da lista (retorna 0 ou 1)*/
int pertence_bool(int num, No *aux){
    if(aux==NULL){
        return 0;
    }
    else if(aux->num == num){
        return 1;
    }
    else{
        return pertence_bool(num, aux->prox);
    }
    return 0;
}

/*Funcao para Inserir Noh no conj*/
No *Insere(No *novo, No *conj, No *aux){
    if(pertence_bool(novo->num, conj)) /*Se noh ja esta no conj, nao insere*/
        return conj;
    
    if(conj==NULL){ /*se lista for vazia*/
        novo->prox = NULL;
        return novo; /*Novo eh o inicio do conj, entao retorna ele*/
    }
    else{
        aux = conj; /*Aponta aux para o inicio do conj*/
        if(aux->num > novo->num){ /*se elemento ja estiver na cabeça da lista*/
            novo->prox = aux;
            return novo;
        }
        aux = posicao_aux(aux, novo); /*acha o local onde será inserida a variavel, recursivamente*/
        novo->prox = aux->prox;
        aux->prox = novo;
        return conj;
    }
}

/*Funcao que printa NAO se num nao esta em nenhum noh da lista
 * e printa SIM caso estiver em algum noh da lista*/
void Pertence(int num, No *aux){
    if(aux==NULL){
        printf("NAO\n");
        return;
    }
    else if(aux->num == num){
        printf("SIM\n");
        return;
    }
    else{
        Pertence(num, aux->prox);
    }
}

/*Funcao que remove Noh do conj*/
No *Remove(int num, No *conj, No *aux){
    if(aux==conj && aux->num == num){ /*Numero esta na primeira posição*/
        No *kamikaze = conj; /*No que existe soh dentro da funcao que serve so pra dar free no noh que sera destruido*/
        conj = conj->prox;
        free(kamikaze);
        return conj;
    }
    else if(aux->prox->num == num){ /*se o proximo for o noh a ser retirado*/
        No *aux2 = aux->prox; /*guarda o prox num auxilia*/
        free(aux->prox); /*da free no proximo*/
        aux->prox = aux2->prox; /*liga o atual com o proximo do proximo*/
        return conj;
    }
    else{
        return(Remove(num, conj, aux->prox)); /*Desloca o aux, recursivamente*/
    }
}

/*Funcao que faz a uniao dos dois conjuntos*/
No *Uniao(No *conj1, No *conj2, No *aux){ 
    /*na primeira chamada da funcao, aux esta no inicio do conj2*/
    if(aux==NULL){ /*caso encontre o fim, ja retorna conj1*/
        return conj1;
    }
    else if(!(pertence_bool(aux->num, conj1))) {/*Se o numero que aux esta lendo no conj2 NAO esta no conj1, insere ele no conj1*/
        No *aux2 = NULL;
        No *novo = (No*) malloc(sizeof(No)); /*Aloca um novo noh*/
        *novo = *aux; /*Este novo noh tem as informacoes do aux, mas tem enderecos diferentes*/
        conj1 = Insere(novo, conj1, aux2); /*Insere esse novo noh no conj1, usando aux1 para se movimentar*/
    }
    return(Uniao(conj1, conj2, aux->prox)); /*Caso numero estiver no conj1, passa pro proximo da lista do conj2*/
}

No *Interseccao(No *inter, No *conj1, No *conj2, No *aux){
    if(aux==NULL){ /*Na primeira chamada aux esta no conj1, se conj1 eh vazio, nao ha interseccao*/
        return inter; 
    }
    else{
        if(pertence_bool(aux->num, conj2)){ /*Se numero estiver no conj2*/
            No *novo = (No*) malloc(sizeof(No)); /*Cria um novo noh*/
            *novo = *aux; /*Copia as informacoes do aux*/
            No *aux2 = inter; /*aux2 aponta para o comeco da interseccao*/
            inter = Insere(novo, inter, aux2); /*Insere o novo noh no inter*/
        }
        return Interseccao(inter, conj1, conj2, aux->prox); /*Chama recursivamente a funcao para o prox elemento*/
    }
    return inter;
}

No *Subtracao(No *conj1, No *conj2, No *aux){
    /*aux começa no inicio do conj1*/
    if(aux==NULL){ /*Se conj1 for vazio nao ha subtracao*/
        return conj1;
    }
    else{
        if(pertence_bool(aux->num, conj2)){ /*se num num estiver no conj2*/
            No *aux2 = conj1; /*Coloca aux2 no inicio do conj1*/
            conj1 = Remove(aux->num, conj1, aux2); /*remove o noh do conj1*/
        }
        return Subtracao(conj1, conj2, aux->prox); /*Chama recursivamente a funcao para o proximo*/
    }
}


int main(){
    char comando; 
    int num, conj;
    /*criando as duas listas de conjuntos e um aux*/
    No *conj1 = NULL;
    No *conj2 = NULL;
    No *aux = conj1;

    /*Le o primeiro comando*/
    scanf(" %c", &comando);
    while(comando != 's'){ /*sai do while quando digitar s*/
        if(comando=='i'){ /*Inserir*/
            scanf(" %d%d", &num, &conj);
            
            /*Cria um novo no e armazena o num nele*/
            No *novo = (No*) malloc(sizeof(No));
            novo->num = num; 
            if(conj==1) conj1 = Insere(novo, conj1, aux); /*Insere o no novo no conj1*/
            else conj2 = Insere(novo, conj2, aux); /*Insere o no novo no conj2*/
        }
        else if(comando=='p'){ /*Pertence*/
            scanf(" %d%d", &num, &conj);
            if(conj==1) Pertence(num, conj1); /*Verifica se há um noh no conj1 que tem num*/
            else Pertence(num, conj2); /*Verifica se há um noh no conj2 que tem num*/
        }
        else if(comando=='r'){ /*Remove*/
            scanf(" %d%d", &num, &conj);
            if(conj==1){
                aux = conj1; /*coloca o aux apontando pro inicio do conj1*/
                conj1 = Remove(num, conj1, aux); /*Remove o primeiro no que tem num no conj1*/
            }
            else{
                aux = conj2; /*coloca o aux apontando pro inicio do conj2*/
                conj2 = Remove(num, conj2, aux); /*Remove o primeiro no que tem num no conj2*/
            }
        }
        else if(comando=='u'){ /*União*/
            aux = conj2; /*Coloca aux no inicio do conj2*/
            conj1 = Uniao(conj1, conj2, aux); /*faz a uniao dos dois conjuntos e armazena no conj1*/
        }
        else if(comando=='x'){ /*Interseccao*/
            No *inter = NULL; /*Cria uma nova lista pra só pra organizar a interseccao*/
            aux = conj1; /*Coloca o aux no inicio do conj1*/
            conj1 = Interseccao(inter, conj1, conj2, aux); /*Faz a interseccao e armazena no conj1*/
        }
        else if(comando=='b'){ /*Subtracao*/
            aux = conj1; /*Coloca o aux no inicio do conj1*/
            conj1 = Subtracao(conj1, conj2, aux); /*faz subtracao dos elementos do conj1 pelo conj2*/
        }

        /*Imprime atual situacao dos conjuntos e pega novo comando*/
        imprimir_conjunto(conj1);
        imprimir_conjunto(conj2);
        scanf(" %c", &comando);
    }

    /*Imprime e finaliza programa*/
    imprimir_conjunto(conj1);
    imprimir_conjunto(conj2);    

    return 0;
}
