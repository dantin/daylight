#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    char *str;
    char *target;
};

int str_str(char *haystack, char *needle)
{
    int hlen = strlen(haystack);
    int nlen = strlen(needle);

    if (nlen == 0) {
        return 0;
    }

    /* brute force */
    int i, j;
    for (i = 0; i < hlen; i++) {
        int found = 1;
        if (haystack[i] == needle[0]) {
            for (j = 1; j < nlen; j++) {
                if (i + j < hlen) {
                    if (haystack[i+j] != needle[j]) {
                        found = 0;
                        break;
                    }

                } else {
                    return -1;
                }
            }
            if (found == 1) {
                return i;
            }
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    struct object inputs[] = {
        {"hello", "ll"},
        {"aaaaa", "bba"},
    };
    int i, idx, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        printf("\n haystack = \"%s\", needle = \"%s\"\n", inputs[i].str, inputs[i].target);
        idx = str_str(inputs[i].str, inputs[i].target);
        printf(" Output: %d\n", idx);
    }

    return EXIT_SUCCESS;
}
