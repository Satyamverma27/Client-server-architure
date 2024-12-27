#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 1024

// Define the message structure
struct message {
    long msg_type; // Message type
    char text[MAX_TEXT]; // Message text
};

int main() {
    key_t key = ftok("msgfile", 65); // Generate a unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue

    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    struct message msg;

    // Prompt user to enter a mathematical expression
    printf("Enter a mathematical expression (e.g., 1 + 1): ");
    fgets(msg.text, sizeof(msg.text), stdin);
    msg.text[strcspn(msg.text, "\n")] = 0; // Remove trailing newline
    msg.msg_type = 1; // Set message type for request

    // Send the expression to the server
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }
    printf("Client: Sending expression: %s\n", msg.text);

    // Receive the result from the server
    if (msgrcv(msgid, &msg, sizeof(msg.text), 2, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }
    printf("Result from server: %s\n", msg.text);

    msgctl(msgid, IPC_RMID, NULL); // Destroy message queue
    return 0;
}
