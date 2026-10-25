
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./exercise_3 r|c|a|m value [number]\n");
        return 1;
    }

    if (strcmp(argv[1], "r") == 0) {
        for (int i = strlen(argv[2]) - 1; i >= 0; i--)
            printf("%c", argv[2][i]);
        printf("\n");
    }
    else if (strcmp(argv[1], "c") == 0) {
        int v = 0, c = 0;

        for (int i = 0; argv[2][i]; i++) {
            char ch = argv[2][i];

            if (strchr("aeiouAEIOU", ch))
                v++;
            else if ((ch >= 'a' && ch <= 'z') ||
                     (ch >= 'A' && ch <= 'Z'))
                c++;
        }

        printf("Vowels = %d\n", v);
        printf("Consonants = %d\n", c);
    }
    else if (strcmp(argv[1], "a") == 0 && argc >= 4) {
        printf("Sum = %d\n", atoi(argv[2]) + atoi(argv[3]));
    }
    else if (strcmp(argv[1], "m") == 0 && argc >= 4) {
        printf("Product = %d\n", atoi(argv[2]) * atoi(argv[3]));
    }
    else {
        printf("Invalid arguments!\n");
    }

    return 0;
}
