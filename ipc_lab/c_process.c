
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[3][2], n = 3, result;

    for (int i = 0; i < 3; i++)
        pipe(fd[i]);

    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            for (int j = 0; j < 3; j++) {
                close(fd[j][0]);
                if (j != i) close(fd[j][1]);
            }

            if (i == 0) result = n * n;
            else if (i == 1) result = n * n * n;
            else result = n * 2;

            write(fd[i][1], &result, sizeof(result));
            close(fd[i][1]);
            _exit(0);
        }
    }

    for (int i = 0; i < 3; i++)
        close(fd[i][1]);

    for (int i = 0; i < 3; i++) {
        read(fd[i][0], &result, sizeof(result));
        if (i == 0) printf("Square = %d\n", result);
        if (i == 1) printf("Cube = %d\n", result);
        if (i == 2) printf("Double = %d\n", result);
        close(fd[i][0]);
    }

    for (int i = 0; i < 3; i++)
        wait(NULL);

    return 0;
}
