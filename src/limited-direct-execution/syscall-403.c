#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
    // deliberately creating a restricted file to check error message through a syscall
    open("./restricted.txt", O_CREAT, 0000);
    int fd = open("./restricted.txt", O_RDONLY);
    
    if (fd == -1) {
        // errno is auto set when a syscall errors
        printf("Error opening file: %s\n", strerror(errno));
        
        // can also use perror() for a similar effect:
        perror("Error opening file");
    }
    
    fd = open("./allowed.txt", O_RDONLY);
    if (fd > 0) {   
        printf("Opened file but just printing error to see if stored from before: %s\n", strerror(errno));
    }
    
    return 0;
}