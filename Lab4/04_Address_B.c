#include <stdio.h>
#include <stdlib.h>

void main() {
    int x = 5, y = 10;
    int * p;
    p = &x;

    printf("--------------------------------------------------------------\n");
    printf("FUNCTION main():\n");
    printf("x:    &x = %p     x = %d\n", (void *)&x, x);
    printf("y:    &y = %p     y = %d\n", (void *)&y, y);
    printf("p:    &p = %p     p = %p    *p = %d\n", (void *)&p, (void *)p, *p);
    printf("\n");
    printf("--------------------------------------------------------------\n");
    
    modify_var(y, p);
    
    printf("FUNCTION main():\n");
    printf("x:    &x = %p     x = %d\n", (void *)&x, x);
    printf("y:    &y = %p     y = %d\n", (void *)&y, y);
    printf("p:    &p = %p     p = %p    *p = %d\n", (void *)&p, (void *)p, *p);
    printf("\n");
    printf("--------------------------------------------------------------\n");
}

int modify_var(int a, int *q) {

    printf("\n");
    printf("Calling mod_var(y, p): \n");
    printf("FUNCTION modify_var( ) -- before modifications\n");
    printf("a:    &a = %p     a = %d\n", (void *)&a, a);
    printf("q:    &q = %p     q = %p    *q = %d\n", (void *)&q, (void *)q, *q);
    printf("\n"); 
      
    *q = 45; 
    a = 100;
    printf("FUNCTION modify_var() -- after modifications\n");
    printf("a:    &a = %p     a = %d\n", (void *)&a, a);
    printf("q:    &q = %p     q = %p    *q = %d\n", (void *)&q, (void *)q, *q);
    printf("\n"); 
    printf("--------------------------------------------------------------\n");

    return 0;
}


