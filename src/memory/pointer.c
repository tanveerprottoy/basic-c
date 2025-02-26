#include <stdio.h>

void pointer() {
    int *a, b;
    b = 5;
    a = &b;

    printf("b: %p\n", b);
    printf("a: %p\n", a);

    printf("*a: %d\n", *a);
}