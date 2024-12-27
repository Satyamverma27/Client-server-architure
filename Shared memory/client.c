#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    char *shared_memory = (char *)shmat(shmid, NULL, 0);

    while (1) {
        char expression[100];
        printf("Enter a mathematical expression (e.g., 1 + 1): ");
        fgets(expression, sizeof(expression), stdin);
        expression[strcspn(expression, "\n")] = '\0';

        strcpy(shared_memory, expression);
        while (shared_memory[0] != '*') {
            usleep(100000); // Wait for server response
        }

        printf("Client: %s\n", shared_memory + 1); // Display result
        shared_memory[0] = '\0'; // Reset shared memory
    }

    shmdt(shared_memory);

    return 0;
}
