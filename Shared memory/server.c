#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define SHM_SIZE 1024

bool validate_expression(const char *expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (!isdigit(expr[i]) && !isspace(expr[i]) && !strchr("+-*/.", expr[i])) {
            return false;
        }
    }
    return true;
}

double evaluate_expression(const char *expr) {
    char op;
    double num1, num2;

    if (sscanf(expr, "%lf %c %lf", &num1, &op, &num2) == 3 ||
        sscanf(expr, "%lf%c%lf", &num1, &op, &num2) == 3) {
        switch (op) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': return num2 != 0 ? num1 / num2 : NAN;
            default: return NAN;
        }
    }

    return NAN; // If parsing fails
}

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    char *shared_memory = (char *)shmat(shmid, NULL, 0);

    printf("Server: Waiting for expressions...\n");
    while (1) {
        while (shared_memory[0] == '\0') {
            usleep(100000);
        }

        printf("Server: Received expression: %s\n", shared_memory);
        if (validate_expression(shared_memory)) {
            double result = evaluate_expression(shared_memory);
            if (isnan(result)) {
                strcpy(shared_memory, "Error: Invalid expression");
            } else {
                sprintf(shared_memory, "Result: %.2f", result);
            }
        } else {
            strcpy(shared_memory, "Error: Invalid expression");
        }

        shared_memory[0] = '*'; // Indicate result is ready
    }

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
