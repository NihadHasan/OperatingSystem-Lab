#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    while (1) {
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(2);
    }
    return 0;
}