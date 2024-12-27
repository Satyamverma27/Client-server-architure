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

// Function to evaluate the mathematical expression
int evaluate_expression(const char *expr) {
    int num1, num2;
    char op;

    // Parse the expression (e.g., "1 + 1", "2 * 3")
    if (sscanf(expr, "%d %c %d", &num1, &op, &num2) != 3) {
        return -1; // Error if the format is invalid
    }

    // Perform the operation based on the operator
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return (num2 != 0) ? num1 / num2 : -1; // Avoid division by zero
        default: return -1; // Unsupported operator
    }
}


int main() {
    key_t key = ftok("msgfile", 65); // Generate a unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue

    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    struct message msg;

    while (1) {
        // Receive message from client
        if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {
            perror("msgrcv failed");
            continue; // Continue to the next iteration if receiving fails
        }

        printf("Server: Received expression: %s\n", msg.text);

        int result = evaluate_expression(msg.text); // Evaluate the expression

        // Prepare the response message
        if (result == -1) {
            snprintf(msg.text, sizeof(msg.text), "Error: Invalid expression");
        } else {
            snprintf(msg.text, sizeof(msg.text), "%d", result); // Write result to message
        }

        // Send the result back to the client
        msg.msg_type = 2; // Set message type for response

  if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd failed");
        }
    }

    msgctl(msgid, IPC_RMID, NULL); // Destroy message queue
    return 0;
}
