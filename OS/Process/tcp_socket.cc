#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

//#define PORT 8080
#define PORT 9994

void server() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    int client_fd = accept(server_fd, nullptr, nullptr);
    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer));
    std::cout << "Server received: " << buffer << std::endl;
    send(client_fd, "Hello from server", 17, 0);
    close(client_fd);
    close(server_fd);
}

void client() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    connect(sock, (struct sockaddr*)&address, sizeof(address));

    send(sock, "Hello from client", 17, 0);
    char buffer[1024] = {0};
    read(sock, buffer, sizeof(buffer));
    std::cout << "Client received: " << buffer << std::endl;
    close(sock);
}

int main() {
    pid_t pid = fork();
    if (pid == 0) { 
      std::cout << "Child PID: " << getpid() << std::endl;
      server(); // Run server 
    }
    else {
        sleep(1); // Give server time to set up
        client(); // Run client
    }
    return 0;
}

