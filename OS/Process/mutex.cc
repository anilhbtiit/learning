#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>

// Structure to hold shared memory and mutex
struct SharedData {
    pthread_mutex_t mutex;
    int shared_value;
};

int main() {
    // Size of shared memory
    const size_t SHM_SIZE = sizeof(SharedData);

    // Create shared memory
    int shm_fd = shm_open("/shared_mutex", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    // Set size of shared memory
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate failed");
        return 1;
    }

    // Map shared memory
    SharedData* shared_data = (SharedData*)mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // Initialize mutex in shared memory
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&shared_data->mutex, &attr);
    shared_data->shared_value = 0;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        for (int i = 0; i < 5; ++i) {
            pthread_mutex_lock(&shared_data->mutex);
            ++shared_data->shared_value;
            std::cout << "Child incremented value to: " << shared_data->shared_value << "\n";
            pthread_mutex_unlock(&shared_data->mutex);
            sleep(1);
        }
    } else {
        // Parent process
        for (int i = 0; i < 5; ++i) {
            pthread_mutex_lock(&shared_data->mutex);
            ++shared_data->shared_value;
            std::cout << "Parent incremented value to: " << shared_data->shared_value << "\n";
            pthread_mutex_unlock(&shared_data->mutex);
            sleep(1);
        }

        // Wait for child to finish
        wait(nullptr);

        // Cleanup
        pthread_mutex_destroy(&shared_data->mutex);
        munmap(shared_data, SHM_SIZE);
        shm_unlink("/shared_mutex");
    }

    return 0;
}

