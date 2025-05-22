#include <unistd.h>
#include <sys/types.h>
#include <iostream>

int main() {
    pid_t pid = fork();
    std::cout << "pid: " << pid << "\n";
    if (pid == 0) {
        // Child process
      std::cout << "forking program executable \n";
      execl("../compilerSteps/program", "child_executable", NULL);
      std::cout << "THIS SHOULD NOT BE EXECUTED \n";
    } else if (pid > 0) {
        // Parent process
        std::cout << "Parent process running\n";
    } else {
        std::cerr << "Fork failed\n";
    }
    return 0;
}

