#include<stdio.h>
#include<stdlib.h>
#define n 3

void printm(int **m){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int **soma(int **m1, int **m2, int **m3){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m3[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return m3; 
}

int **mult(int **m1, int **m2, int **m3){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                m3[i][j] += m1[i][k] *  m2[k][j];
            }
        }
    }
    return m3; 

}

int main(){
    int **m1 = malloc(n*sizeof(int));
    int **m2 = malloc(n*sizeof(int));
    int **m3 = malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        m1[i] = malloc(n*sizeof(int));
        m2[i] = malloc(n*sizeof(int));
        m3[i] = malloc(n*sizeof(int));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf(" %d", &m1[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf(" %d", &m2[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m3[i][j] = 0;
        }
    }
    printm(m1);
    printm(m2);
    //m3 = soma(m1,m2,m3);
    m3 = mult(m1,m2,m3);
    printm(m3);
     
    return 0;
}
