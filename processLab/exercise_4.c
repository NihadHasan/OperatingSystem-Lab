#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("data.txt", "w");
    fprintf(f, "Hello from child process!");
    fclose(f);

    pid_t pid = fork();

    if (pid == 0) {
        f = fopen("data.txt", "r");
        char s[100];
        fgets(s, sizeof(s), f);
        printf("Child read: %s\n", s);
        fclose(f);
        exit(0);
    } else {
        wait(NULL);
        f = fopen("data.txt", "a");
        fprintf(f, "\nParent wrote this.");
        fclose(f);
        printf("Parent completed.\n");
    }

    return 0;
}