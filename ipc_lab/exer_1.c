
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char msg[] = "Hello Child";
    char buf[50];

    pipe(fd);

    if (fork() == 0) {
        close(fd[1]);
        read(fd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], msg, sizeof(msg));
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
