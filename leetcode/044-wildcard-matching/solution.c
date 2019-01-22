#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct object {
    char *s;
    char *p;
};

bool is_match(char *s, char *p)
{
    char *last_s = NULL, *last_p = NULL;

    while (*s != '\0') {
        if (*p == '*') {
            p++;
            if (*p == '\0') return true;
            last_s = s;
            last_p = p;
        } else if (*p == '?' || *s == *p) {
            s++;
            p++;
        } else if (last_s != NULL) {
            p = last_p;
            s = ++last_s;
        } else {
            return false;
        }
    }

    while (*p == '*') {
        p++;
    }

    return *p == '\0';
}

int main(int argc, char **argv)
{
    struct object inputs[] = {
        {.s = "aa",    .p = "a"},
        {.s = "aa",    .p = "*"},
        {.s = "cb",    .p = "?a"},
        {.s = "adceb", .p = "*a*b"},
        {.s = "acdcb", .p = "a*c?b"},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;
        char *p = inputs[i].p;
        printf("\n s = \"%s\"\n", s);
        printf(" p = \"%s\"\n", p);

        bool matched = is_match(s, p);
        printf(" Output: %s\n", matched ? "true" : "false");
    }

    return EXIT_SUCCESS;
}
