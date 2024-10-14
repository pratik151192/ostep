#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Error opening file", 23);
        exit(1);
    }

    pid_t child_pid = fork();
    if (child_pid < 0) {
        write(STDERR_FILENO, "Error forking", 12);
        exit(1);
    } else if (child_pid == 0) {
        const char *item = "New item from child";
        write(fd, item, strlen(item));
        close(fd);
    } else {
        const char *item = "New item from parent";
        write(fd, item, strlen(item));
        char buf[2];
        read(fd, buf, 2);
        write(STDOUT_FILENO, buf, 2);
        close(fd);
    }
}