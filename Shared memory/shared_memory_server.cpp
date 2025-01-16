#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *expression = (char*) shmat(shmid,(void*)0,0);

    while (true) {
        if (strlen(expression) > 0) {
            string expr(expression);
            if (expr == "exit") break;

            string command = "echo 'print(" + expr + ")' | python3";
            FILE* pipe = popen(command.c_str(), "r");
            if (!pipe) {
                cerr << "Failed to run command" << endl;
                continue;
            }

            char result[128];
            fgets(result, 128, pipe);
            pclose(pipe);

            strcpy(expression, result);
            sleep(1);
        }
    }

    shmdt(expression);
    shmctl(shmid,IPC_RMID,NULL);

    return 0;
}
