#include <stdio.h>
#include <stdlib.h>

void simple_malloc() {
    int* ptr;

    // allocate memory
    ptr = (int*)malloc(sizeof(int) * 10);
    if (ptr == NULL) {
        printf("Memory not allocated");

        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < 10; i++) {
        *(ptr + i) = i;
    }

    printf("Printing elements: ");

    for (int i = 0; i < 10; i++) {
        printf("%d ", *(ptr + i));
    }

    // deallocate the memory
    free(ptr);

    // set the pointer to NULL
    ptr = NULL;
}

void m_alloc() {
    int n, i, sum = 0;
    int* ptr;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // allocate memory
    // malloc() function allocates memory and leaves the memory uninitialized
    ptr = (int*)malloc(sizeof(int) * n);

    // if memory cannot be allocated
    if (ptr == NULL) {
        printf("Error! memory not allocated.");

        exit(EXIT_SUCCESS);
    }

    printf("Enter elements: ");

    for (i = 0; i < n; ++i) {
        scanf("%d", ptr + i);

        sum += *(ptr + i);
    }

    printf("Sum = %d", sum);

    // deallocate the memory
    free(ptr);

    // set the pointer to NULL
    ptr = NULL;
}

void c_alloc() {
    int n, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // the calloc() function writes zeroes into all of the allocated memory
    ptr = (int*)calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Error! memory not allocated.");

        exit(EXIT_SUCCESS);
    }

    printf("Enter elements: ");

    for (i = 0; i < n; ++i) {
        scanf("%d", ptr + i);

        sum += *(ptr + i);
    }

    printf("Sum = %d", sum);

    // deallocate the memory
    free(ptr);

    // set the pointer to NULL
    ptr = NULL;
}

void r_alloc() {
    int i, n1, n2;
    int* ptr;

    printf("Enter size: ");
    scanf("%d", &n1);

    ptr = (int*)malloc(sizeof(int) * n1);

    printf("Addresses of previously allocated memory:\n");

    for (i = 0; i < n1; ++i) {
        printf("%pc\n", ptr + i);
    }

    printf("\nEnter the new size: ");
    scanf("%d", &n2);

    // rellocating the memory
    ptr = realloc(ptr, n2 * sizeof(int));

    printf("Addresses of newly allocated memory:\n");

    for (i = 0; i < n2; ++i) {
        printf("%pc\n", ptr + i);
    }

    // deallocate the memory
    free(ptr);

    // set the pointer to NULL
    ptr = NULL;
}
