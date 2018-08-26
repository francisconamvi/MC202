#include <stdio.h>  /*Biblioteca para input e output*/
#include <math.h>   /*Biblioteca com a funcao de raiz quadrada*/

/*funcao que vai fazer a convulucao ao redor do pixel dado (i,j)*/
int convulucao(long int img[98][130], int F[3][3],int i, int j){
    int x,y,z=0;
    for(x=-1;x<2;x++){
        for(y=-1;y<2;y++){
            z += img[i+x][j+y]*F[x+1][y+1];
        }
    }
    return z;
}


int main(){
    int i,j;

    /*Funcoes que serao aplicadas na imagem*/
    int Fx[3][3] = {
        {1,0,-1},
        {2,0,-2},
        {1,0,-1}
    };
    int Fy[3][3] = {
        {1,2,1},
        {0,0,0},
        {-1,-2,-1}
    };

    /*criando matrizes imagem's e adicionando 0s*/
    long int imagem[98][130];
    long int imagemx[98][130];
    long int imagemy[98][130];
    long int imagemfinal[96][128];

    for(i=0;i<98;i++){
        for(j=0;j<130;j++){
            imagem[i][j] = 0;
            imagemx[i][j] = 0;
            imagemy[i][j] = 0;
        }
    }

    for(i=0;i<96;i++){
        for(j=0;j<128;j++){
            imagemfinal[i][j] = 0;
        }
    }

    /*Pegando entrada e colocando na matriz "imagem"*/
    for(i=1;i<97;i++){
        for(j=1;j<129;j++){
            scanf(" %ld", &imagem[i][j]);
        }
    }

    /*convulução com a x*/
    for(i=1;i<97;i++){
        for(j=1;j<129;j++){
            imagemx[i][j] = convulucao(imagem,Fx,i,j);
        }
    }

    /*convulução com a y*/
    for(i=1;i<97;i++){
        for(j=1;j<129;j++){
            imagemy[i][j] = convulucao(imagem,Fy,i,j);
        }
    }

    /*aplica pitagoras na imagemx e imagemy e escrevendo imagemfinal*/
    for(i=1;i<97;i++){
        for(j=1;j<129;j++){
            imagemfinal[i-1][j-1] = sqrt(pow(imagemx[i][j],2) + pow(imagemy[i][j],2));
        }
    }

    /*printa imagem final*/
    for(i=0;i<96;i++){
        for(j=0;j<128;j++){
            if (j != 0) printf(" ");
            printf("%ld", imagemfinal[i][j]);
        } printf("\n");
    }

    /*finaliza o programa*/
    return 0;
}
