#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int ret = fork();
    
    int x = 100;
    if (ret == -1) {
        printf("Error");
        exit(1);
    } else if (ret == 0) {
        printf("child's x is %d\n", x);
    } else {
        wait(NULL);
        printf("parent's x is %d\n", x);
    }
    return 0;
}