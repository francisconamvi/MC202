#include <stdio.h>

/* funcao bin pega o numero decimal e retorna seus ultimos dois bits em binario*/
int bin(int n){
    return(n%2+((n/2)%2)*2);
}

/*funcao dec pega o numero binario e retorna seu valor decimal*/
int dec(int n){
    if (n==0) return(0);
    else if (n==1) return(1);
    else if (n==10) return(2);
    else if (n==11) return(3);
}

int main(){
    int PN, c, l, max, i, aux;
    int a,b,ce,d, letra;
    char P;
    /*scanf que recolhe o valor de todas as variaveis que nao sao os pixels da imagem*/
    scanf(" %c%d %d %d %d", &P, &PN, &c, &l, &max);

    /*for que ira percorrer todos os pixels multiplos de 4 da imagem*/
    for(i=0;i<=(l*c);i = i+4){
        scanf(" %d",&aux);
        a = bin(aux);
        scanf(" %d",&aux);
        b = bin(aux);
        scanf(" %d",&aux);
        ce = bin(aux);
        scanf(" %d",&aux);
        d = bin(aux);
        letra = dec(a)*64+dec(b)*16+dec(ce)*4+dec(d);
        if(letra=='\0') break; /*se achar o \0 irá finalizar o for, pois acabou a mensagem*/
        printf("%c", letra);
    }

    return 0;
}
