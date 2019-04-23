#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int min_cut(char *s)
{
    int len = strlen(s);
    if (len <= 1) {
        return 0;
    }

    int i, j;
    int *cuts = malloc((len + 1) * sizeof(int));
    for (i = 0; i <= len; i++) {
        cuts[i] = i - 1;
    }

    for (i = 0; i < len; i++) {
        /* odd length palindrome. */
        for (j = 0; i - j >= 0 && i + j < len && s[i - j] == s[i + j]; j++) {
            if (cuts[i - j] + 1 < cuts[i + j + 1]) {
                cuts[i + j + 1] = cuts[i - j] + 1;
            }
        }

        /* even length palindrome. */
        for (j = 1; i - j + 1 >= 0 && i + j < len && s[i - j + 1] == s[i + j]; j++) {
            if (cuts[i - j + 1] + 1 < cuts[i + j + 1]) {
                cuts[i + j + 1] = cuts[i - j + 1] + 1;
            }
        }
    }

    int count = cuts[len];
    free(cuts);
    return count;
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "aab",
    };
    int i, len = sizeof(inputs) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *s = inputs[i];
        printf("\n Input: \"%s\"", s);
        int count = min_cut(s);
        printf("\n Output: %d\n", count);
    }

    return EXIT_SUCCESS;
}
