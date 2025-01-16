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
        string expr;
        cout << "Enter a mathematical expression (or type 'exit' to quit): ";
        getline(cin, expr);
        strcpy(expression, expr.c_str());

        if (expr == "exit") break;

        sleep(1);
        cout << "Result: " << expression;
    }

    shmdt(expression);

    return 0;
}
