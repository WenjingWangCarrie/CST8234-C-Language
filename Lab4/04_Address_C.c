#include <stdio.h>
#include <stdlib.h>

void main() {
    int x = 5;
    int * p;
    int * q;
    q = &x;
    p = (int *) malloc(sizeof(int));
    *p = 50;

    printf("--------------------------------------------------------------\n");
    printf("In main() after memory allocation\n");
    printf("x:    &x = %p     x = %d\n", (void *)&x, x);
    printf("q:    &q = %p     q = %p     *q = %d\n", (void *)&q, (void *)q, *q);
    printf("p:    &p = %p     p = %p     *p = %d\n", (void *)&p, (void *)p, *p);
    printf("\n");
    printf("--------------------------------------------------------------\n");
    
    free(p);

}
