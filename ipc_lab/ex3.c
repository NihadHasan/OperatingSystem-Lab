
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2], n = 5, result;
    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], &n, sizeof(n));
        result = n * n;
        write(p2[1], &result, sizeof(result));

        close(p1[0]);
        close(p2[1]);
        return 0;
    }

    close(p1[0]);
    close(p2[1]);

    write(p1[1], &n, sizeof(n));
    read(p2[0], &result, sizeof(result));

    printf("Square = %d\n", result);

    close(p1[1]);
    close(p2[0]);
    wait(NULL);
    return 0;
}
