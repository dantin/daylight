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
    if (*p == '\0') {
        return *s == '\0';
    }
    /* p's length 1 is special case */
    if (*(p+1) == '\0' || *(p+1) != '*') {
        if (*s == '\0' || (*p != '.' && *s != *p)) {
            return false;
        } else {
            return is_match(s+1, p+1);
        }
    }
    int len = strlen(s);
    int i = -1;
    while (i < len && (i < 0 || *p == '.' || *p == *(s+i))) {
        if (is_match(s+i+1, p+2)) {
            return true;
        }
        i++;
    }
    return false;
}

int main(int argc, char **argv)
{
    int i;
    struct object array[] = {
        {"aa", "a"},
        {"aa", "a*"},
        {"ab", ".*"},
        {"aab", "c*a*b"},
        {"mississippi", "mis*is*p*."}
    };
    int len = sizeof(array) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        char *s = array[i].s;
        char *p = array[i].p;
        printf(" s = %s\n p = %s\n Output: %s\n\n", s, p, is_match(s, p) ? "true" : "false");
    }

    return 0;
}
