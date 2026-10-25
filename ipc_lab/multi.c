
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int fd[2], a[] = {1, 2, 3, 4, 5};
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        write(fd[1], a, sizeof(a));
        close(fd[1]);
        exit(0);
    }

    if (fork() == 0) {
        int b[5], sum = 0;
        close(fd[1]);
        read(fd[0], b, sizeof(b));
        for (int i = 0; i < 5; i++)
            sum += b[i];
        printf("Sum = %d\n", sum);
        close(fd[0]);
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
