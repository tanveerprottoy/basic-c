#include <stdio.h>
#include <stdlib.h>

void memory_leak() {
    int* ptr = malloc(sizeof(int));
    *ptr = 100;

    // no free, memory leak
    // ptr points to heap memory, but we never free() it.
    // The OS might reclaim it at process end, but tools like Valgrind will flag it
}

void double_free() {
    int* ptr = malloc(sizeof(int));
    *ptr = 42;

    // The second free() call is undefined behavior
    // It can cause a crash or silently corrupt memory
    free(ptr);
    free(ptr);
}

void use_after_free() {
    int* ptr = malloc(sizeof(int));
    *ptr = 55;
    free(ptr);

    printf("%d\n", *ptr);  // use-after-free
}

void local_variable() {
    // this variable will be allocated in the stack
    // it will be freed after function returns
    int a = 42;  // lives until local_variable() returns
}

int* local_variable_return() {
    // this will not work as we define
    // a as a local (stack) variable
    // this memory is bound to the function stack
    // so this address will be freed and be invalid
    // after the function returns
    // detail:  is allocated on the stack when bar() is called.
    // When bar() returns, the stack frame is destroyed—a no longer exists.
    // But you return &a,
    // a pointer to memory that has been invalidated.
    // The caller now holds a dangling pointer—a pointer to garbage memory.
    // Accessing this pointer causes undefined behavior
    // Why It’s Dangerous
    // Sometimes it seems to work, especially in small test programs,
    // because the stack memory might not be reused immediately.
    // But this is not reliable.Any of these can happen :
    //     Program crashes(segfault)
    //     Garbage values are read.
    //     Memory corruption.
    //     Security vulnerabilities(e.g., in exploits)
    int a = 10;
    return &a;
}

int main() {
    memory_leak();

    double_free();

    use_after_free();

    return 0;
}