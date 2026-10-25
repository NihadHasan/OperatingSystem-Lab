#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int *counter = mmap(NULL, sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *counter = 0;

    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            for (int j = 0; j < 10000; j++) {
                (*counter)++;  
            }
            exit(0);
        }
    }

    for (int i = 0; i < 3; i++)
        wait(NULL);

    printf("Without lock: %d\n", *counter);

    *counter = 0;
    int fd = open("/tmp/ex5lock", O_CREAT | O_RDWR, 0600);

    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            for (int j = 0; j < 10000; j++) {
                flock(fd, LOCK_EX);
                (*counter)++;
                flock(fd, LOCK_UN);
            }
            close(fd);
            exit(0);
        }
    }

    for (int i = 0; i < 3; i++)
        wait(NULL);

    printf("With lock: %d\n", *counter);

    close(fd);
    munmap(counter, sizeof(int));
    return 0;
}