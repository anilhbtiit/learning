#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

int main() {
    // Generate a unique key
    key_t key = ftok("token.txt", 65);

    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Create a shared memory segment
    // The key is used in shmget() to create a shared memory segment. If the same key is used by another process, it can access the same segment.
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Attach the shared memory segment
    // Processes attach to the shared memory segment using the key and exchange data.
    char* sharedMem = (char*)shmat(shmid, NULL, 0);
    if (sharedMem == (void*)-1) {
        perror("shmat failed");
        return 1;
    }

    // Write to the shared memory segment
    // All processes using the same file and project identifier will generate the same key, allowing them to coordinate access to the same IPC object.
    strcpy(sharedMem, "Hello, shared memory!");

    std::cout << "Data written to shared memory: " << sharedMem << std::endl;

    // Detach the shared memory segment
    shmdt(sharedMem);

    return 0;
}

