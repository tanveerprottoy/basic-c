#include <stdio.h>

void pointer() {
    int* a;
    int b;

    b = 5;
    a = &b;

    printf("b: %p\n", b);
    printf("a: %p\n", a);

    printf("*a: %d\n", *a);
}

void pointer_to_pointer() {
    int* a;
    int** b;
    int c;

    c = 10;
    a = &c;
    b = &a;

    printf("c: %p\n", c);
    printf("a: %p\n", a);
    printf("b: %p\n", b);

    printf("*a: %d\n", *a);
    printf("**b: %d\n", **b);

    int a = 10;
    int* p = &a;    // p points to a
    int** pp = &p;  // pp points to p

    printf("%d\n", a);     // 10
    printf("%d\n", *p);    // 10
    printf("%d\n", **pp);  // 10
}
