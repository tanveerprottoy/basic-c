#include <stdio.h>

#include "problems/leetcode.c"
#include "thread/mutex.c"

void *count_entry() {
    increment();

    printf("%d\n", read());

    return NULL;
}

void multi_threading_count() {
    pthread_t thread1, thread2;

    // create thread 1
    pthread_create(&thread1, NULL, count_entry, NULL);

    // create thread 2
    pthread_create(&thread2, NULL, count_entry, NULL);

    // wait for thread 1 to finish
    pthread_join(thread1, NULL);

    // wait for thread 2 to finish
    pthread_join(thread2, NULL);
}

void *thread_entry(void *arg) {
    printf("Thread created: %p\n", arg);

    char *message = (char *)arg;

    // dereference the argument
    printf("%s\n", *message);

    return NULL;
}

void multi_threading_simple() {
    pthread_t thread1, thread2;

    char hello[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

    char message0[] = "Hello, World! from thread 1";
    char message1[] = "Hello, World! from thread 2";

    // create thread 1
    pthread_create(&thread1, NULL, thread_entry, &message0);

    // create thread 2
    pthread_create(&thread2, NULL, thread_entry, &message1);

    // wait for thread 1 to finish
    pthread_join(thread1, NULL);

    // wait for thread 2 to finish
    pthread_join(thread2, NULL);
}

void misc() {
    //     mem_alloc();
    /*  short a;
     int i;
     long b;
     long long c;
     long double d;

     printf("size of short = %lu bytes\n", sizeof(a));
     printf("size of int = %lu bytes\n", sizeof(i));
     printf("size of long = %lu bytes\n", sizeof(b));
     printf("size of long long = %lu bytes\n", sizeof(c));
     printf("size of long double= %lu bytes\n", sizeof(d));

     printf("TAFHEEM\n"); */

    /* int nums[10] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    int* ptr = nums;

    int size = sizeof(nums) / sizeof(nums[0]);

    printf("%d\n", removeDuplicates(ptr, size)); */
}

void thread_safe_counter() {
    /* increment();

    printf("%d\n", read()); */
}

int main() {
    multi_threading_simple();

    // multi_threading_count();

    return EXIT_SUCCESS;
}
