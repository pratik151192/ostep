#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

double get_time_diff_micros(struct timespec *start, struct timespec *end) {
    // converting to microseconds
    return (end->tv_sec - start->tv_sec) * 1e6 + (end->tv_nsec - start->tv_nsec) / 1e3;
}

int main() {
    int fd = open("ipsum.txt", O_RDONLY);

    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    long total_bytes_read = 0;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    char buf[1];
    ssize_t n;
    while ((n = read(fd, buf, 1)) > 0) {
        total_bytes_read += n;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    if (n < 0) {
        perror("Error reading file");
        close(fd);
        exit(1);
    }

    close(fd);

    double elapsed_time_micros = get_time_diff_micros(&start, &end);
    double avg_time_per_byte_micros = elapsed_time_micros / total_bytes_read;

    printf("File read complete.\n");
    printf("Total bytes read: %ld\n", total_bytes_read);
    printf("Total time: %.2f microseconds\n", elapsed_time_micros);
    printf("Average time per byte: %.4f microseconds\n", avg_time_per_byte_micros);
    printf("Read speed: %.2f MB/s\n", (total_bytes_read / 1e6) / (elapsed_time_micros / 1e6));

    return 0;
}