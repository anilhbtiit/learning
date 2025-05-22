#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <semaphore.h>
#include <sys/wait.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SIZE 1024

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
        char* shared_mem = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        sem_t* sem = sem_open(SEM_NAME, 0);

        sem_wait(sem);
        std::cout << "Child read: " << shared_mem << std::endl;
        sem_post(sem);

        munmap(shared_mem, SIZE);
        close(shm_fd);
    } else { // Parent process
        int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, SIZE);
        char* shared_mem = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

        strcpy(shared_mem, "Hello from parent!");
        sem_post(sem);

        wait(nullptr); // Wait for child
        sem_close(sem);
        sem_unlink(SEM_NAME);
        munmap(shared_mem, SIZE);
        shm_unlink(SHM_NAME);
    }

    return 0;
}

