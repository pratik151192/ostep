#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    pid_t child_pid = fork();

    if (child_pid < 0) {
        write(STDERR_FILENO, "Error forking!", 14);
        exit(1);
    } else if (child_pid == 0) {
        printf("hello");
    } else {
        sleep(1);
        printf("goodbye");
    }
}