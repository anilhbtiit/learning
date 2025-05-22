#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>

// Function to simulate work
void simulateWork(const std::string &task, int duration) {
    for (int i = 0; i < duration; ++i) {
        std::cout << task << " working: step " << i + 1 << "/" << duration << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    int pipefd[2]; // Pipe file descriptors: [0] for reading, [1] for writing
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid = fork(); // Create child process

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close unused read end of the pipe

        std::cout << "Child process started. PID: " << getpid() << "\n";
        simulateWork("Child", 3);

        // Send message to the parent
        std::string message = "Hello from child process!";
        write(pipefd[1], message.c_str(), message.size() + 1); // Include null terminator
        close(pipefd[1]); // Close write end after sending the message

        std::cout << "Child process completed.\n";
        exit(0); // Terminate child process
    } else {
        // Parent process
        close(pipefd[1]); // Close unused write end of the pipe

        std::cout << "Parent process started. PID: " << getpid() << ", waiting for child to complete.\n";

        // Wait for child to complete
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            std::cout << "Child exited with status: " << WEXITSTATUS(status) << "\n";
        }

        // Read message from child
        char buffer[256];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
        if (bytesRead > 0) {
            std::cout << "Parent received message: " << buffer << "\n";
        }
        close(pipefd[0]); // Close read end

        std::cout << "Parent process completed.\n";
    }

    return 0;
}

