#include <iostream>
#include <csignal>
#include <unistd.h>

void signalHandler(int signum) {
    std::cout << "Signal received: " << signum << std::endl;
}

int main() {
    signal(SIGUSR1, signalHandler);
    if (fork() == 0) { // Child process
        sleep(1);
        kill(getppid(), SIGUSR1); // Send signal to parent
    } else { // Parent process
        pause(); // Wait for the signal
    }
    return 0;
}

