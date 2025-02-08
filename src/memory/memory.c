#include <stdio.h>
#include <stdlib.h>

void m_alloc() {
    int n, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // allocate memory
    ptr = (int *)malloc(n * sizeof(int));

    // if memory cannot be allocated
    if (ptr == NULL) {
        printf("Error! memory not allocated.");

        exit(0);
    }

    printf("Enter elements: ");

    for (i = 0; i < n; ++i) {
        scanf("%d", ptr + i);

        sum += *(ptr + i);
    }

    printf("Sum = %d", sum);

    // deallocate the memory
    free(ptr);
}

void c_alloc() {
    int n, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    ptr = (int *)calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Error! memory not allocated.");

        exit(0);
    }

    printf("Enter elements: ");

    for (i = 0; i < n; ++i) {
        scanf("%d", ptr + i);

        sum += *(ptr + i);
    }

    printf("Sum = %d", sum);

    free(ptr);
}

void r_alloc() {
    int *ptr, i, n1, n2;

    printf("Enter size: ");
    scanf("%d", &n1);

    ptr = (int *)malloc(n1 * sizeof(int));

    printf("Addresses of previously allocated memory:\n");

    for (i = 0; i < n1; ++i)
        printf("%pc\n", ptr + i);

    printf("\nEnter the new size: ");
    scanf("%d", &n2);

    // rellocating the memory
    ptr = realloc(ptr, n2 * sizeof(int));

    printf("Addresses of newly allocated memory:\n");

    for (i = 0; i < n2; ++i)
        printf("%pc\n", ptr + i);

    free(ptr);
}

int main() {
    mem_alloc();
    
    return 0;
}