#include <stdio.h>

/*
Pointer Arithmetic (e.g., traversing arrays via pointers)
In C, pointer arithmetic works based on the size of the data type the pointer points to.
Example: Traversing an array using pointers
*/
void traversing_array_via_pointers() {
    // ptr + i adds i * sizeof(int) bytes to the address ptr
    // *(ptr + i) dereferences the resulting address
    int arr[] = {10, 20, 30, 40};
    int* ptr = arr;  // Same as &arr[0]

    for (int i = 0; i < 4; i++) {
        printf("%d\n", *(ptr + i));  // Access via pointer arithmetic
    }

    // alternate way
    // You can also increment the pointer directly:
    while (ptr < arr + 4) {
        printf("%d\n", *ptr);
        ptr++;  // Move to next int (4 bytes forward)
    }

    // pointer arithmetic is only valid within the bounds of the same allocated object.
}

struct Point {
    int x, y;
};

void pointers_to_structs() {
    struct Point p = {1, 2};
    struct Point* ptr = &p;

    printf("%d %d\n", ptr->x, ptr->y);  // Arrow operator is shortcut for (*ptr).x
    // ptr->x is the same as (*ptr).x.
}

void pointers_to_array() {
    int arr[3] = {1, 2, 3};
    int (*ptr)[3] = &arr;  // Pointer to an array of 3 integers

    printf("%d\n", (*ptr)[1]);  // Access second element

    // the above example is different from:
    // int* ptr = arr;  // Pointer to first element
    // Array decay: In most contexts, arr decays to &arr[0], so int* ptr = arr works for traversing
}

void const_volatile_with_pointers() {
    const int* ptr1;        // Pointer to a constant int (read-only data)
    int* const ptr2;        // Constant pointer to int (cannot change address)
    const int* const ptr3;  // Constant pointer to constant int

    /*
    | Declaration            | Can change pointer? | Can change data? |
    | ---------------------- | ------------------- | ---------------- |
    | `const int* ptr`       | ✅ Yes               | ❌ No             |
    | `int* const ptr`       | ❌ No                | ✅ Yes            |
    | `const int* const ptr` | ❌ No                | ❌ No             |
    */

    /*volatile keyword Used to tell the compiler that the value may change
    unexpectedly(e.g., hardware register, shared memory in multithreading)
    Example use cases:
    Memory-mapped I/O
    Signal handlers
    Variables shared between threads (with caution)

    It prevents compiler optimizations that assume variable doesn't change
    unless explicitly written.*/
    volatile int* ptr;  // Don't optimize reads/writes to *ptr
}
