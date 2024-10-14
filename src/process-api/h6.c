#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t child1 = fork();
    pid_t child2 = fork();
    
    if (child1 == -1 || child2 == -1) {
        perror("Fork error");
        exit(1);
    }

    if (child1 > 0 && child2 > 0) {
        printf("Parent process (PID: %d)\n", getpid());
        waitpid(child1, NULL, 0);
        waitpid(child2, NULL, 0);
        printf("Parent is done!\n");
    } else if (child1 == 0) {
        printf("First child (PID: %d, Parent: %d)\n", getpid(), getppid());
        waitpid(child2, NULL, 0);
    } else if (child2 == 0) {
        printf("Second child of parent (PID: %d, Parent: %d)\n", getpid(), getppid());
    } else {
        printf("Child of first child (PID: %d, Parent: %d)\n", getpid(), getppid());
    }
    
    return 0;
}