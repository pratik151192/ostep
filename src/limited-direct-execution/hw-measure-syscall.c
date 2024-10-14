#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {

    int fd = open("ipsum.txt", O_RDONLY);

    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    int total_bytes_read = 0;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (;;) {

        char buf[4096];
        int n = read(fd, buf, 4096);
        if (n == 0) {
            printf("file ended!");
            break;
        }
        total_bytes_read += n;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("file ended!\n bytes read: %d\n", total_bytes_read);
    printf("%ld", (end.tv_nsec - start.tv_nsec) / 1000);
    
}