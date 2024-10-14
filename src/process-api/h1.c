#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child_pid = fork();
    
    int x = 100;
    if (child_pid == -1) {
        printf("Error");
        exit(1);
    } else if (child_pid == 0) {
        printf("child's x is %d\n", x);
        x = x + 1;
        printf("child's mutated x is %d\n", x);
    } else {
        printf("parent's x is %d\n", x);
        x = x + 1;
        printf("parent's mutated x is %d\n", x);
    }
    
    return 0;
}