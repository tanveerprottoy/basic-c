#include <pthread.h>

pthread_mutex_t mutex;

int count;

int read() {
    return count;
}

void increment() {
    // lock
    pthread_mutex_lock(&mutex);

    count++;

    // unlock
    pthread_mutex_unlock(&mutex);
}