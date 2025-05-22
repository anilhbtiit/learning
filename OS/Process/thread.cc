#include <iostream>
#include <pthread.h>
#include <unistd.h>

// Shared data and mutex
int shared_counter = 0;
pthread_mutex_t mutex;

void* thread_function(void* arg) {
    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex);
        ++shared_counter;
        std::cout << "Thread " << (char*)arg << " incremented counter to: " << shared_counter << "\n";
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_function, (void*)"A");
    pthread_create(&thread2, NULL, thread_function, (void*)"B");

    // Wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    std::cout << "Final counter value: " << shared_counter << "\n";
    return 0;
}

