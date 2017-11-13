#include <stdio.h>
#include <stdlib.h>

void main() {
    int x, y;
    int * p;
    
    printf("--------------------------------------------------------------\n");
    printf("STEP 1: Printing Sizes\n");
    printf("Sizeof(int) = %d\n", sizeof(int));
    printf("Sizeof(memory address) = %d\n", sizeof(p));
    printf("--------------------------------------------------------------\n");

    printf("STEP 2: Variables -- Before initialization\n");
    printf("x:    &x = %p     x = %d\n", (void *)&x, x);
    printf("y:    &y = %p     y = %d\n", (void *)&y, y);
    printf("p:    &p = %p     p = %p    *p = %d\n", (void *)&p, (void *)p, *p);
    printf("--------------------------------------------------------------\n");
    
    x = 25;
    y = 1986;
    p = &x;
    printf("STEP 3: Variables -- After initialization\n");
    printf("x:    &x = %p     x = %d\n", (void *)&x, x);
    printf("y:    &y = %p     y = %d\n", (void *)&y, y);
    printf("p:    &p = %p     p = %p    *p = %d\n", (void *)&p, (void *)p, *p);
    printf("--------------------------------------------------------------\n");
    
    *p = 55;
    p = &x;
    printf("STEP 4: Pointer content with new value\n");
    printf("x:    &x = %p     x = %d\n", (void *)&x, x);
    printf("y:    &y = %p     y = %d\n", (void *)&y, y);
    printf("p:    &p = %p     p = %p    *p = %d\n", (void *)&p, (void *)p, *p);
    printf("--------------------------------------------------------------\n");
    
    *p = 1443558584;
    int *pointer;
    p = &x;
    pointer = p;
    printf("STEP 5: Variable assignation to pointer\n");
   /* printf("%p    %p    %d\n", (void *)&pointer,(void *)pointer, *pointer); */
    printf("x:    &x = %p     x = %d\n", (void *)&x, x);
    printf("y:    &y = %p     y = %d\n", (void *)&y, y);
    printf("p:    &p = %p     p = %p    *p = %d\n", (void *)&p, (void *)p, *p);
    printf("--------------------------------------------------------------\n");

}
