#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child_pid = fork();
    if (child_pid == -1) {
        printf("Error");
        exit(1);
    } else if (child_pid == 0) {
        printf("Child entering with pid: %d\n", getpid());
        wait(NULL);
        perror("Child tried to wait; error is ");
    } else {
        int child_pid = wait(NULL);
        printf("Child pid is %d\n", child_pid);
        printf("Parent is done!");
    }
    
    return 0;
}