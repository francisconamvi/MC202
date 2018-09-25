#include<stdio.h>

int main(){
    int x,y;
    int *p1;
    int *p2;
    x = 10;
    y = 20;
    p1 = &x;
    p2 = &y;
    (*p1)++;

    printf("%d\n", *(&x));
    return 0;
}
