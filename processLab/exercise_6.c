#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int a = 20, b = 10, result[4];
    int fd[2];

    for (int i = 0; i < 4; i++) {
        pipe(fd);
        pid_t pid = fork();

        if (pid == 0) {
            close(fd[0]);

            int r;
            if (i == 0) r = a + b;
            else if (i == 1) r = a - b;
            else if (i == 2) r = a * b;
            else r = a / b;

            write(fd[1], &r, sizeof(r));
            close(fd[1]);
            exit(0);
        } else {
            close(fd[1]);
            read(fd[0], &result[i], sizeof(result[i]));
            close(fd[0]);
            waitpid(pid, NULL, 0);
        }
    }

    printf("Addition = %d\n", result[0]);
    printf("Subtraction = %d\n", result[1]);
    printf("Multiplication = %d\n", result[2]);
    printf("Division = %d\n", result[3]);

    return 0;
}