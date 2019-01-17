#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10000

void parse(char *input, char *output)
{
    char *p = input, *q = output;

    while (*p != '\0') {
        int count = 1;
        while (p[0] == p[1]) {
            count++;
            p++;
        }

        // reverse count.
        int n = 0;
        while (count > 0) {
            n *= 10;
            n += count % 10;
            count /= 10;
        }

        // show count.
        while (n > 0) {
            *q++ = (n % 10) + '0';
            n /= 10;
        }

        *q++ = p[0];
        p++;
    }

    *q = '\0';
}

char *count_and_say(int n)
{
    if (n < 1) {
        return NULL;
    }

    char *result, *prev = malloc(BUFFER_SIZE), *next = malloc(BUFFER_SIZE);
    strcpy(prev, "1");
    if (n == 1) {
        return prev;
    }

    int i;
    for (i = 2; i <= n; i++) {
        if (i & 0x1) {
            parse(next, prev);
            result = prev;
        } else {
            parse(prev, next);
            result = next;
        }
    }

    return result;
}

int main(int argc, char **argv)
{
    int inputs[] = {1, 4};
    int i, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int n = inputs[i];

        printf("\n Input: %d\n", n);
        char *say = count_and_say(n);
        printf(" Output: %s\n", say);
        free(say);
    }
    
    return EXIT_SUCCESS;
}
