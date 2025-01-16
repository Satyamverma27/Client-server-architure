#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

using namespace std;

struct message {
    long type;
    char text[100];
};

int main() {
    key_t key = ftok("msgqueue", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    message msg;

    while (true) {
        msgrcv(msgid, &msg, sizeof(msg), 1, 0);
        string expression(msg.text);
        if (expression == "exit") break;

        string command = "echo 'print(" + expression + ")' | python3";
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            cerr << "Failed to run command" << endl;
            continue;
        }

        char result[100];
        fgets(result, 100, pipe);
        pclose(pipe);

        msg.type = 2;
        strcpy(msg.text, result);
        msgsnd(msgid, &msg, sizeof(msg), 0);
    }

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
