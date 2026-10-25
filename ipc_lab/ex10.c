
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buf[100];
    ssize_t n;

    pipe(fd);

    for (int i = 1; i <= 3; i++) {
        if (fork() == 0) {
            char msg[30];
            int len;

            close(fd[0]);

            len = snprintf(msg, sizeof(msg),
                           "Child %d writes data\n", i);
            write(fd[1], msg, len);

            close(fd[1]);
            _exit(0);
        }
    }

    close(fd[1]);

    while ((n = read(fd[0], buf, sizeof(buf))) > 0)
        write(STDOUT_FILENO, buf, n);

    close(fd[0]);

    for (int i = 0; i < 3; i++)
        wait(NULL);

    return 0;
}
