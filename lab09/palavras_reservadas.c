/* Francisco Namias Vicente
   RA: 216028 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAIORPALAVRA 20 /*Estimativa de qual é a maior palavra no codigo de entrada*/

/*Struct do No das arvores de busca AVL*/
typedef struct No{
    char palavra[9];
    int profundidade;
    struct No *dir, *esq;
}No;


/*Funcoes auxiliares para operacoes*/
int altura (No *raiz){
    int h_esq, h_dir;
    if (raiz==NULL)
        return 0;
    else{
        h_esq = altura(raiz->esq);
        h_dir = altura(raiz->dir);
        return 1 + (h_esq > h_dir ? h_esq : h_dir);
    }
}

int maior(char p1[], char p2[]){ /*diz qual das duas palavras é maior*/
    /*1 = p1>p2
     -1 = p2>p1
      0 = p1=p2
    */
    for(int i=0; i<9; i++){
        if(p1[i]==0 && p2[i]==0) return 0;
        else if(p1[i]==0) return -1;
        else if(p2[i]==0) return 1;

        if(p1[i] > p2[i]) return 1;
        else if(p1[i] < p2[i]) return -1;
        else continue;
    }
    return 0;
}

void zerar_palavra(char palavra[]){
    for(int i=0; i<MAIORPALAVRA; i++){
        palavra[i] = 0;
    }
}

int pertence(char *palavra, No *arv){
    if(arv==NULL) return 0;
    if(maior(palavra, arv->palavra)==0) return 1;
    if(maior(palavra,arv->palavra)>0)
        return pertence(palavra, arv->dir);
    else
        return pertence(palavra, arv->esq);
}

No *att_profundidade(No *arv, int p){
    if(arv==NULL) return arv;
    arv->profundidade = p;
    arv->esq = att_profundidade(arv->esq, p+1);
    arv->dir = att_profundidade(arv->dir, p+1);
    return arv;
}

/*Funcoes de rotacao*/
No *rotacao_esq(No *raiz){
    No *nova_raiz = raiz->dir;
    raiz->dir = nova_raiz->esq;
    nova_raiz->esq = raiz;
    return nova_raiz;
}

No *rotacao_dir(No *raiz){
    No *nova_raiz = raiz->esq;
    raiz->esq = nova_raiz->dir;
    nova_raiz->dir = raiz;
    return nova_raiz;
}

No *rotacao_dupla_esq(No *raiz){
    raiz->dir = rotacao_dir(raiz->dir);
    raiz = rotacao_esq(raiz);
    return raiz;
}

No *rotacao_dupla_dir(No *raiz){
    raiz->esq = rotacao_esq(raiz->esq);
    raiz = rotacao_dir(raiz);
    return raiz;
}

/*Funcao da arvore binaria de busca AVL*/
No *criar_no(char palavra[]){
    No *novo = (No*) malloc(sizeof(No));
    strcpy(novo->palavra, palavra);
    novo->profundidade = 1; /*numero aleatorio pois isto é importante apenas para o final*/
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserir(char palavra[], No *arv){
    if(arv==NULL){
        No *novo = criar_no(palavra);
        return novo;
    }
    if(maior(palavra, arv->palavra)>0)
        arv->dir = inserir(palavra, arv->dir);
    else if(maior(palavra, arv->palavra)<0)
        arv->esq = inserir(palavra, arv->esq);
    return arv;
}

No *verificar(No *arv){
    if(arv==NULL) return arv;

    int Q = altura(arv->dir) - altura(arv->esq);

    if(Q>1){
        int Qr = altura(arv->dir->dir) - altura(arv->dir->esq);
        if(Qr<0)
            arv = rotacao_dupla_esq(arv);
        else
            arv = rotacao_esq(arv);
    }
    else if(Q<-1){
        int Qe = altura(arv->esq->dir) - altura(arv->esq->esq);
        if(Qe>0)
            arv = rotacao_dupla_dir(arv);
        else
            arv = rotacao_dir(arv);
    }

    arv->esq = verificar(arv->esq);
    arv->dir = verificar(arv->dir);
    return arv;
}

No *liberar_arvore(No* arv){
    if(arv!=NULL){
        arv->dir = liberar_arvore(arv->dir);
        arv->esq = liberar_arvore(arv->esq);
        free(arv);
    }
    return NULL;
}

No *criar_arv_proibidas(char lista[32][9]){
    No *arv = NULL;
    for(int i=0; i<32; i++){
        arv = inserir(lista[i], arv);
        arv = verificar(arv);
    }
    return arv;
}

/*Funcoes para printar a arvore*/
void print_esq(No *arv, int p){ /*esquerda pra direita\*/
    if(arv!=NULL){
        print_esq(arv->esq, p);
        if(arv->profundidade == p){ /*se no tiver a profundidade desejada, printa*/
            printf("%s ", arv->palavra);
        }
        print_esq(arv->dir, p);
    }
    return;
}

void print_dir(No *arv, int p){ /*direita pra esquerda*/
    if(arv!=NULL){
        print_dir(arv->dir, p);
        if(arv->profundidade == p){ /*se no tiver a profundidade desejada, printa*/
            printf("%s ", arv->palavra);
        }
        print_dir(arv->esq, p);
    }
    return;
}

void zigzag(No *arv, int p, int max){
    if(p==max) return;
    if(p%2==1){ /*se profundidade for impar, printa da esquerda pra direita*/
        printf("[ ");
        print_esq(arv,p);
        printf("]");
    }
    else{ /*se profundidade for par, printa da direita pra esquerda*/
        printf("[ ");
        print_dir(arv,p);
        printf("]");
    }
    printf("\n");
    zigzag(arv, p+1, max); /*printa proximo nivel*/
    return;
}

int main(){
    /*vetor de palavras proibidas*/
    char proibidas[32][9] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    No *arv_proibidas = criar_arv_proibidas(proibidas); /*palavras proibidas organizadas numa arvore para que as operações sejam mais eficientes*/
    No *arv = NULL; /*arvore onde serao depositadas as palavras do código de entrada*/
    int cont = 0; /*contador de loops*/
    char *palavra = (char*) malloc(MAIORPALAVRA*sizeof(char));
    char lixo;
    do{
        zerar_palavra(palavra);
        scanf(" %[^#<> {};*():,=-""''%% .+\n]s", palavra); /*Ler a entrada até o primeiro caracter diferente*/
        scanf("%c", &lixo); /*recolher caracter que nao sera utilizado*/
        if(palavra[0]==0){
            cont++;
            if(cont==5) break; /*se a palavra nao se alterar em 5 loops, significa que nao esta mais atualizando e o programa acabou*/
        }
        else cont = 0;
        if(pertence(palavra, arv_proibidas)){ /*se a palavra esta na arvore proibidas*/
            arv = inserir(palavra, arv); /*insere a palavra na arvore*/
            arv = verificar(arv); /*verifica e balanceia a arvore*/
        }
    }while(1);
    arv = att_profundidade(arv,0); /*atualiza a profundidade de cada no da arvore*/
    int max = altura(arv); /*profundidade maxima, que eh igual a altura da raiz + 1 (nao somei um porque teria que subtrair na funcao)*/
    printf("O percurso da árvore é:\n");
    zigzag(arv, 0, max); /*printa arvore em zigzag*/

    /*Liberar espaço das árvore*/
    arv_proibidas = liberar_arvore(arv_proibidas);
    arv = liberar_arvore(arv);
    free(palavra);

    return 0;
}
