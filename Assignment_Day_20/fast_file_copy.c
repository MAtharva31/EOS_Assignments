#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_SIZE (1 * 1024 * 1024 * 1024)  // 1 GB

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *src_filename = argv[1];
    const char *dest_filename = argv[2];

    // Step 1: Open source file in read-only mode
    int src_fd = open(src_filename, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Step 2: Get size of source file
    struct stat src_stat;
    if (fstat(src_fd, &src_stat) < 0) {
        perror("Error getting source file size");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    if (src_stat.st_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: Source file size exceeds 1 GB\n");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    size_t src_size = src_stat.st_size;

    // Step 3: Map source file contents to memory using mmap()
    void *src_map = mmap(NULL, src_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if (src_map == MAP_FAILED) {
        perror("Error mapping source file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Step 4: Create destination file in read-write mode
    int dest_fd = open(dest_filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (dest_fd < 0) {
        perror("Error opening/creating destination file");
        munmap(src_map, src_size);
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Step 5: Make size of destination file same as size of source file using ftruncate()
    if (ftruncate(dest_fd, src_size) < 0) {
        perror("Error setting destination file size");
        munmap(src_map, src_size);
        close(src_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    // Step 6: Map destination file contents to memory using mmap() -- MAP_SHARED
    void *dest_map = mmap(NULL, src_size, PROT_READ | PROT_WRITE, MAP_SHARED, dest_fd, 0);
    if (dest_map == MAP_FAILED) {
        perror("Error mapping destination file");
        munmap(src_map, src_size);
        close(src_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    // Step 7: Copy source file to destination file using memcpy()
    memcpy(dest_map, src_map, src_size);

    // Step 8: Close source and destination files
    munmap(src_map, src_size);
    munmap(dest_map, src_size);
    close(src_fd);
    close(dest_fd);

    return 0;
}

