#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>


struct Message {
    long messageType;
    char text[100];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (fork() == 0) { // Child process
        Message message = {1, "Hello from child"};
        msgsnd(msgid, &message, sizeof(message.text), 0);
    } else { // Parent process
        Message message;
        msgrcv(msgid, &message, sizeof(message.text), 1, 0);
        std::cout << "Parent received: " << message.text << std::endl;
        msgctl(msgid, IPC_RMID, NULL); // Remove the queue
    }
    return 0;
}

