#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MQ_KEY		0x1234

typedef struct msg {
    long type;
    int num1;
    int num2;
    int result;
} msg_t;

int main() {
    int mqid, ret, s;
    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if(mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }

    ret = fork();
    if(ret == 0) {
        // child process
        msg_t m1, m2;
        m1.type = 1;
        printf("Child: Enter two numbers: ");
        scanf("%d %d", &m1.num1, &m1.num2);

        // Send the message to parent
        ret = msgsnd(mqid, &m1, sizeof(m1) - sizeof(long), 0);
        if(ret < 0) {
            perror("msgsnd() failed");
            _exit(1);
        }

        // Receive result from parent
        ret = msgrcv(mqid, &m2, sizeof(m2) - sizeof(long), 2, 0);
        if(ret < 0) {
            perror("msgrcv() failed");
            _exit(1);
        }
        printf("Child: Sum received from parent: %d\n", m2.result);
        _exit(0);
    }
    else {
        // parent process
        msg_t m1, m2;

        // Receive numbers from child
        ret = msgrcv(mqid, &m1, sizeof(m1) - sizeof(long), 1, 0);
        if(ret < 0) {
            perror("msgrcv() failed");
            _exit(1);
        }
        printf("Parent: Numbers received from child: %d, %d\n", m1.num1, m1.num2);

        // Calculate sum
        m2.result = m1.num1 + m1.num2;
        m2.type = 2;

        // Send result back to child
        ret = msgsnd(mqid, &m2, sizeof(m2) - sizeof(long), 0);
        if(ret < 0) {
            perror("msgsnd() failed");
            _exit(1);
        }

        // Wait for child to complete
        wait(&s);
    }
    // Destroy the message queue
    msgctl(mqid, IPC_RMID, NULL);

    return 0;
}

