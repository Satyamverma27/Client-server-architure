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
        string expression;
        cout << "Enter a mathematical expression (or type 'exit' to quit): ";
        getline(cin, expression);

        msg.type = 1;
        strcpy(msg.text, expression.c_str());
        msgsnd(msgid, &msg, sizeof(msg), 0);

        if (expression == "exit") break;

        msgrcv(msgid, &msg, sizeof(msg), 2, 0);
        cout << "Result: " << msg.text;
    }

    return 0;
}
