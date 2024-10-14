#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    int ret = fork();

    if (ret < 0) {
        write(STDERR_FILENO, "Error forking!", 15);
        exit(1);
    } else if (ret == 0) {
        printf("hello");
    } else {
        wait(NULL);
        printf("goodbye");
    }
}