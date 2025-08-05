/*
 Thread Creation (POSIX Threads - pthread)
To create and manage threads in C, the pthread library is used (#include <pthread.h>).
*/

#include <pthread.h>
#include <stdio.h>

void* my_thread_func(void* arg) {
    printf("Hello from thread!\n");
    return NULL;
}

void create_thread() {
    pthread_t thread_id;

    // Create a thread
    pthread_create(&thread_id, NULL, my_thread_func, NULL);

    // Wait for the thread to finish
    pthread_join(thread_id, NULL);

    printf("Thread finished\n");

    /*
    Important functions:
    pthread_create(&thread, attr, function, arg)
    pthread_join(thread, retval)
    pthread_exit(retval)
    */
}

/*
Race Conditions
A race condition occurs when two or more threads access shared data without proper
synchronization, and the final result depends on who runs first.
*/
int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
    return NULL;
}

int race_condition() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter: %d\n", counter);  // May not be 200000 due to race

    /*
    Why?: counter++ is not atomic. It translates to:
    load counter into register
    increment register
    store register back into memory
    Two threads can interleave these steps.
    */
}

/*
Mutex (Mutual Exclusion Locks)
Mutexes are used to prevent race conditions by allowing only one thread to access
a critical section at a time.
*/
int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void mutex() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Counter: %d\n", counter);  // Should be 200000

    /*
    Functions:
    pthread_mutex_init(&mutex, NULL)
    pthread_mutex_lock(&mutex)
    pthread_mutex_unlock(&mutex)
    pthread_mutex_destroy(&mutex)
    Always release the mutex (unlock) or you can deadlock.
    */
}

/*
Thread-Local Storage (TLS)
What is TLS?
Thread-local storage (TLS) allows each thread to have its own copy of a variable,
even though it may be declared globally or statically.
This helps avoid race conditions without locking, when each thread needs a private copy
of data (e.g., buffers, counters, etc.).
*/
// POSIX TLS Using pthread_key_t
#include <pthread.h>
#include <stdio.h>

pthread_key_t tls_key;

void destructor(void* ptr) {
    free(ptr);
}

void* thread_func(void* arg) {
    char* buf = malloc(100);
    sprintf(buf, "Hello from thread %ld\n", (long)arg);
    pthread_setspecific(tls_key, buf);

    printf("%s", (char*)pthread_getspecific(tls_key));
    return NULL;
}

void posix_tls_pthread_key_t() {
    pthread_t t1, t2;

    // Create TLS key with destructor
    pthread_key_create(&tls_key, destructor);

    pthread_create(&t1, NULL, thread_func, (void*)1);
    pthread_create(&t2, NULL, thread_func, (void*)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_key_delete(tls_key);

    /*
    TLS functions:
    pthread_key_create(&key, destructor)
    pthread_setspecific(key, value)
    pthread_getspecific(key)
    pthread_key_delete(key)
    Each thread has its own void* value associated with the key.
    */
}

/*
GCC/Clang: __thread (non-portable)
If portability isn't an issue, GCC/Clang provide a simpler syntax:

*/
__thread int tls_var = 0;

void* thread_func(void* arg) {
    tls_var++;
    printf("tls_var = %d\n", tls_var);
    return NULL;
    // Each thread will get its own instance of tls_var.
}

/*
| Concept              | Purpose                                      | Tooling                          |
| -------------------- | -------------------------------------------- | -------------------------------- |
| Thread creation      | Run multiple functions concurrently          | `pthread_create`, `pthread_join` |
| Race condition       | Bug due to unsynchronized shared data access | Happens if no locking used       |
| Mutex                | Synchronize access to shared data            | `pthread_mutex_lock/unlock`      |
| Thread-local storage | Keep thread-private data                     | `pthread_key_t` or `__thread`    |

*/