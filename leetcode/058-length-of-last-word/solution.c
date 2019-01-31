#include <stdio.h>
#include <stdlib.h>

int length_of_last_word(char *s)
{
    int len = 0;
    while (*s != '\0') {
        if (s[-1] == ' ' && s[0] != ' ') {
            len = 1;
        } else if (*s != ' ') {
            len++;
        }
        s++;
    }
    return len;
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "Hello World",
    };
    int i, len = sizeof(inputs) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *s = inputs[i];
        printf("\n Input: \"%s\"\n", s);
        int length = length_of_last_word(s);
        printf(" Output: %d\n", length);
    }

    return EXIT_SUCCESS;
}
