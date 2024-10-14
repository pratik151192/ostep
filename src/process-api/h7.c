#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        printf("Error");
        exit(1);
    } else if (child_pid == 0) {
        close(1);
        printf("I'm a child");
    } else {
        printf("I'm the parent");
    }
    
    return 0;
}